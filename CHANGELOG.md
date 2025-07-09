# Changelog

## Flex Reference Applications v1.4.1

* Update Flex SDK dependency to v2.5.0

## Flex Reference Applications v1.4.0

* Update Flex SDK dependency to v2.4.0
* Adds `MESSAGES_PER_DAY` as a configuration value that can be updated via Bluetooth using the FlexAssist mobile application.
* Updates the file extension of the compiled binaries that do not include network info to .nonetwork.bin.

## Flex Reference Applications v1.3.2

* Update Flex SDK dependency to v2.3.1

## Flex Reference Applications v1.3.1

* Update Flex SDK dependency to v2.3.0

## Flex Reference Applications v1.2.2

* Update Flex SDK dependency to v2.2.2

## Flex Reference Applications v1.2.1

* Update Flex SDK dependency to v2.2.1

## Flex Reference Applications v1.2.0

* Fix the `002_sensor_4-20ma` and `003_pulse_counter` application Tago
  'parser.js' files. Both where missing the `Location` field.

* Fix the documented byte offset range for the message payload format for all
  application's README.md files. Byte offset were using open interval notation
  [a, b) and have been updated to use close interval notation [a, b].

* Add a 'time' field to all 'Tago' parsers. The time field has been added to
  allow scheduled time to be displayed on Tago dashboards.

* Add preprocessor `POWER_OUT_VOLTAGE` to define power output voltage in the
  `002_sensor_4-20ma` application.

* Add preprocessor `APP_NAME`, `APP_VERSION`, and `APP_ID` to all reference
  applications for general program legibility.

* General documented improvements:

  - Add improved detail to message payload format field descriptions.

  - Add note about message payload format endianness.

  - Add documentation on how to add message per day configurations.

  - Add documentation on using Tago as a visualisation platform.

  - Add documentation on using `message_store.py` and `unpack.py`

  - Add documentation for where to get pre-built reference application binaries.

## Flex Reference Applications v1.1.1

* Fix synchronize released applications versions to v1.2.1

* Fix indentation of `FLEX_LastLocationAndLastFixTime` in:
  - 002_sensor_4-20ma/main.c
  - 003_pulse_counter/main.c

## Flex Reference Applications v1.1.0

* Update to Flex-SDK v2.1.0

  - Change prefix for applications without network information merged in from
    "_build_key.bin" to ".app.bin"

  - Update pulse_counter to use FLEX_HandlerModifyAction

* Improve payload documentaion for applications in READMEs

* Add wiring diagrams to sensor's and pulse conuter's READMEs

* pulse_counter and sensor_4-20ma now use `FLEX_LastLocationAndLastFixTime`
  instead of `FLEX_GNSSFix` to save battery life.

* Fix error where the order of latitude longitude was incorrect

* Fix error where the order of latitude longitude was incorrect

## Flex Reference Applications v1.1.0

* Initial Release Flex Reference Applications
