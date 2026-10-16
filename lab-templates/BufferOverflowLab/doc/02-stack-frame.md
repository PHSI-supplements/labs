## What Does the Stack Frame Look Like?

When conducting your attack, you will need to know how much space there is between the beginning of the input buffer and the return address that you will overwrite.
You will also need to honor any byte-alignment requirements required by the system.

You should review the stack discussion for your system's architecture.
- [x86-64](#x86-64), such as a typical Windows laptop
- [AArch64 (A64 instruction set)](#aarch64-a64-instruction-set), such as a MacBook or a Windows-on-Arm laptop
<!--
- [AArch32 (T32 instruction set)](#aarch32-t32-instruction-set), such as the Cow&nbsp;Pi development board
-->

### x86-64

#### x86-64 Stack Alignment

Conventionally, immediately before a function call, the stack pointer needs to point to an address that is divisible by 16.
The `call` instruction will push the return address onto the stack, and so the stack pointer will be misaligned when the program enters a function.
One of the jobs of the function prologue is to re-align the stack pointer through a combination of `pushq %reg` and/or `subq #imm, %rsp` instructions.

The prologue will be similar to
```asm
pushq %rbp                  // push registers onto the stack to save their contents
pushq %rbx
subq  $40, %rsp             // allocate additional space for local variables
```
or
```asm
subq  $56, %rsp             // allocate the stack frame
movq  %rbp, 48(%rsp)        // store registers on the stack to save their contents
movq  %rbx, 40(%rsp)
                            // remaining space (in this case, 40 bytes) is available for local variables
```

The function epilogue undoes the work of the prologue, de-allocating space created for local variables and restoring saved registers;
consequently, the stack pointer will point to the return address (which is at an address divisible by 8 but *not* by 16) immediately before the function return.
When the `ret` instruction pops the return address, it will cause the stack pointer to point to an address that *is* divisible by 16 when the program returns to the calling function.

When you craft your input and cause the program to go to the appropriate checkpoint function,
you will need to make sure that after the checkpoint function's prologue, the stack pointer is aligned to a 16-byte address.

#### x86-64 Stack Frame

Immediately before the call to `get_s`, `get_input`'s stack frame will look something like this:

```
higher address  | Caller's Frame  |        (address divisible by 16)
                |-----------------|
                | Return Address  |        (address not divisible by 16)
                | - - - - - - - - |
                | saved registers |
                | buffer          |
                |     buffer      |
                |          buffer | <--rsp (address divisible by 16)
lower address   |-----------------|
```

The buffer might start at the address pointed to by `%rsp`, or it might start a few bytes above that address.
For example, if you see `movq %rsp, %rdi` shortly before `call get_s`, then that copies the stack pointer into register `%rdi`, indicating that the buffer starts at the address pointed to by `%rsp`.
On the other hand, `leaq 4(%rsp), %rdi` computes an address four bytes above that address, indicating that the buffer starts there.

When crafting your input,
you will need to consider how many bytes there are between the start of the buffer and the start of the saved registers (if any),
and how much space is used by the saved registers (each saved register occupies 8 bytes).

There are no alignment requirements for assembly instructions that you inject.

After the `ret` instruction executes, the stack pointer will point to the low end of the caller's frame when the `ret` instruction executes.
You should take this into account when injecting data or ROP gadget addresses on the stack


### AArch64 (A64 Instruction Set)

#### AArch64 Stack Alignment

At all times, the stack pointer needs to point to an address that is divisible by 16;
this is enforced by the processor.
Function prologues maintain this alignment when allocating space on the stack with either a `stp x29, x30, [sp, -imm]!` instruction or with a `sub sp, sp, #imm` instruction:
in either case, the stack pointer will be adjusted by a multiple of 16.

When you craft your input and cause the program to go to the appropriate function, 
you will need to make sure that the stack pointer is aligned to a 16-byte address immediately before the function's address is loaded into register `x30` (aka, `lr`).

Immediately before the call to `get_s`, `get_input`'s stack frame will look like one of these examples, depending on the size of the buffer:

#### AArch64 Stack Frame with a Small Buffer

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

#### AArch64 Stack Frame with a Large Buffer, possibility 1

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

#### AArch64 Stack Frame with a Large Buffer, possibility 2

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


<!--
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
-->


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                      [➡️](03-stage0.md)                      |
|:----------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Stage 0: Simple Buffer Overflow on the Stack](03-stage0.md) |
