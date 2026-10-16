## Stage 1: Code Injection with Integer Argument

> 📇 **Scenario, continued**
>
> The PA system is now active.
> Veterinarian Connie D. Shun reminds you that if the megafauna hear the dinner bell over the zoo's PA system,
> they will return to the feeding pens in their enclosures.
> 
> After digging through the zoo control software's code, you find the `ring_dinner_bell` function.
> On closer examination, you notice that, unlike `activate_pa_system`, the `ring_dinner_bell` function will only work for authorized users.


In stage 1, you want to cause the program to run the `ring_dinner_bell` function.
This function takes one argument, the integer representation of your student ID.
Your task is not only to cause the program to run `ring_dinner_bell`, but also to make it appear to that function as though you called it with the integer version of your student ID as the argument.

You will need to craft some assembly code that places the integer version of your student ID in the appropriate register.
The machine code corresponding to that assembly code will be part of your attack string.

You will also need the address of your buffer.

> 📝 **Grading Note**
>
> We will look for your attack string in `data/stage1.hex`.


### Obtain the Buffer Address

[//]: # (TODO: alternate instructions for IDE-hosted debuggers)

- [ ] Load `build/target` into `gdb`
- In gdb:
  - [ ] Set a breakpoint at the start of `get_s`
    - `break get_s`
  - [ ] Launch the program, specifying a stage (it does not matter which stage, but a stage must be specified)
    - `run 1`
  - [ ] When the program hits the breakpoint at the start of `get_s`, examine the contents of the first-argument register;
    this is the buffer's address
    - x86-64: `print/x $rdi`
    <!--
    - AArch64: `print/x $x0`
    - AArch32: `print/x $r0`
    -->

  
### Construct Your Attack

- [x86-64](#x86-64)
- [A64](#a64)


#### x86-64

- [ ] Write one or more assembly instructions and identify data (if any) & addresses that you need on the stack so that:
  - The 32-bit integer version of your student ID will be in the register used for a function's first argument, `%edi`.
  - Your assembly instructions conclude with a `ret` instruction.
  > 🐛 **Frequently-Made Error**
  >
  > In x86 AT&T Syntax, immediate values must be preceded with a `$`.
  > If you omit the `$`, then the number will be interpreted as a bare address that must be dereferenced.

  > 🧮 **Number-Base Gotcha**
  >
  > If your student ID starts with a leading 0, such as `01234567`, then do *not* include the leading 0 (or 0s).
  > You've already seen that `0b` is the prefix for a binary literal,
  > and `0x` is the prefix for a hexadecimal literal.
  > `0`, without a subsequent letter, is the prefix for an *octal* literal.
  > Because of this, you'd want to use `$1234567` instead of `$01234567`.
  > Alternatively, you can describe the integer as a hexadecimal literal: `$0x12D687`.
- [ ] Determine the bytes for your assembly instructions' machine code
  - Option 1: [Use tools](AA-assemble-disassemble.md)
  - Option 2: [Encode the instructions by hand](BB-x86-64-encoding.md)
- [ ] Construct your attack string so that:
  - The bytes for your attack code begin at the start of the buffer.
  - There is padding to fill the rest of the stack frame.
  - The original return address with the buffer's address so that the program "returns" to code that you will place in the buffer.
  - The data (if any) that you need on the stack will be where your instructions need it.
  - `ring_dinner_bell`'s address is positioned so that when the `ret` in your attack code executes, the program will "return" to `ring_dinner_bell`.
  - Data and addresses in your attack string are byte-reversed.
- [ ] Save your attack string in `stage1.hex`

[//]: # (A little less clear, but a one-liner that already has Arm instructions byte-reversed: `gcc -c -Wa,-alh stageN.s -o /dev/null`)


#### A64

- [ ] Write one or more assembly instructions and identify data (if any) & addresses that you need on the stack so that:
  - The 32-bit integer version of your student ID will be in the register used for a function's first argument, `w0`.
  - `ring_dinner_bell`'s address in register `x30` (aka, `lr`) so that when the `ret` in your attack code executes, the program will "return" to `ring_dinner_bell`.
  - Your assembly instructions conclude with a `ret` instruction.
  > ⚙️ **A64 Assembly Code Detail**
  >
  > If your assembly code uses `mov` to place data in a register, note that move-immediate can only move 16 bytes.
  > For a 32-bit or 64-bit value, you will need to combine `mov` with `movk`.
  > There is an example in this assignment's [Appendix C](CC-A64-encoding.md#immediate-register-move).
  
  > 🧮 **Number-Base Gotcha**
  >
  > If a decimal immediate value starts with a leading 0, such as `01234567`, then do *not* include the leading 0 (or 0s).
  > You've already seen that `0b` is the prefix for a binary literal,
  > and `0x` is the prefix for a hexadecimal literal.
  > `0`, without a subsequent letter, is the prefix for an *octal* literal.
  > Because of this, you'd want to use `#12345` instead of `#012345`.
  > Alternatively, you can describe the integer as a hexadecimal literal: `#0x3039`,
  > which will also be useful when partitioning the valut into two-byte chunks. 
  > (You may omit `#` because gcc treats the `#` marker as optional.)

  > 😖 **Avoid Frustration**
  >
  > If your assembly code places any data in the caller's frame *other than overwriting the return address*, be mindful that `caller` will overwrite four bytes in its stack.
  > Review `caller`'s assembly code in `data/target.d` to identify which bytes these are, and do not place anything in those bytes that you need for your attack.
- [ ] Determine the bytes for your assembly instructions' machine code
  - Option 1: [Use tools](AA-assemble-disassemble.md)
  - Option 2: [Encode the instructions by hand](CC-A64-encoding.md)
- [ ] Construct your attack string so that:
  - The bytes for your attack code begin at the start of the buffer.
  - There is padding to fill the rest of the stack frame.
  - The original return address with the buffer's address so that the program "returns" to code that you will place in the buffer.
  - The data (if any) that you need on the stack will be where your instructions need it.
  - Instructions, data, and addresses in your attack string are byte-reversed.
  > 😖 **Avoid Frustration, repeated for emphasis**
  >
  > If the return address that you need to overwrite is in `caller`'s stack frame (instead of `get_input`'s frame),
  > then examine `caller`'s assembly code to note what changes are made to the stack and to the stack pointer.
  > Do not place data at locations that will be overwritten!
  > Take the change to `sp` into account when planning data locations and/or offsets from `sp`.
- [ ] Save your attack string in `stage1.hex`


<!--
#### T32

[//]: # (TODO: discuss the limits of `mov`, and update the number-base gotcha accordingly)

- [ ] Write one or more assembly instructions and identify data (if any) & addresses that you need on the stack so that:
  - The 32-bit integer version of your student ID will be in the register used for a function's first argument, `r0`.
  > 🧮 **Number-Base Gotcha**
  >
  > If your student ID starts with a leading 0, such as `01234567`, then do *not* include the leading 0 (or 0s).
  > You've already seen that `0b` is the prefix for a binary literal,
  > and `0x` is the prefix for a hexadecimal literal.
  > `0`, without a subsequent letter, is the prefix for an *octal* literal.
  > Because of this, you'd want to use `#1234567` instead of `#01234567`.
  > Alternatively, you can describe the integer as a hexadecimal literal: `#0x12D687`.
  > (You may omit `#` because gcc treats the `#` marker as optional.)
  - Your assembly instructions conclude with either a `ret` instruction or a `pop` instruction
    - If your instructions conclude with `ret`, then include code to place `ring_dinner_bell`'s address in register `r14` (aka, `lr`) so that when the `ret` in your attack code executes, the program will "return" to `ring_dinner_bell`.
    - If your instructions conclude with `pop`, then be sure that `pc` is one of the `pop` instruction's destinations.
- [ ] Determine the bytes for your assembly instructions' machine code
  - Option 1: [Use tools](AA-assemble-disassemble.md)
  - Option 2: [Encode the instructions by hand](DD-T32-encoding.md)
- [ ] Construct your attack string so that:
  - The bytes for your attack code begin at the start of the buffer.
  - There is padding to fill the rest of the stack frame.
  - The original return address with the buffer's address so that the program "returns" to code that you will place in the buffer.
  - The data (if any) that you need on the stack will be where your instructions need it.
  - If your instructions conclude with `pop`, then be sure that `ring_dinner_bell`'s address is positioned so that when the `pop` in your attack code executes, the program will "return" to `ring_dinner_bell`.
  - Instructions, data, and addresses in your attack string are byte-reversed.
- [ ] Save your attack string in `stage1.hex`
-->


### Conduct Your Attack

- [ ] Use the `hex2raw` tool to convert your attack string into raw bytes,
  and use Unix input/output redirection or piping to send those bytes into the target's input stream.

For example:
```shell
build/hex2raw < data/stage1.hex | build/target 1
```

or
```shell
build/hex2raw < data/stage1.hex > data/stage1.raw
build/target 0 < data/stage1.raw
```


---

|              [⬅️](05-stage1.md)              |      [⬆️](../README.md)      |                      [➡️](06-stage2.md)                      |
|:--------------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [What is Your Student ID?](04-student-id.md) | [Front Matter](../README.md) | [Stage 2: Code Injection with String Argument](06-stage2.md) |
