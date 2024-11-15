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

#define APP_NAME "Pulse Counter"
#define APP_VERSION "1.2.2"
#ifndef APP_ID
#define APP_ID 3
#endif

#ifndef MESSAGES_PER_DAY
#define MESSAGES_PER_DAY 4
#endif

#define PULSE_LOG_COUNT 5
#define PCNT_STABILISE_DELAY_MS 5

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
  uint16_t pulse_counter;
} __attribute__((packed));
_Static_assert(sizeof(struct message) <= FLEX_MAX_MESSAGE_SIZE,
    "max message size");

static uint8_t SequenceNumberNext(void) {
  static uint8_t sequence_number = 0;
  return sequence_number++;
}

static uint32_t *GetInitPulseCount(void) {
  static uint32_t init = 0;
  return &init;
}

static uint16_t ReadPulseCount(void) {
  const uint32_t *init = GetInitPulseCount();
  uint16_t pcnt = (uint16_t)(FLEX_PulseCounterGet() - *init);
  printf("pulse_counter = %u\n", pcnt);
  return pcnt;
}

static void PulseCounterEvent(void) {
  // Debugging method. Every 5 pulses print out the sensor values.
  ReadPulseCount();
}

static void PulseCounterInit(void) {
  // Enable pulse counter
  if (FLEX_PulseCounterInit(PULSE_LOG_COUNT, FLEX_PCNT_DEFAULT_OPTIONS)) {
    printf("Failed to initialise pulse counter\n");
    return;
  }
  FLEX_PulseCounterHandlerModify(PulseCounterEvent, FLEX_HANDLER_MODIFY_ADD);
  FLEX_DelayMs(PCNT_STABILISE_DELAY_MS);

  // Initalize pulse count
  uint32_t *init = GetInitPulseCount();
  *init = FLEX_PulseCounterGet();
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
  msg.pulse_counter = ReadPulseCount();

  printf("Scheduled message: %u %lu %ld %ld %u\n",
    msg.sequence_number,
    msg.time,
    msg.latitude,
    msg.longitude,
    msg.pulse_counter);

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
  PulseCounterInit();
  FLEX_JobSchedule(QueueMessage, FLEX_ASAP());
}
