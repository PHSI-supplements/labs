## What Does the Stack Frame Look Like?

When conducting your attack, you will need to know how much space there is between the beginning of the input buffer and the return address that you will overwrite.
You will also need to honor any byte-alignment requirements required by the system.

You should review the stack discussion for your system's architecture.
- [x86-64](#x86-64), such as a typical Windows laptop
- [AArch64 (A64 instruction set)](#aarch64-a64-instruction-set), such as a MacBook or a Windows-on-Arm laptop
- [AArch32 (T32 instruction set)](#aarch32-t32-instruction-set), such as the Cow&nbsp;Pi development board

### AArch32 (T32 Instruction Set)

#### AArch32 Stack Alignment

Conventionally, immediately before a function call, the stack pointer needs to point to an address that is divisible by 8.
Function prologues maintain this alignment when allocating space on the stack with a combination of `push {reg-list}` and/or `sub sp, sp, #imm` instructions.

The prologue will be similar to:
```asm
push {r4, lr}               // save registers in reverse order, placing `lr` at the high end of the frame 
sub  sp, sp, #24            // allocate additional space for local variables
```
The corresponding epilogue would be:
```asm
add  sp, sp, #24            // de-allocate the space used by local variables
pop  {r4, pc}               // restore saved registers in order; the address that had been pushed from `lr` is popped into `pc`
```

When you craft your input and cause the program to go to the appropriate function, 
you will need to make sure that the stack pointer is aligned to an 8-byte address immediately before the function's address is popped into `pc`.

Immediately before the call to `get_s`, `get_input`'s stack frame will look something like this:

#### AArch32 Stack Frame

```
|      Caller's Frame      |       (address divisible by 8)
|--------------------------|
| saved link register (lr) |       (address not divisible by 8)
|     saved registers      |
| buffer                   |
|          buffer          |
|                   buffer | <--sp (address divisible by 8)
|--------------------------|
```

The buffer might start at the address pointed to by `sp`, or it might start a few bytes above that address.
For example, if you see `mov r0, sp` shortly before `bl get_s`, then that copies the stack pointer into register `r0`, indicating that the buffer starts at the address pointed to by `sp`.
On the other hand, `add r0, sp, #4` computes an address four bytes above that address, indicating that the buffer starts there.

When crafting your input,
you will need to consider how many bytes there are between the start of the buffer and the start of the saved registers, 
and how much space is used by the saved registers (each saved register occupies 4 bytes).

Any assembly instructions that you inject must be aligned to a 2-byte boundary.

The functions epilogue will ensure that the stack pointer points to the low end of the caller's frame when the `pop` instruction executes.
You should take this into account when injecting data or ROP gadget addresses on the stack.


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                      [➡️](03-stage0.md)                      |
|:----------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Stage 0: Simple Buffer Overflow on the Stack](03-stage0.md) |
