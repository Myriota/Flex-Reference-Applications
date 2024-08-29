# Pulse Counter v1.0.0

## Payload Format

| Message Field | Bytes |
| ------------- | ----- |
| sequence_number | 1 Byte |
| time | 4 Bytes |
| longitude | 4 Bytes |
| latitude | 4 Bytes |
| pulse_counter | 2 Bytes |

## Field Descriptions

### Sequence Number

The sequence number of the message, i.e. message count. Note that the message counter is shared between all message types.

### Time

The epoch time at which the message is created.

### Location

The longitude and latitude values both scaled by `1e7`. For example a received latitude value of `-891234567` is actually `-89.1234567`.

### Pulse Counter

The number of pulse that have been counted by the FlexSenses pulse counter.
