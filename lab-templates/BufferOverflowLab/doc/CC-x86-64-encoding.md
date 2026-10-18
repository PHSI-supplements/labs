## Appendix C: x86-64 Instruction Encodings

To keep the options simple, we will limit the available registers to x86's original eight "named" registers.
Among those eight, the corresponding register numbers are:

| Register | %rax | %rcx | %rdx | %rbx | %rsp | %rbp | %rsi | %rdi |
|---------:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|:----:|
|   Number |  0   |  1   |  2   |  3   |  4   |  5   |  6   |  7   |
|     Bits | 000  | 001  | 010  | 011  | 100  | 101  | 110  | 111  |


- [32-bit register-register move](#32-bit-register-register-move)
- [64-bit register-register move](#64-bit-register-register-move)
- [32-bit immediate-register move](#32-bit-immediate-register-move)
- [64-bit immediate-register move](#64-bit-immediate-register-move)
- [64-bit load](#64-bit-load-move-from-memory-to-register)
- [64-bit store](#64-bit-store-move-from-register-to-memory)
- [64-bit add](#64-bit-add)
- [Load effective address](#load-effective-address)
- [Pop](#pop)
- [Push](#push)
- [Return](#return)
- [No-Op](#no-op)

---

### 32-bit register-register move

The core encoding is:

`89 C0`

The source and destination register numbers are bitwise-ORed into the **second** byte:

| bit7 | bit6 | bits5..3 |  bits2..0   |
|:----:|:----:|:--------:|:-----------:|
|  1   |  1   |  source  | destination |

For example, `movl %ecx, %edx` is encoded as `89 CA`.


### 64-bit register-register move

The core encoding is:

`48 89 C0`

The source and destination register numbers are bitwise-ORed into the **third** byte:

| bit7 | bit6 | bits5..3 |  bits2..0   |
|:----:|:----:|:--------:|:-----------:|
|  1   |  1   |  source  | destination |

For example, `movq %rcx, %rdx` is encoded as `48 89 CA`.


### 32-bit immediate-register move

The core encoding is:

`B8 4-byte-immediate`

The destination register number is bitwise-ORed into the **first** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 |   bits2..0   |
|:----:|:----:|:----:|:----:|:----:|:------------:|
|  1   |  0   |  1   |  1   |  1   | destination  |

The next four bytes are the byte-reversed immediate value.
For example, `movl $320, %ecx` is encoded as `B9 40 01 00 00`.


### 64-bit immediate-register move

#### 4-byte immediate value

The core encoding is:

`48 C7 C0 4-byte-immediate`

The destination register number is bitwise-ORed into the **third** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 |  bits2..0   |
|:----:|:----:|:----:|:----:|:----:|:-----------:|
|  1   |  1   |  0   |  0   |  0   | destination |

The next four bytes are the byte-reversed immediate value.
For example, `movq $320, %rcx` is encoded as `48 C7 C1 40 01 00 00`.

#### 8-byte immediate value

The core encoding is:

`48 B8 8-byte-immediate`

The destination register number is bitwise-ORed into the **second** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 |  bits2..0   |
|:----:|:----:|:----:|:----:|:----:|:-----------:|
|  1   |  0   |  1   |  1   |  1   | destination |

The next eight bytes are the byte-reversed immediate value.
For example, `movabs $0x1234567890, %rcx` is encoded as `48 B9 90 78 56 34 12 00 00 00`.


### 64-bit load (move from memory to register)

#### Base+Displacement (base address register is not %rsp)

The core encodings are:

| displacement<br>size | first<br>byte | second<br>byte | third<br>byte | remaining<br>bytes |
|:--------------------:|:-------------:|:--------------:|:-------------:|:------------------:|
|       0 bytes        |     `48`      |      `8B`      |     `00`      |        n/a         |
|        1 byte        |     `48`      |      `8B`      |     `40`      |  1-byte-immediate  |
|       4 bytes        |     `48`      |      `8B`      |     `80`      |  4-byte-immediate  |

The base address register number and the destination register number are bitwise-ORed into the **third** byte:

|                                bits7..6                                |  bits5..3   |   bits2..0   |
|:----------------------------------------------------------------------:|:-----------:|:------------:|
| 00=no_displacement<br>01=1_byte_displacement<br>10=4_byte_displacement | destination | base address |

#### Base+Displacement (%rsp base address register)

The core encodings are:

| displacement<br>size | first<br>byte | second<br>byte | third<br>byte | fourth<br>byte | remaining<br>bytes |
|:--------------------:|:-------------:|:--------------:|:-------------:|:--------------:|:------------------:|
|       0 bytes        |     `48`      |      `8B`      |     `04`      |      `24`      |        n/a         |
|        1 byte        |     `48`      |      `8B`      |     `44`      |      `24`      |  1-byte-immediate  |
|       4 bytes        |     `48`      |      `8B`      |     `84`      |      `24`      |  4-byte-immediate  |

The base address register number and the destination register number are bitwise-ORed into the **third** byte:

|                                bits7..6                                |  bits5..3   | bit2 | bit1 | bit0 |
|:----------------------------------------------------------------------:|:-----------:|:----:|:----:|:----:|
| 00=no_displacement<br>01=1_byte_displacement<br>10=4_byte_displacement | destination |  1   |  0   |  0   |

#### Base+Index✖️Scale

The core encoding is:

`48 8B 04 00`

The destination register number is bitwise-ORed into the **third** byte:

| bit7 | bit6 |  bits5..3   | bit2 | bit1 | bit0 |
|:----:|:----:|:-----------:|:----:|:----:|:----:|
|  0   |  0   | destination |  1   |  0   |  0   |

The base address register number, the index register number, and the scale are bitwise-ORed into the **fourth** byte:

|                             bits7..6                             |    bits5..3    |       bits2..0        |
|:----------------------------------------------------------------:|:--------------:|:---------------------:|
| <u>scale</u><br>00=1_byte<br>01=2_byte<br>10=4_byte<br>11=8_byte | index register | base address register |


### 64-bit store (move from register to memory)

#### Base+Displacement (base address register is not %rsp)

The core encodings are:

| displacement<br>size | first<br>byte | second<br>byte | third<br>byte | remaining<br>bytes |
|:--------------------:|:-------------:|:--------------:|:-------------:|:------------------:|
|       0 bytes        |     `48`      |      `89`      |     `00`      |        n/a         |
|        1 byte        |     `48`      |      `89`      |     `40`      |  1-byte-immediate  |
|       4 bytes        |     `48`      |      `89`      |     `80`      |  4-byte-immediate  |

The base address register number and the destination register number are bitwise-ORed into the **third** byte:

|                                bits7..6                                |  bits5..3   |   bits2..0   |
|:----------------------------------------------------------------------:|:-----------:|:------------:|
| 00=no_displacement<br>01=1_byte_displacement<br>10=4_byte_displacement | destination | base address |

#### Base+Displacement (%rsp base address register)

The core encodings are:

| displacement<br>size | first<br>byte | second<br>byte | third<br>byte | fourth<br>byte | remaining<br>bytes |
|:--------------------:|:-------------:|:--------------:|:-------------:|:--------------:|:------------------:|
|       0 bytes        |     `48`      |      `89`      |     `04`      |      `24`      |        n/a         |
|        1 byte        |     `48`      |      `89`      |     `44`      |      `24`      |  1-byte-immediate  |
|       4 bytes        |     `48`      |      `89`      |     `84`      |      `24`      |  4-byte-immediate  |

The base address register number and the destination register number are bitwise-ORed into the **third** byte:

|                                bits7..6                                |  bits5..3   | bit2 | bit1 | bit0 |
|:----------------------------------------------------------------------:|:-----------:|:----:|:----:|:----:|
| 00=no_displacement<br>01=1_byte_displacement<br>10=4_byte_displacement | destination |  1   |  0   |  0   |

#### Base+Index✖️Scale

The core encoding is:

`48 89 04 00`

The destination register number is bitwise-ORed into the **third** byte:

| bit7 | bit6 |  bits5..3   | bit2 | bit1 | bit0 |
|:----:|:----:|:-----------:|:----:|:----:|:----:|
|  0   |  0   | destination |  1   |  0   |  0   |

The base address register number, the index register number, and the scale are bitwise-ORed into the **fourth** byte:

|                             bits7..6                             |    bits5..3    |       bits2..0        |
|:----------------------------------------------------------------:|:--------------:|:---------------------:|
| <u>scale</u><br>00=1_byte<br>01=2_byte<br>10=4_byte<br>11=8_byte | index register | base address register |


### 64-bit add

#### Register-register add

The core encoding is:

`48 01 C0`

The source and destination register numbers are bitwise-ORed into the **third** byte:

| bit7 | bit6 | bits5..3 |  bits2..0   |
|:----:|:----:|:--------:|:-----------:|
|  1   |  1   |  source  | destination |

For example, `addq %rcx, %rdx` is encoded as `48 01 CA`.

#### Immediate-register add (1-byte immediate value)

The core encoding is:

`48 83 c0 1-byte-immediate`

The destination register number is bitwise-ORed into the **third** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 |  bits2..0   |
|:----:|:----:|:----:|:----:|:----:|:-----------:|
|  1   |  1   |  0   |  0   |  0   | destination |

For example, `addq $64, %rcx` is encoded as `48 83 c1 40`

#### Immediate-register add (4-byte immediate value, %rax destination)

The encoding is:

`48 05 4-byte-immediate`

#### Immediate-register add (4-byte immediate value, destination is not %rax)

The core encoding is:

`48 81 c0 4-byte-immediate`

The destination register number is bitwise-ORed into the **third** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 |   bits2..0   |
|:----:|:----:|:----:|:----:|:----:|:------------:|
|  1   |  1   |  0   |  0   |  0   | destination  |

For example, `addq $64, %rcx` is encoded as `48 81 c1 40 01 00 00`


### Load effective address

#### Base+Displacement (base address register is not %rsp)

The core encodings are:

| displacement<br>size | first<br>byte | second<br>byte | third<br>byte | remaining<br>bytes |
|:--------------------:|:-------------:|:--------------:|:-------------:|:------------------:|
|       0 bytes        |     `48`      |      `8D`      |     `00`      |        n/a         |
|        1 byte        |     `48`      |      `8D`      |     `40`      |  1-byte-immediate  |
|       4 bytes        |     `48`      |      `8D`      |     `80`      |  4-byte-immediate  |

The base address register number and the destination register number are bitwise-ORed into the **third** byte:

|                                bits7..6                                |  bits5..3   |   bits2..0   |
|:----------------------------------------------------------------------:|:-----------:|:------------:|
| 00=no_displacement<br>01=1_byte_displacement<br>10=4_byte_displacement | destination | base address |

#### Base+Displacement (%rsp base address register)

The core encodings are:

| displacement<br>size | first<br>byte | second<br>byte | third<br>byte | fourth<br>byte | remaining<br>bytes |
|:--------------------:|:-------------:|:--------------:|:-------------:|:--------------:|:------------------:|
|       0 bytes        |     `48`      |      `8D`      |     `04`      |      `24`      |        n/a         |
|        1 byte        |     `48`      |      `8D`      |     `44`      |      `24`      |  1-byte-immediate  |
|       4 bytes        |     `48`      |      `8D`      |     `84`      |      `24`      |  4-byte-immediate  |

The base address register number and the destination register number are bitwise-ORed into the **third** byte:

|                                bits7..6                                |  bits5..3   | bit2 | bit1 | bit0 |
|:----------------------------------------------------------------------:|:-----------:|:----:|:----:|:----:|
| 00=no_displacement<br>01=1_byte_displacement<br>10=4_byte_displacement | destination |  1   |  0   |  0   |

#### Base+Index✖️Scale

The core encoding is:

`48 8D 04 00`

The destination register number is bitwise-ORed into the **third** byte:

| bit7 | bit6 |  bits5..3   | bit2 | bit1 | bit0 |
|:----:|:----:|:-----------:|:----:|:----:|:----:|
|  0   |  0   | destination |  1   |  0   |  0   |

The base address register number, the index register number, and the scale are bitwise-ORed into the **fourth** byte:

|                             bits7..6                             |    bits5..3    |       bits2..0        |
|:----------------------------------------------------------------:|:--------------:|:---------------------:|
| <u>scale</u><br>00=1_byte<br>01=2_byte<br>10=4_byte<br>11=8_byte | index register | base address register |


### Pop

The core encoding is:

`58`

The destination register number is bitwise-ORed into the **first** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 |   bits2..0   |
|:----:|:----:|:----:|:----:|:----:|:------------:|
|  0   |  1   |  0   |  1   |  1   | destination  |

For example, `popq %rcx` is encoded as `59`.


### Push

The core encoding is:

`50`

The source register number is bitwise-ORed into the **first** byte:

| bit7 | bit6 | bit5 | bit4 | bit3 | bits2..0 |
|:----:|:----:|:----:|:----:|:----:|:--------:|
|  0   |  1   |  0   |  1   |  0   |  source  |

For example, `popq %rcx` is encoded as `51`.


### Return

The encoding for `ret` is:

`C3`


### No-Op

These encodings are those recommended by Intel.
You can create other `NOP` encodings by using various addressing modes with `nopw`, `nopl`, and `nopq`.

| 1 byte |     2 bytes     |    3 bytes    |     4 bytes      |         5 bytes         |         6 bytes          |         7 bytes         |            8 bytes             |
|:------:|:---------------:|:-------------:|:----------------:|:-----------------------:|:------------------------:|:-----------------------:|:------------------------------:|
| `nop`  | `xchg %ax, %ax` | `nopl (%rax)` | `nopl 0x0(%rax)` | `nopl 0x0(%rax,%rax,1)` | `nopw 0x0(%rax, %rax,1)` | `nopl 0x00000000(%rax)` | `nopl 0x00000000(%rax,%rax,1)` |
|  `90`  |     `66 90`     |  `0F 1F 00`   |  `0F 1F 40 00`   |    `0F 1F 44 00 00`     |   `66 0F 1F 44 00 00`    | `0F 1F 80 00 00 00 00`  |   `0F 1F 84 00 00 00 00 00`    |


If you have the GNU assembler process these specific instructions, it will optimize some of them to be shorter (for example, `nopl 0x0(%rax)` would become `nopl (%rax)`).
If you write code in assembly and need a `NOP` of a specific length, use `.nops N`, where `N` is the number of bytes, and the GNU assembler will emit the appropriate encoding.

"Functional NOP" instructions also exist, such as `leaq 0(%rax), %rax` and `orl %eax, %eax`.
While these are unlikely to appear intentionally, they can be useful when looking for opportunities to repurpose bytes in a ROP attack.


---

|                      [⬅️](AA-assemble-disassemble.md)                      |      [⬆️](../README.md)      |            [➡️](BB-A64-encoding.md)             |
|:--------------------------------------------------------------------------:|:----------------------------:|:-----------------------------------------------:|
| [Generating Instruction Encodings Using Tools](AA-assemble-disassemble.md) | [Front Matter](../README.md) | [A64 Instruction Encodings](BB-A64-encoding.md) |
