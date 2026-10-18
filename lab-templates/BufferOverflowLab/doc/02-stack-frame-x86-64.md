## What Does the Stack Frame Look Like?

> 🧩 **Note the Instruction Set**
>
> Use these instructions if your environment's instruction set architecture is the **x86-64** ISA.

When conducting your attack, you will need to know how much space there is between the beginning of the input buffer and the return address that you will overwrite.
You will also need to honor any byte-alignment requirements required by the system.

This discussion of the x86-64 stack should help you with that.

### x86-64 Stack Alignment

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

### x86-64 Stack Frame

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

---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                      [➡️](03-stage0.md)                      |
|:----------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Stage 0: Simple Buffer Overflow on the Stack](03-stage0.md) |
