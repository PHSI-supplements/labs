## Caesar Cipher Function

> 🧩 **Note the Instruction Set**
>
> Use these instructions if you are editing *caesarcipher-**x86-64**-linux.s*.

The first of the three functions is the Caesar Cipher itself.
Here is the equivalent C code:

```c
28. char *caesar_cipher(char *restrict destination, char const *restrict text, int key) {
29.     char *target = destination;
30.     int reduced_character;
31.     while (*text) {
32.         if ('A' <= *text && *text <= 'Z') {
33.             reduced_character = *text - 'A';
34.             reduced_character = (reduced_character + key + 26) % 26;
35.             *target = (char) (reduced_character + 'A');
36.         } else {
37.             *target = *text;
38.         }
39.         target++;
40.         text++;
41.     }
42.     *target = '\0';
43.     return destination;
44. }
```


### Copy from One Register to Another

[//]: # (Task 1)

In this task, you will insert the assembly instruction that corresponds to line&nbsp;29.
Specifically, we are making a copy of the `destination` pointer.
Because the `destination` pointer is the function's first argument, it is in register `%rdi` -- this will be the assembly instruction's source.
The assembly instruction's destination will be register `%r9`.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 1 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movq` instruction that copies the contents of register `%rdi` into register `%r9`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Subtract Using an Immediate Operand

[//]: # (Task 2)

In this task, you will insert the assembly instruction that corresponds to line&nbsp;33 in the function's C code.
Specifically, we are mapping the uppercase letters `A`-`Z` to the integer values `0`-`25`.
(In the assembly code, the mapping occurs before the `if` statement, to simplify the `if` condition.)
The character is initially in register `%ecx`, and we will place `reduced_character` in `%ecx` -- `%ecx` will be the instruction's destination.
The mapping is achieved by subtracting `'A'` from the character -- the immediate value `0x41` (or decimal `65`) will be the instruction's source.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 2 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `subl` instruction that subtracts the immediate value `0x41` from the contents of register `%ecx` and places the difference in register `%ecx`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Add the Contents of Two Registers

[//]: # (Task 3)

You can now add the value computed in Task&nbsp;2 to the `key` as part of line&nbsp;34 in the function's C code.
The reduced character is still in register `%ecx`, and we will place the sum in the same register -- `%ecx` will be the instruction's destination.
A copy of `key` is in register `%r8d` -- this will be the instruction's source.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 3 ON NEXT LINE #####
  ```
- [ ] On the next line, insert an `addl` instruction to add the contents of `%ecx` and `%r8d`, leaving the sum in `%ecx`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Store a Value in Memory

[//]: # (Task 4)

The next assembly instruction you will introduce performs part of line&nbsp;35.
Register `%dl` holds `(char) (reduced_character+'A')` from line&nbsp;34. 
This character needs to be placed in memory at the address pointed to by the `target` pointer.
Register `%r9` holds that address.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 4 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movb` instruction to copy the character.
  The source for the instruction is the `%dl` register.
  The destination is the memory location pointed to by the `%r9` register;
  that is, you will need to dereference the address in `%r9`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Load a Value from Memory

[//]: # (Task 5)

Now you will load the next character to be enciphered.
This character is pointed to by the `text` pointer, 
and this pointer is in register `%rsi`. 
You will place the character in the 32-bit register `%eax`.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 5 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movzbl` instruction to copy the character.
  The source for the instruction is the memory location pointed to by `%rsi`,
  and the destination is register `%ecx`.
  - `movzbl` is like a `mov`, except that it *z*ero-extends a *b*yte so that it becomes a *l*ong word (using the x86 nomenclature that a "long word" occupies 4 bytes).
 
Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Check Your Work

> ⓘ **Note**
> 
> The `caesar_cipher()` function will only encipher uppercase letters.
> All other characters will be left unchanged.

- [ ] Compile and run *addressinglab*.
- [ ] Select option 1, "caesar_cipher".
- [ ] Test your code with plaintext "ZEBRA" and the key `1`; the ciphertext should be "AFCSB".
- [ ] Try a few other plaintext strings and keys.

If the function does not perform correctly go back and double-check each of the five instructions you placed in it.


---

|        [⬅️](01-getting-started.md)         |      [⬆️](../README.md)      |               [➡️](03-capitalization-x86-64.md)               |
|:------------------------------------------:|:----------------------------:|:----------------------------------------------------------:|
|  [Getting Started](01-getting-started.md)  | [Front Matter](../README.md) | [Sentence to Uppercase Function](03-capitalization-x86-64.md) |
