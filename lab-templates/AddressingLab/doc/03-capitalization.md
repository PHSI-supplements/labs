## Sentence to Uppercase Function

The second of the three functions converts lowercase letters in a sentence to uppercase letters.
Here is the equivalent C code:

```c
41. char *sentence_to_uppercase(char *restrict destination, char const *restrict sentence) {
42.     size_t length = strlen(sentence);
43.     for (size_t i = 0; i < length; i++) {
44.         destination[i] = (char) toupper(sentence[i]);
45.     }
46.     return destination;
47. }
```

Both tasks for this function are for line&nbsp;44.


### Index Arrays as the Source

[//]: # (Task 5)

Your next task is to convert lowercase letters to uppercase letters. 
As an efficiency gain, the repeated calls to `toupper` on line&nbsp;44 have been replaced with a lookup table. 
The base address for the `sentence` array is in `%r15`; 
the base address for the lookup table is in `%rcx`, 
and the loop index `i` is in `%rbx`.

- [ ] Find the line in *caesarcipher.s* that says
  ```asm
  ##### PLACE INSTRUCTIONS FOR TASK 5 ON NEXT TWO LINES #####
  ```
- [ ] On the next line, insert a `movsbq` instruction.
  The source is a location in the `sentence` array: use the indexed addressing mode.
  The base address is `%r15`;
  the index is `%rbx`, and each array element is 1 byte.
  The destination for this instruction is `%rdx`.
  - `movsbq` is like `movsbl` except that it sign-extends the byte so that it becomes a *q*uad word (using the AMD64 nomenclature that a ``quad word'' occupies 8 bytes).

On the next line after that you will use the `toupper` lookup table.
To preserve the illusion that the program called the `toupper` function, the lookup table stores integers (`toupper`'s specification states that it returns an `int`).
- [ ] Insert a `movzbl` instruction. 
  The source is a location in the lookup table array: use the indexed addressing mode. 
  The base address is `%rcx`; 
  the index is the character from the previous instruction in `%rdx`,
  and each array element is 4 bytes in size. The destination for this instruction is `%ecx`.

Do not delete the `##### PLACE INSTRUCTIONS...` comment,
and do not delete or modify any other instructions.


### Index an Array as the Destination

[//]: # (Task 6)

The other part of line&nbsp;44 is casting the integer from Task&nbsp;5 to a
`char` and storing it in the `destination` array. 
The array's base address is in `%r14`, and as before the loop index is in `%rbx`.

- [ ] Find the line in *caesarcipher.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 6 ON NEXT LINE #####
  ```
- [ ] On the next line, use a `movb` instruction to move the lower 8 bits of the integer into the `destination` array. 
  The instruction's source is `%cl`,
  and the destination is a location in the array. 
  The array's base address is `%r14`; the index is `%rbx`, 
  and each array element is 1 byte.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Check Your Work

- [ ] Compile and run *addressinglab*.
- [ ] Select option 2, "sentence_to_uppercase + caesar_cipher".
- [ ] Test your code with plaintext "ZebrA" and the key `1`; the ciphertext should be "AFCSB".
- [ ] Try a few other plaintext strings and keys.

If the function does not perform correctly go back and double-check each of the three instructions you placed in it.


---

|           [⬅️](02-caesar-cipher.md)           |      [⬆️](../README.md)      |             [➡️](04-cipher-validation.md)             |
|:---------------------------------------------:|:----------------------------:|:-----------------------------------------------------:|
| [Caesar Cipher Function](02-caesar-cipher.md) | [Front Matter](../README.md) | [Cipher Validation Function](04-cipher-validation.md) |
