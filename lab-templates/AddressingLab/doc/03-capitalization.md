## Sentence to Uppercase Function

> ⓘ **Note**
>
> If you are editing caesarcipher-x86-64-linux.s, follow the instructions for **x86-64**.
> If you are editing caesarcipher-A64-linux.s or caesarcipher-A64-macos.s, follow the instructions for **A64**.

The second of the three functions converts lowercase letters in a sentence to uppercase letters.
Here is the equivalent C code:

```c
46. char *sentence_to_uppercase(char *restrict destination, char const *restrict sentence) {
47.     size_t length = strlen(sentence);
48.     for (size_t i = 0; i < length; i++) {
49.         destination[i] = (char) toupper(sentence[i]);
50.     }
51,     destination[length] = '\0';
52.     return destination;
53. }
```

All three tasks for this function are for line&nbsp;49 of the C code.

As an efficiency gain, the repeated calls to `toupper` on line&nbsp;49 have been replaced with a lookup table.
```c
int upper[] = {...};
destination[i] = (char) upper[sentence[i]];
```

### Load a Character from an Array

[//]: # (Task 6)

#### x86-64
First you need to load the character to be capitalized.
The base address for the `sentence` array is in `%rbx`.
The loop index `i` is in `%rcx`.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 6 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movzbq` instruction.
  The source is a location in the `sentence` array: use the indexed addressing mode.
  The base address is `%rbx`;
  the index is `%rcx`, 
  and each array element is 1 byte.
  The destination for this instruction is `%rdx`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.

#### A64
First you need to load the character to be capitalized.
The base address for the `sentence` array is in `x21`.
The loop index `i` is in `x10`.

- [ ] Find the line in *caesarcipher-A64-linux.s* or *caesarcipher-A64-macos.s* (as appropriate) that says
  ```asm
  //// PLACE INSTRUCTION FOR TASK 6 ON NEXT LINE ////
  ```
- [ ] On the next line, insert a `ldrb` instruction.
  The source is a location in the `sentence` array: use the indexed addressing mode.
  The base address is `x21`;
  the index is `x10`, 
  and each array element is 1 byte.
  The destination for this instruction is `w11`.

Do not delete the `///// PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Load an Integer from an Array

[//]: # (Task 7)

You'll now use the character loaded in the previous task as the index to an array.
To preserve the illusion that the program called the `toupper` function, the lookup table stores integers (`toupper`'s specification states that it returns an `int`).

#### x86-64
- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 7 ON NEXT LINE #####
  ```
- [ ] On the next line, insert a `movl` instruction.
  The source is a location in the lookup table array: use the indexed addressing mode.
  The base address is `%r8`;
  the index is the character from the previous task in `%rdx`,
  and each array element is 4 bytes in size.
  The destination for this instruction is `%edx`.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.

#### A64
- [ ] Find the line in *caesarcipher-A64-linux.s* or *caesarcipher-A64-macos.s* (as appropriate) that says
  ```asm
  ///// PLACE INSTRUCTION FOR TASK 7 ON NEXT LINE /////
  ```
- [ ] On the next line, insert a `ldr` instruction.
  The source is a location in the lookup table array: use the indexed addressing mode.
  The base address is `x12`;
  the index is the character from the previous task in `w11`,
  and each array element is 4 bytes in size.
  The destination for this instruction is `w12`.
  - When you provide the shift, use `uxtw` instead of `lsl`.
    The `uxtw` modifier will perform the shift just the same as `lsl`, except that it will extend `w11` into `x11` so that the index is specified as a 64-bit value.

Do not delete the `///// PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.


### Store a Character to an Array

#### x86-64
The final part of line&nbsp;49 is casting the integer from Task 7 to a `char` and storing it in the `destination` array.
The array's base address is in `%rbp`, and as before, the loop index is in `%rcx`.

- [ ] Find the line in *caesarcipher-x86-64-linux.s* that says
  ```asm
  ##### PLACE INSTRUCTION FOR TASK 8 ON NEXT LINE #####
  ```
- [ ] On the next line, use a `movb` instruction to copy the lower 8 bits of the integer into the `destination` array.
  The instruction's source is `%dl`,
  and the destination is a location in the array.
  The array's base address is in `%rbp`; 
  the index is in `%rcx`,
  and each array element is 1 byte.

Do not delete the `##### PLACE INSTRUCTION...` comment,
and do not delete or modify any other instructions.

#### A64
The final part of line&nbsp;49 is casting the integer from Task 7 to a `char` and storing it in the `destination` array.
The array's base address is in `%rbp`, and as before, the loop index is in `%rcx`.

- [ ] Find the line in *caesarcipher-A64-linux.s* or *caesarcipher-A64-macos.s* (as appropriate) that says
  ```asm
  ///// PLACE INSTRUCTION FOR TASK 8 ON NEXT LINE /////
  ```
- [ ] On the next line, use a `strb` instruction to copy the lower 8 bits of the integer into the `destination` array.
  The instruction's data is in `w12`,
  and the destination is a location in the array.
  The array's base address is in `x20`;
  the index is in `x10`,
  and each array element is 1 byte.

Do not delete the `///// PLACE INSTRUCTION...` comment,
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
