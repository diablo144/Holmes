#!/usr/bin/env python3
"""Build a valid, non-exporting Riftcap v2 capsule."""

from __future__ import annotations

import struct
from pathlib import Path

CODE_ADDRESS = 0x500000000000
CODE_OFFSET = 0x1000
UNWIND_OFFSET = 0x2000
DATA_OFFSET = 0x3000
DATA_SIZE = 0x700
FIXUP_OFFSET = 0x4000
TOTAL_SIZE = 0x5000

GATE_CODE = bytes.fromhex(
    "f3 0f 1e fa 48 83 ec 08 41 ff d5 48 83 c4 08 c3"
)


def safe_eh_frame() -> bytes:
    frame = bytearray(68)
    struct.pack_into("<II", frame, 0x00, 0x14, 0)
    frame[0x08:0x16] = bytes([
        1, ord("z"), ord("R"), 0, 1, 0x78, 16, 1, 0,
        0x0C, 7, 8, 0x90, 1,
    ])
    struct.pack_into("<IIQQ", frame, 0x18,
                     0x24, 0x1C, CODE_ADDRESS, len(GATE_CODE))
    frame[0x30:0x3A] = bytes([
        0, 0x48, 0x0E, 16, 0x10, 12, 3, 0x7F, 0x80, 0x02,
    ])
    return bytes(frame)


def build() -> bytes:
    result = bytearray(TOTAL_SIZE)
    result[:80] = struct.pack(
        "<8s12I24s",
        b"RIFTCAP\0", 2, TOTAL_SIZE,
        CODE_OFFSET, len(GATE_CODE),
        UNWIND_OFFSET, len(safe_eh_frame()),
        DATA_OFFSET, DATA_SIZE,
        FIXUP_OFFSET, 0,
        0, 0, bytes(24),
    )
    result[CODE_OFFSET:CODE_OFFSET + len(GATE_CODE)] = GATE_CODE
    frame = safe_eh_frame()
    result[UNWIND_OFFSET:UNWIND_OFFSET + len(frame)] = frame
    return bytes(result)


if __name__ == "__main__":
    output = Path(__file__).with_name("sample.rcap")
    output.write_bytes(build())
    print(output)
