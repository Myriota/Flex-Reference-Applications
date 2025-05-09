# Tracker v1.3.0

A reference app to demonstrate location reporting over the Myriota satellite network.

## Operation

The application uses the GNSS receiver onboard the FlexSense
to fetch and report the location of the device. A GNSS fix
will be performed before every satellite message is sent. The
device also reports the internal temperature of the
FlexSense.

> [!IMPORTANT] Performing GNSS fixes has a relatively high energy usage.
> Firmware configurations with high message rates (and therefore frequent GNSS
> fixes) will have reduced battery life.

## Message Payload Format

| Byte Offset | Content | Type | Description |
| ----------- | ------- | ---- | ----------- |
| 0 | Sequence Number | uint8 | The sequence number of the message, i.e. message count. |
| 1 - 4 | Time | uint32 | The time of the location reading in [UTC](https://en.wikipedia.org/wiki/Coordinated_Universal_Time) time. This is in [Unix time](https://en.wikipedia.org/wiki/Unix_time) format (also called Epoch time). |
| 5 - 8 | Latitude | int32 | The latitude of the device scaled by `1e7`. For example a received latitude value of `-891234567` is actually `-89.1234567`. |
| 9 - 12 | Longitude | int32 | The longitude of the device scaled by `1e7`. For example a received longitude value of `1386073300` is actually `138.6073300`. |
| 13 - 14 | Onboard Temperature | int16 | The temperature inside the Myriota Module in degrees Celsius scale by 100.  For example a received value of 3000 is actually 30.00 C. |

> [!IMPORTANT]
> Message data types are packed using little endian byte ordering.

