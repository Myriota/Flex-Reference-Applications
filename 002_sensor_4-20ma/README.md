# Sensor 4-20ma v1.0.0

## Payload Format

| Message Field | Bytes |
| ------------- | ----- |
| sequence_number | 1 Byte |
| time | 4 Bytes |
| longitude | 4 Bytes |
| latitude | 4 Bytes |
| onboard_temperature | 2 Bytes |
| sensor_current | 2 Bytes |

## Field Descriptions

### Sequence Number

The sequence number of the message, i.e. message count. Note that the message counter is shared between all message types.

### Time

The epoch time at which the message is created.

### Location

The longitude and latitude values both scaled by `1e7`. For example a received latitude value of `-891234567` is actually `-89.1234567`.

### Onboard Temperature

The temperature inside the Myriota Module in degrees Celsius scale by 100.  For example a received value of 3000 is actually 30.00 C.

### Sensor Current

The current of an externally attached sensor. The current sensor reading is in micro-amps (uA).
