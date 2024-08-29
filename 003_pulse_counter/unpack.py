#!/usr/bin/env python3
# -*- coding: utf-8 -*-
# Copyright (c) 2021-2024, Myriota Pty Ltd, All Rights Reserved
# SPDX-License-Identifier: BSD-3-Clause-Attribution
#
# This file is licensed under the BSD with attribution  (the "License"); you
# may not use these files except in compliance with the License.
#
# You may obtain a copy of the License here:
# LICENSE-BSD-3-Clause-Attribution.txt and at
# https://spdx.org/licenses/BSD-3-Clause-Attribution.html
#
# See the License for the specific language governing permissions and
# limitations under the License.


# Unpacker for the FlexSense - "Pulse Counter" 1.0.0
# Usage:
# unpack.py -x <message_data>
# or
# echo "<message_data>" | unpack.py

import argparse
import struct
import json
import fileinput

def unpack(packet):
    sequence_number, time, longitude, latitude, pulse_counter = struct.unpack(
        "<BIiiH", bytearray.fromhex(packet[0:30]))

    return [{
        "Sequence Number": sequence_number,
        "Time": time,
        "Longitude": longitude * 1e-07,
        "Latitude": latitude * 1e-07,
        "Pulse Counter": pulse_counter,
    }]

if __name__ == "__main__":
    parser = argparse.ArgumentParser(
        description="Unpack hexadecimal data from FlexSense - \"Pulse Counter\" 1.0.0",
        formatter_class=argparse.ArgumentDefaultsHelpFormatter,
    )
    parser.add_argument(
        "-x", "--hex", type=str, default="-", help="Packet data in hexadecimal format"
    )
    args = parser.parse_args()

    d = []
    if args.hex == "-":
        for line in fileinput.input():
            d = d + unpack(line.strip())
    else:
        d = d + unpack(args.hex)

    print(json.dumps(d))
