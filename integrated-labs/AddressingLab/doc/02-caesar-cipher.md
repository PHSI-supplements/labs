## Caesar Cipher Function

The first of the three functions is the Caesar Cipher itself.
Here is the equivalent C code:

```c
23. char *caesar_cipher(char *restrict destination, char const *restrict text, int key) {
24.     char *target = destination;
25.     int reduced_character;
26.     while (*text) {
27.         if ('A' <= *text && *text <= 'Z') {
28.             reduced_character = *text - 'A';
29.             reduced_character = (reduced_character + key + 26) % 26;
30.             *target = (char) (reduced_character + 'A');
31.         } else {
32.             *target = *text;
33.         }
34.         target++;
35.         text++;
36.     }
37.     *target = '\0';
38.     return destination;
39. }
```


### Subtract Using an Immediate Operand

[//]: # (Task 1)

In this task, you will insert the assembly instruction that corresponds to line&nbsp;28 and part of line&nbsp;29 in the function's C code.
Specifically, we are combining the `- 'A'` from line 28 with the `key + 26` to create a temporary variable equal to `key + 26 - 'A'`.
The `key` value is initially in register `%edx`;
since we will not need this value again, the assembly instruction can safely overwrite `%edx`.

- [ ] Find the line in *caesarcipher.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 1 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `subl` instruction that subtracts the immediate value `39` from the contents of register `%edx` and places the difference in register `%edx`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Add the Contents of Two Registers

[//]: # (Task 2)

You can now add the value computed in Task&nbsp;1 to the copy of the character previously pointed to by the `text` pointer, as part of line&nbsp;29.
The character is in the `%al` register, and the value from Task&nbsp;1 is in register `%edx`.
In this task,
you will first sign-extend the one-byte character so that it can be added to the 32-byte value,
and then you will perform the addition.

- [ ] Find the line in *caesarcipher.s* that says
  ```asm
  ##### PLACE INSTRUCTIONS FOR TASK 2 ON NEXT TWO LINES #####
  ```
- [ ] On the next line, insert a `movsbl` instruction.
  The source for this instruction is the `%al` register, and the destination is `%eax`.
  - This instruction is like a `mov` instruction except that it *s*ign-extends a *b*yte so that it becomes a *l*ong word (using the IA32 nomenclature that a "long word" occupies 4 bytes).
- [ ] On the next line after that, insert an `addl` instruction to add the contents of `%eax` and `%edx`, leaving the sum in `%eax`.

Do not delete the `##### PLACE INSTRUCTIONS...` comment,
and do not delete or modify any other instructions.


### Store a Value in Memory

[//]: # (Task 3)

The next assembly instruction you will introduce combines part of line&nbsp;30 and line&nbsp;32.
Register `%al` will hold either `(char) (reduced_character+'A')` from line&nbsp;30 or it will hold the character previously pointed to by `text`. 
This character needs to be placed in memory at the address pointed to by the `target` pointer.
Register `%r8` holds that address.

- [ ] Find the line in *caesarcipher.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 3 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movb` instruction to copy the character.
  The source for the instruction is the `%al` register.
  The destination is the memory location pointed to by the `%r8` register;
  that is, you will need to dereference the address in `%r8`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Load a Value from Memory

[//]: # (Task 4)

Now you will load the next character to be enciphered.
This character is pointed to by the `text` pointer, 
and this pointer is in register `%rsi`. 
You will place the character in the 32-bit register `%eax`.

- [ ] Find the line in *caesarcipher.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 4 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movzbl` instruction to copy the character.
  The source for the instruction is the memory location pointed to by `%rsi`,
  and the destination is register `%eax`.
  - `movzbl` is like `movsbl`, except that it *z*ero-extends the byte.
 
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

If the function does not perform correctly go back and double-check each of the six instructions you placed in it.


---

|        [⬅️](01-getting-started.md)         |      [⬆️](../README.md)      |               [➡️](03-capitalization.md)               |
|:------------------------------------------:|:----------------------------:|:------------------------------------------------------:|
|  [Getting Started](01-getting-started.md)  | [Front Matter](../README.md) | [Sentence to Uppercase Function](03-capitalization.md) |
