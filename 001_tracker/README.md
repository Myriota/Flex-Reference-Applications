# Tracker v1.2.1
A reference app that reports on-board temperature and location over Myriota satellite network.

## Message Payload Format

| Byte Offset | Content | Type | Description |
| ----------- | ------- | ---- | ----------- |
| 0 | Sequence Number | uint8 | The sequence number of the message, i.e. message count. Note that the message counter is shared between all message types. |
| 1 - 5 | Time | uint32 | The Unix time at which the message is created. |
| 5 - 9 | Latitude | int32 | The latitude of the device scaled by `1e7`. For example a received latitude value of `-891234567` is actually `-89.1234567`. |
| 9 - 13 | Longitude | int32 | The longitude of the device scaled by `1e7`. For example a received longitude value of `1386073300` is actually `138.6073300`. |
| 13 - 15 | Onboard Temperature | int16 | The temperature inside the Myriota Module in degrees Celsius scale by 100.  For example a received value of 3000 is actually 30.00 C. |


