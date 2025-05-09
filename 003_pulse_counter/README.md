# Pulse Counter v1.3.0

A reference app demonstrating how to interface to a pulse counter sensor from the FlexSense and send the measurement over the Myriota satellite network.

## Operation

The application configures the FlexSense to count pulses on the Digital I/O 2
interface. The pulse counter value reported is cumulative and overflows (and
resets back to 0) after counting up to 65535. The application uses the onboard
GNSS receiver to report the last known location of the device. A GNSS fix will
be performed once a week.

## Message Payload Format

| Byte Offset | Content | Type | Description |
| ----------- | ------- | ---- | ----------- |
| 0 | Sequence Number | uint8 | The sequence number of the message, i.e. message count. |
| 1 - 4 | Time | uint32 | The time of the location reading in [UTC](https://en.wikipedia.org/wiki/Coordinated_Universal_Time) time. This is in [Unix time](https://en.wikipedia.org/wiki/Unix_time) format (also called Epoch time). |
| 5 - 8 | Latitude | int32 | The latitude of the device recorded on the last call to `FLEX_GNSSFix` scaled by `1e7`. For example a received latitude value of `-891234567` is actually `-89.1234567`. |
| 9 - 12 | Longitude | int32 | The longitude of the device recorded on the last call to `FLEX_GNSSFix` scaled by `1e7`. For example a received longitude value of `1386073300` is actually `138.6073300`. |
| 13 - 14 | Pulse Counter | uint16 | The number of pulse that have been counted by the FlexSenses pulse counter. |

> [!IMPORTANT]
> Message data types are packed using little endian byte ordering.

## Wiring Diagram

The FlexSense supports pulse counter sensors with a normally open contact
interface (contact closes for the count event). Below is a diagram illustrating
how to interface a pulse counter sensor to the FlexSense.

<p align="center" width="100%">
  <img src="../wiring_diagrams/pulse-counter.svg" alt="Pulse Counter" style="width:60%; height:auto;">
</p>
