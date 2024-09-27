# Pulse Counter v1.2.0
A reference app that reports the pulses count by the FlexSense device. The pulse counter value reported is cumulative and overflows (and resets back to 0) after counting up to 65535.

## Message Payload Format

| Byte Offset | Content | Type | Description |
| ----------- | ------- | ---- | ----------- |
| 0 | Sequence Number | uint8 | The sequence number of the message, i.e. message count. Note that the message counter is shared between all message types. |
| 1 - 5 | Time | uint32 | The Unix time at which the message is created. |
| 5 - 9 | Latitude | int32 | The latitude of the device recorded on the last call to `FLEX_GNSSFix` scaled by `1e7`. For example a received latitude value of `-891234567` is actually `-89.1234567`. |
| 9 - 13 | Longitude | int32 | The longitude of the device recorded on the last call to `FLEX_GNSSFix` scaled by `1e7`. For example a received longitude value of `1386073300` is actually `138.6073300`. |
| 13 - 15 | Pulse Counter | uint16 | The number of pulse that have been counted by the FlexSenses pulse counter. |

## Wiring Diagram
![Pulse Counter](../wiring_diagrams/pulse-counter.svg)

