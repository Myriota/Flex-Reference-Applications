// Copyright (c) 2016-2024, Myriota Pty Ltd, All Rights Reserved
// SPDX-License-Identifier: BSD-3-Clause-Attribution
//
// This file is licensed under the BSD with attribution  (the "License"); you
// may not use these files except in compliance with the License.
//
// You may obtain a copy of the License here:
// LICENSE-BSD-3-Clause-Attribution.txt and at
// https://spdx.org/licenses/BSD-3-Clause-Attribution.html
//
// See the License for the specific language governing permissions and
// limitations under the License.

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include "flex.h"

#ifndef GIT_SHORT_HASH
#error "Must supply a GIT_SHORT_HASH!"
#endif

#define APP_NAME "Sensor 4-20ma"
#define APP_VERSION "1.3.2"
#ifndef APP_ID
#define APP_ID 2
#endif

#ifndef MESSAGES_PER_DAY
#define MESSAGES_PER_DAY 4
#endif

#define POWER_OUT_VOLTAGE FLEX_POWER_OUT_24V
#define DELAY_SENSOR_STABILISE_MS 1500

#define FLEX_CHECK(ret) \
  do { \
    if (ret != FLEX_SUCCESS) { \
      printf("FLEX ERROR %d at @%s %d\n", ret, __func__, __LINE__); \
    } \
  } while (0);

struct message {
  uint8_t sequence_number;
  uint32_t time;
  int32_t latitude;
  int32_t longitude;
  int16_t onboard_temperature;
  uint16_t sensor_current;
} __attribute__((packed));


static uint8_t SequenceNumberNext(void) {
  static uint8_t sequence_number = 0;
  return sequence_number++;
}

static uint32_t ReadSensorExternal(void) {
  uint32_t MicroAmps = UINT32_MAX;

  if (FLEX_PowerOutInit(POWER_OUT_VOLTAGE) != 0) {
    printf("Failed to Init Power Out\n");
    goto fail_0;
  }

  if (FLEX_AnalogInputInit(FLEX_ANALOG_IN_CURRENT) != 0) {
    printf("Failed to Init Analog Input\n");
    goto fail_1;
  }

  FLEX_DelayMs(DELAY_SENSOR_STABILISE_MS);

  if (FLEX_AnalogInputReadCurrent(&MicroAmps) != 0) {
    printf("Failed to Read Current\n");
  } else {
    printf("Current = %uuA\n", (unsigned)MicroAmps);
  }

  FLEX_AnalogInputDeinit();
fail_1:
  FLEX_PowerOutDeinit();
fail_0:
  return MicroAmps;
}

static time_t QueueMessage() {
  struct message msg = {0};

  msg.sequence_number = SequenceNumberNext();
  msg.time = FLEX_TimeGet();
  int32_t latitude;
  int32_t longitude;
  FLEX_LastLocationAndLastFixTime(&latitude, &longitude, NULL);
  msg.latitude = (int32_t)latitude;
  msg.longitude = (int32_t)longitude;
  float onboard_temperature;
  FLEX_CHECK(FLEX_TemperatureGet(&onboard_temperature));
  msg.onboard_temperature = (int16_t)(onboard_temperature * 100);
  msg.sensor_current = ReadSensorExternal();

  printf("Scheduled message: %u %lu %ld %ld %d %u\n",
    msg.sequence_number,
    msg.time,
    msg.latitude,
    msg.longitude,
    msg.onboard_temperature,
    msg.sensor_current);

  FLEX_MessageSchedule((uint8_t *)&msg, sizeof(msg));

  return (FLEX_TimeGet() + 24 * 3600 / MESSAGES_PER_DAY);
}

const char *FLEX_AppVersionString() { return APP_VERSION; }

uint16_t FLEX_AppId() { return APP_ID; }

uint16_t FLEX_MessagesPerDay() { return MESSAGES_PER_DAY; }

/*
 * IMPORTANT! `FLEX_AppInit` is the entry point for your application. You
 * must provide an implementation, otherwise you will experience linking
 * errors similar to this: "undefined reference to `FLEX_AppInit'"
 */
void FLEX_AppInit() {
  printf("%s: %s-%s\n", APP_NAME, APP_VERSION, GIT_SHORT_HASH);

  FLEX_JobSchedule(QueueMessage, FLEX_ASAP());
}
