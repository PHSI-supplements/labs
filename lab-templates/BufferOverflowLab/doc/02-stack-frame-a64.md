## What Does the Stack Frame Look Like?

> 🧩 **Note the Instruction Set**
>
> Use these instructions if your environment's instruction set architecture is the **A64** ISA.

When conducting your attack, you will need to know how much space there is between the beginning of the input buffer and the return address that you will overwrite.
You will also need to honor any byte-alignment requirements required by the system.

This discussion of the AArch64 (A64 Instruction Set) stack should help you with that.

### AArch64 Stack Alignment

At all times, the stack pointer needs to point to an address that is divisible by 16;
this is enforced by the processor.
Function prologues maintain this alignment when allocating space on the stack with either a `stp x29, x30, [sp, imm]!` instruction or with a `sub sp, sp, #imm` instruction:
in either case, the stack pointer will be adjusted by a multiple of 16.

When you craft your input and cause the program to go to the appropriate function, 
you will need to make sure that the stack pointer is aligned to a 16-byte address immediately before the function's address is loaded into register `x30` (aka, `lr`).

Immediately before the call to `get_s`, `get_input`'s stack frame will look like one of these examples, depending on the size of the buffer:

### AArch64 Stack Frame with a Small Buffer

**This is the stack frame that you are most likely to see in BufferOverflowLab, but you should not assume that it is until you examine the function prologue**

If the stack frame isn't too large, then you will likely see code similar to this in the prologue:
```asm
stp x29, x30, [sp, -80]!    // pre-decrement sp, save x29 (fp) at sp, save x30 (lr) at sp+8
mov x29, sp                 // point the frame pointer to the saved frame pointer
str x19, [sp, 16]           // save any other registers above the saved link register
                            // remaining space (in this case, 56 bytes) is available for local variables
```

This will result in the saved return address to the being *below* the buffer -- you won't be able to overflow into it.
However, you *can* overflow into the caller's stack frame and overwrite the return address that the caller saved.

```
higher address  |  Caller's Caller's Frame  |
                | saved link register (x30) |       
                | saved frame pointer (x29) |       (address divisible by 16)
                |---------------------------|
                |      Caller's Frame       |
                | saved link register (x30) |       (address not divisible by 16)
                | saved frame pointer (x29) |       (address divisible by 16)
                |---------------------------|
                | buffer                    |
                |          buffer           |
                |                    buffer |
                |      saved registers      |
                | saved link register (x30) |       (address not divisible by 16)
                | saved frame pointer (x29) | <--sp (address divisible by 16)
lower address   |---------------------------|
```

The buffer might start immediately above the saved registers (in the above example, `sp`+24), or it might start several bytes above that address.
In either case, the `add x0, sp, #imm` instruction shortly before `bl get_s` will tell you where the buffer begins.

When crafting your input,
you will need to consider how many bytes there are between the start of the stack frame,
and where the caller's saved return address is stored in its stack frame.

Any assembly instructions that you inject must be aligned to a 4-byte boundary.

The function's epilogue will ensure that the stack pointer points to the low end of the caller's caller's frame when the `ret` instruction executes.
You should take this into account when injecting data or ROP gadget addresses on the stack.

### AArch64 Stack Frame with a Large Buffer, possibility 1

If the stack frame is sufficiently large, then the compiler will allocate the stack frame using a `sub` instruction, due to the limited range possible with pre-decrementing `stp`.
In this case, you will likely see code similar to this in the prologue:
```asm
sub sp, sp, #576            // allocate the stack frame
stp x29, x30, [sp]          // save x29 (fp) at sp, save x30 (lr) at sp+8
mov x29, sp                 // point the frame pointer to the saved frame pointer
str x19, [sp, 16]           // save any other registers above the saved link register
                            // remaining space (in this case, 56 bytes) is available for local variables
```

The resulting stack frame and considerations are the same as the "small buffer" case.

### AArch64 Stack Frame with a Large Buffer, possibility 2

Depending on the placement of the local variables in the stack frame, the compiler may generate code that will point the frame pointer to the opposite end of the stack frame than the stack pointer so that the frame pointer can be used as the base address register when addressing some variables on the stack.
In this case, you will likely see code similar to this in the prologue:
```asm
sub sp, sp, #304            // allocate the stack frame
stp x29, x30, [sp, 272]     // save x29 (fp) at or near the high end of the frame, and x30 (sp) eight bytes above that
add x29, sp, 272            // point the frame pointer to the saved frame pointer
str x19, [sp, 288]          // save any other registers above the saved link register
                            // remaining space (in this case, 272 bytes) is available for local variables
```

This will place the buffer below the saved return address, and you will be able to overflow into it.

```
higher address  |      Caller's Frame       |       (address divisible by 16)
                |---------------------------|
                |      saved registers      |
                | saved link register (x30) |       (address not divisible by 16)
                | saved frame pointer (x29) | <--fp (address divisible by 16)
                | buffer                    |
                |          buffer           |
                |                    buffer | <--sp (address divisible by 16)
lower address   |---------------------------|
```

The buffer might start at the address pointed to by `sp`, or it might start a few bytes above that address.
For example, if you see `mov x0, sp` shortly before `bl get_s`, then that copies the stack pointer into register `x0`, indicating that the buffer starts at the address pointed to by `sp`.
On the other hand, `add x0, sp, #4` computes an address four bytes above that address, indicating that the buffer starts there.

When crafting your input,
you will need to consider how many bytes there are between the start of the buffer and the start of the saved frame pointer,
and how much space is used by the frame pointer register (8 bytes).

Any assembly instructions that you inject must be aligned to a 4-byte boundary.

The function's epilogue will ensure that the stack pointer points to the low end of the caller's frame when the `ret` instruction executes.
You should take this into account when injecting data or ROP gadget addresses on the stack.


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                      [➡️](03-stage0.md)                      |
|:----------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Stage 0: Simple Buffer Overflow on the Stack](03-stage0.md) |
