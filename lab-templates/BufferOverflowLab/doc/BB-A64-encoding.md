## Appendix B: A64 Instruction Encodings

- [Register-register move](#register-register-move)
- [Immediate-register move](#immediate-register-move)
- [Load/Store](#loadstore)
- [Add/Subtract](#addsubtract)
- [Return](#return)
- [No-Op](#no-op)

---

### Register-register move

The core encoding is:

`2A00'03E0`

The register size and register numbers are bitwise-ORed into the instruction:

| bit number |         31         | 30 | 29 | 28 | 27 | 26 | 25 | 24 | 23 | 22 | 21 | 20..16 | 15 | 14 | 13 | 12 | 11 | 10 | 9 | 8 | 7 | 6 | 5 |    4..0     |
|:----------:|:------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:------:|:--:|:--:|:--:|:--:|:--:|:--:|:-:|:-:|:-:|:-:|:-:|:-----------:|
| **value**  | 0=32bit<br>1=64bit | 0  | 1  | 0  | 1  | 0  | 1  | 0  | 0  | 0  | 0  | source | 0  | 0  | 0  | 0  | 0  | 0  | 1 | 1 | 1 | 1 | 1 | destination |

For example, `mov x1, x2` is encoded as `AA02'03E1`.


### Immediate-Register move

When moving immediate values into a register, you can only do so 16 bits at a time.
This is accomplished by placing the lower 16 bits into the register with a `mov` instruction,
and then placing the remaining bits into the register with one or more `movk` ("move-keep") instructions.

For example, placing the value `0x1234'5678'9ABC'DEF0` into register `x0` would be achieved with:
```asm
mov  x0, #0xDEF0
movk x0, #0x9ABC, lsl 16
movk x0, #0x5678, lsl 32
movk x0, #0x1234, lsl 48
```

#### mov

The core encoding is:

`5280'0000`

The register size, destination register number, and left-shift amount are bitwise-ORed into the instruction:

| bit number |         31         | 30 | 29 | 28 | 27 | 26 | 25 | 24 | 23 |  22..21  |         20.. 5         |    4..0     |
|:----------:|:------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--------:|:----------------------:|:-----------:|
| **value**  | 0=32bit<br>1=64bit | 1  | 0  | 1  | 0  | 0  | 1  | 0  | 1  | shift÷16 | 16-bit immediate value | destination |

For example, `mov x0, #0xDEF0` is encoded as `D29B'DE00`.


#### movk

The core encoding is:

`7280'0000`

The register size, destination register number, and left-shift amount are bitwise-ORed into the instruction:

| bit number |         31         | 30 | 29 | 28 | 27 | 26 | 25 | 24 | 23 |                                         22..21                                         |         20..5          |    4..0     |
|:----------:|:------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--------------------------------------------------------------------------------------:|:----------------------:|:-----------:|
| **value**  | 0=32bit<br>1=64bit | 1  | 1  | 1  | 0  | 0  | 1  | 0  | 1  | <u>shift÷16</u><br>00=lsl&nbsp;0<br>01=lsl&nbsp;16<br>10=lsl&nbsp;32<br>11=lsl&nbsp;48 | 16-bit immediate value | destination |

For example, `movk x0, #0x9ABC, lsl 16` is encoded as `F2B3'5780`.


### Load/Store

For simplicity, we discuss only `ldr`/`str` with immediate offsets and no pre/post indexing.
We consider `ldp`/`stp` with and without pre/post indexing.

#### Load/store-register with scaled, unsigned offset

The core encoding of `ldr/str` with scaled, unsigned offset is:

`3900'0000`

The data size, load vs. store, scaled immediate value, and registers are bitwise-ORed into the instruction:

| bit number |                   31..30                    | 29 | 28 | 27 | 26 | 25 | 24 | 23 |       22       |         21..10          |         9..5          |     4..0      |
|:----------:|:-------------------------------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:--------------:|:-----------------------:|:---------------------:|:-------------:|
| **value**  | 00=8bit<br>01=16bit<br>10=32bit<br>11=64bit | 1  | 1  | 1  | 0  | 0  | 1  | 0  | 0=str<br>1=ldr | scaled immediate offset | base address register | data register |

The value encoded in the immediate field is left-shifted by the size of the data (0, 1, 2, 3) to determine the unsigned offset.
Put another way, the offset in the plain-text instruction is right-shifted (logical right-shift) by the size of the data.
Because the immediate value is unsigned, only non-negative offsets can be used with these instructions
For our purposes in this assignment, the size will be 2 (4 bytes) or 3 (8 bytes).

For example, `ldr w1, [x2, 32]` is encoded as `B940'2041`


#### Load/store-register with unscaled, signed offset

The core encoding of `ldur`/`stur` (aka `ldr`/`str`), with unscaled, signed offset is:

`B800'0000`

The data size, load vs. store, unscaled immediate value, and registers are bitwise-ORed into the instruction:

| bit number |                   31..30                    | 29 | 28 | 27 | 26 | 25 | 24 | 23 |        22        | 21 |      20..12      | 11 | 10 |         9..5          |     4..0      |
|:----------:|:-------------------------------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:--:|:----------------:|:--:|:----------------:|:--:|:---|:---------------------:|:-------------:|
| **value**  | 00=8bit<br>01=16bit<br>10=32bit<br>11=64bit | 1  | 1  | 1  | 0  | 0  | 0  | 0  | 0=stur<br>1=ldur | 0  | immediate offset | 0  | 0  | base address register | data register |

The value encoded in the immediate field is *not* left-shifted.
Put another way, the offset in the plain-text instruction is encoded directly into the immediate field.
Because the immediate value is signed, both negative and non-negative offsets can be used with these instructions.
An `ldr`/`str` instruction with a negative offset will be encoded as `ldur`/`stur`.
For our purposes in this assignment, the size will be 2 (4 bytes) or 3 (8 bytes).

For example, `ldr w1, [x2, -32]` will be encoded as `ldur w1, [x2, -32]`, which is `B85E'0041`


#### Load/store-pair with scaled, signed offset

The core encoding of `ldp`/`stp` is:

`2800'0000`

The data size, index direction, load vs. store, scaled immediate value, and registers are bitwise-ORed into the instruction:

| bit number |         31         | 30 | 29 | 28 | 27 | 26 | 25 |                        24..23                         |       22       |         21..15          |     14..10     |         9..5          |      4..0      |
|:----------:|:------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:-----------------------------------------------------:|:--------------:|:-----------------------:|:--------------:|:---------------------:|:--------------:|
| **value**  | 0=32bit<br>1=64bit | 0  | 1  | 0  | 1  | 0  | 0  | 10=offset_only<br>11=pre_indexing<br>01=post_indexing | 0=stp<br>1=ldp | scaled immediate offset | data register2 | base address register | data register1 |

The value encoded in the immediate field is left-shifted by the size of the data (2 or 3) to determine the unsigned offset.
Put another way, the offset in the plain-text instruction is right-shifted (logical right-shift) by the size of the data.
Because the immediate value is signed, both negative and non-negative offsets can be used with these instructions.

Examples:

| Notional Use  |       Instruction       |  Encoding   |
|:-------------:|:-----------------------:|:-----------:|
| Simple access | `ldp w1, w4, [x2, 32]`  | `2944'1041` |
|     Push      | `stp x1, x4, [x2, 16]!` | `A981'1041` |
|      Pop      | `ldp x1, x4, [x2], 16`  | `A8C1'1041` |


### Add/Subtract

#### Add/subtract register-register

The core encoding is:

`8B00'0000`

The register numbers and instruction options are bitwise-ORed into the instruction.

If Source2 can be a sign/zero-extended, left-shifted register:

| bit number |         31         |       30       |              29              | 28 | 27 | 26 | 25 | 24 | 23..22 | 21  |         20..16          |                                                15..13                                                |                    12..10                    |          9..5          |            4..0            |
|:----------:|:------------------:|:--------------:|:----------------------------:|:--:|:--:|:--:|:--:|:--:|:------:|:---:|:-----------------------:|:----------------------------------------------------------------------------------------------------:|:--------------------------------------------:|:----------------------:|:--------------------------:|
| **value**  | 0=32bit<br>1=64bit | 0=add<br>1=sub | 0=no_flags<br>1=update_flags | 0  | 1  | 0  | 1  | 1  |   00   |  1  | source2<br>(may be xzr) | 000=UXTB<br>001=UXTH<br>010=LSL/UXTW<br>011=LSL/UXTX<br>100=SXTB<br>101=SXTH<br>110=SXTW<br>111=SXTX | shift_amount 0-4:<br>000, 001, 010, 011, 100 | source1<br>(may be sp) | destination<br>(may be sp) |

If Source2 can be an unextended, left-shifted register:

| bit number |         31         |       30       |              29              | 28 | 27 | 26 | 25 | 24 |           23..22           | 21 |         20..16          |      15..10       |          9..5           |            4..0             |
|:----------:|:------------------:|:--------------:|:----------------------------:|:--:|:--:|:--:|:--:|:--:|:--------------------------:|:--:|:-----------------------:|:-----------------:|:-----------------------:|:---------------------------:|
| **value**  | 0=32bit<br>1=64bit | 0=add<br>1=sub | 0=no_flags<br>1=update_flags | 0  | 1  | 0  | 1  | 1  | 00=LSL<br>01=LSR<br>10=ASR | 0  | source2<br>(may be xzr) | shift_amount 0-63 | source1<br>(may be xzr) | destination<br>(may be xzr) |

#### Add/subtract register-immediate

The core encoding is:

`9100'0000`

The register numbers, immediate value, and instruction options are bitwise-ORed into the instruction:

| bit number |         31         |       30       |              29              | 28 | 27 | 26 | 25 | 24 | 23 |               22                |     21..10      |          9..5          |            4..0            |
|:----------:|:------------------:|:--------------:|:----------------------------:|:--:|:--:|:--:|:--:|:--:|:--:|:-------------------------------:|:---------------:|:----------------------:|:--------------------------:|
| **value**  | 0=32bit<br>1=64bit | 0=add<br>1=sub | 0=no_flags<br>1=update_flags | 1  | 0  | 0  | 0  | 1  | 0  | 0=LSL&nbsp;#0<br>1=LSL&nbsp;#12 | immediate value | source1<br>(may be sp) | destination<br>(may be sp) |


### Return

The encoding for `ret` is:

`D65F'03C0`


### No-Op

The encoding for `nop` is:

`D503'201F`

"Functional NOP" instructions also exist, such as `add x0, x0, xzr`.


---

|              [⬅️](CC-x86-64-encoding.md)              |      [⬆️](../README.md)      |                           |
|:-----------------------------------------------------:|:----------------------------:|:-------------------------:|
| [x86-64 Instruction Encodings](CC-x86-64-encoding.md) | [Front Matter](../README.md) |                           |
