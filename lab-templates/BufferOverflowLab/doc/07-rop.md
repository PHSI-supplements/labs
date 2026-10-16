## Return-Oriented Programming

In the code injection attacks, you placed instructions on the stack and overwrote a return address with the address of those instructions.
When the option of introducing *new* instructions is not available, a clever attacker might use of *existing* instructions.

In *return-oriented programming*, or *ROP*, you identify **gadgets**.
A gadget is a byte sequence in the program that consists of one or more useful instructions,
followed by zero or more inconsequential instructions (such as `nop`),
followed by code to return to another function
- x86-64: `ret`.
- A64: `ldp x29, x30, [sp], #size-of-frame` followed by `ret`.
<!--
- T32: `pop {list-of-registers, pc}`
-->


Read the ROP discussion for your system's ISA.
- [x86-64](#crafting-a-rop-attack-x86-64)
- [A64](#crafting-a-rop-attack-a64)


### Crafting a ROP Attack (x86-64)

Here is an example of an x86-64 gadget:

```asm
 1009f042:	48 89 f7             	mov    %rsi,%rdi
 1009f045:	0f 1f 04 00          	nopl   (%rax,%rax,1)
 1009f049:	66 90                	xchg   %ax,%ax
 1009f04b:	c3                   	ret
```

The first instruction copies the contents of register `%rsi` into `%rdi`: this has the potential to be useful.
The next instruction is a 4-byte no-op, clearly not an instruction that could foul-up our attack
While not as obvious as an instruction that has `nop` in its mnemonic, the third instruction is a 2-byte no-op
(it exchanges the contents of register `%ax` with that of `%ax`; it is also Intel's recommended 2-byte no-op).
Finally, there is a `ret` instruction.

Now, suppose that you cannot execute instructions on the stack.
You might not even be able to determine the buffer's address *a priori*.
But you do know how much space there is between the start of the buffer and the return address that has been placed on the stack.

After examining the disassembled target, you know what your available gadgets are.
With a little creativity and luck (or with a target that has been intentionally seeded with helpful gadgets),
you can design an attack from the gadgets' useful instructions.

Suppose that your stack initially looks like this:

```
| Caller's Frame  |
|-----------------|
| Return Address  |
| saved registers |
| buffer          |
|     buffer      |
|          buffer | <--rsp
|-----------------|
```

Now suppose that you need three gadgets.
Then you'll craft your attack string so that the stack will look like this:
```
| checkpoint's address  |
| 3rd gadget's address  |
| 2nd gadget's address  |
| 1st gadget's address  |
| filler                |
|      filler           |
|           filler      |
|                filler | <--rsp
|-----------------------|
```

When the vulnerable function is at its `ret` instruction
```
| checkpoint's address  |
| 3rd gadget's address  |
| 2nd gadget's address  |
| 1st gadget's address  | <--rsp
| filler                |
|      filler           |
|           filler      |
|                filler |
|-----------------------|
```
the stack pointer will point to the address of the first gadget.
This means that the program will "return" to the first gadget and execute its useful instruction and its inconsequential no-ops.
When the program reaches the `ret` instruction of the first gadget
```
| checkpoint's address  |
| 3rd gadget's address  |
| 2nd gadget's address  | <--rsp
| 1st gadget's address  |
| filler                |
|      filler           |
|           filler      |
|                filler |
|-----------------------|
```
the stack pointer will point to the address of the second gadget.
Thus, the program will "return" to the second gadget, executing  its useful instruction and its inconsequential no-ops.
When the program reaches the `ret` instruction of the second gadget
```
| checkpoint's address  |
| 3rd gadget's address  | <--rsp
| 2nd gadget's address  |
| 1st gadget's address  |
| filler                |
|      filler           |
|           filler      |
|                filler |
|-----------------------|
```
the stack pointer will point to the address of the third gadget.
And so on.


#### Repurposing Bytes

Consider this x86-64 code snippet that clearly has a gadget:

```asm
1009f19a:	48 8d 34 3c          	lea    (%rsp,%rdi,1),%rsi
1009f19e:	90                   	nop
1009f19f:	c3                   	ret
```

You may be surprised to learn that there are *six* gadgets in that snippet.

Three are obvious:
1. If we want to add the contents of `%rsp` and `%rdi`, and place the sum in `%rsi`, then we can use `0x1009'F19A` as one of our gadget addresses, getting us `leaq (%rsp, %rdi), %rsi`, followed by `nop` and `ret`.
2. If we want to move the address held in `%rsp` by eight bytes, then we can use `0x1009'F19F` as one of our gadget addresses, which does nothing but "return" to the next gadget.
3. Similarly, using `0x1009'F19E` will cause the `nop` to execute, followed by the "returning" to the next gadget.

Because an x86 instruction can begin at any address, we are not limited to the instructions that are explicitly in the code.

4. At `0x1009F19B`, we have the instruction encoded as `8D 34 3C`, or `leal (%rsp, %rdi), %esi` -- followed by `nop` and `ret`.
5. At `0x1009F19C`, we have the instruction encoded as `34 3C`, or `xorb $0x3C, %al` -- followed by `nop` and `ret`.
6. At `0x1009F19D`, we have the instruction encoded as `3C 90`, or `cmpb $0x90, %al` -- followed by `ret`.
   Notice that for this gadget, we used bytes from two of the original instructions!

We have seeded the program with sufficient gadgets that do *not* require repurposing bytes, 
that you will not have difficulty solving stages 3 & 4.


### Crafting a ROP Attack (A64)

Here is an example of an A64 gadget:

```asm
 1009f048:	aa0103e0             	mov    x0, x1
 1009f04c:	d503201f             	nop
 1009f050:	8b1f0000             	add    x0, x0, xzr
 1009f054:	a8c17bfd             	ldp    x29, x30, [sp], #16
 1009f058:	d65f03c0             	ret
```

The first instruction copies the contents of register `x1` into `x0`: this has the potential to be useful.
The next instruction is a no-op, clearly not an instruction that could foul-up our attack.
While not as obvious as an instruction that has a `nop` in its mnemonic, the third instruction is a functional no-op
(it adds the contents of the zero-register, 0, to the contents of `x0` and places the result in `x0`, without setting condition codes).
The next instruction pops the saved frame pointer and return address off of the stack, adjusting the stack pointer by 16 in the process,
and finally, there is a `ret` instruction.

Now, suppose that you cannot execute instructions on the stack.
You might not even be able to determine the buffer's address *a priori*.
But you do know how much space there is between the start of the buffer and the return address that has been placed on the stack.

After examining the disassembled target, you know what your available gadgets are.
With a little creativity and luck (or with a target that has been intentionally seeded with helpful gadgets),
you can design an attack from the gadgets' useful instructions.

Suppose that your stack initially looks like this:

```
|  Caller's Caller's Frame  |
| saved link register (x30) |
| saved frame pointer (x29) |
|---------------------------|
|      Caller's Frame       |
| saved link register (x30) |
| saved frame pointer (x29) |
|---------------------------|
| buffer                    |
|          buffer           |
|                    buffer |
|      saved registers      |
| saved link register (x30) |
| saved frame pointer (x29) | <--sp
|---------------------------|
```

Now suppose that you need three gadgets.
Then you'll craft your attack string so that the stack will look like this
(assuming all of the `ldp` instructions update `sp` by 16):
```
|  checkpoint's address  |
| something to go in x29 |
|  3rd gadget's address  |
| something to go in x29 |
|  2nd gadget's address  |
| something to go in x29 |
|  1st gadget's address  |
| something to go in x29 |
| filler                 |
|      filler            |
|            filler      |
|                 filler | <-sp
|------------------------|
```

After the vulnerable function returns to its caller
```
|  checkpoint's address  |
| something to go in x29 |
|  3rd gadget's address  |
| something to go in x29 |
|  2nd gadget's address  |
| something to go in x29 |
|  1st gadget's address  |
| something to go in x29 | <-sp
| filler                 |
|      filler            |
|            filler      |
|                 filler |
|------------------------|
```
the stack pointer will point the first pair of values to pop into registers `x29` and `x30`.
This means that the next `ldp; ret` pair of instructions will place *something* in `x29` and the first gadget's address in `x30`,
and then the program will "return" to the first gadget and execute its useful instruction and its inconsequential no-ops.
When the program reaches the `ldp; ret` instructions of the first gadget
```
|  checkpoint's address  |
| something to go in x29 |
|  3rd gadget's address  |
| something to go in x29 |
|  2nd gadget's address  |
| something to go in x29 | <-sp
|  1st gadget's address  |
| something to go in x29 |
| filler                 |
|      filler            |
|            filler      |
|                 filler |
|------------------------|
```
the stack pointer will point to the second pair of values to pop into registers `x29` and `x30`.
Thus, the program will pop these into `x29` and `x30` and then "return" to the second gadget, executing  its useful instruction and its inconsequential no-ops.
When the program reaches the `ldp; ret` instructions of the second gadget
```
|  checkpoint's address  |
| something to go in x29 |
|  3rd gadget's address  |
| something to go in x29 | <-sp
|  2nd gadget's address  |
| something to go in x29 |
|  1st gadget's address  |
| something to go in x29 |
| filler                 |
|      filler            |
|            filler      |
|                 filler |
|------------------------|
```
the stack pointer will point to the third pair of values to pop into registers `x29` and `x30`.
And so on.


[//]: # (TODO: describe ROP attack for T32)
<!--
```asm
 1009f048:	4608                 	mov    r0, r1
 1009f04a:	f3af 8000            	nop.w
 1009f04e:	46c0                 	nop			; (mov r8, r8)
 1009f050:	bd10                 	pop    {r4, pc}
```
-->


---

|                      [⬅️](06-stage2.md)                      |      [⬆️](../README.md)      |                             [➡️](08-stage3.md)                             |
|:------------------------------------------------------------:|:----------------------------:|:--------------------------------------------------------------------------:|
| [Stage 2: Code Injection with String Argument](06-stage2.md) | [Front Matter](../README.md) | [Stage 3: Return_oriented Programming with Integer Argument](08-stage3.md) |
