// Copyright (c) 2021-2024, Myriota Pty Ltd, All Rights Reserved
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
//
// FlexSenese Tagio Payload Parser - "Pulse Counter" 1.2.0

const payload_raw = payload.find(x => x.variable === 'payload_raw' || x.variable === 'payload' || x.variable === 'data');
if (payload_raw) {
    try {
        // Convert the data from Hex to Javascript Buffer.
        const buffer = Buffer.from(payload_raw.value, 'hex');

        // Extract data
        let data = [];
        data.push({ variable: 'sequence_number', value: buffer.readUInt8(0) });
        data.push({ variable: 'time', value: buffer.readUInt32LE(1) });
        data.push({ variable: 'latitude', value: buffer.readInt32LE(5) * 1e-07 });
        data.push({ variable: 'longitude', value: buffer.readInt32LE(9) * 1e-07 });
        data.push({ variable: 'pulse_counter', value: buffer.readUInt16LE(13) });

        payload = payload.concat(data.map(x => ({ ...x })));
    } catch (e) {
        // Print the error to the Live Inspector.
        console.error(e);

        // Return the variable parse_error for debugging.
        payload = [{ variable: 'parse_error', value: e.message }];
    }
}
