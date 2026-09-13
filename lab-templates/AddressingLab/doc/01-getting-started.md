## Getting Started

> 📇 **Scenario**
>
> You've settled into a comfortable routine at the Pleistocene Petting Zoo.
> While your job isn't quite as exciting as that of the saber-toothed tigers' dentist,
> it still has something new and interesting every week.
> 
> Archie announces that he heard that hand-crafted assembly code can be faster than high-level language code.
> You try to explain that while this may have been true decades ago,
> modern optimizing compilers generate code faster than what a typical programmer can achieve with assembly code.
> Archie doesn't believe you and insists that you write the zoo's new cipher program in x86 assembly code.

During your lab period, the TAs will provide a refresher on
the format of x86 assembly instructions and Arm assembly instructions,
of the nomenclature used to specify the operand sizes, 
and of the role of each component of:
- x86's most-general form of memory addressing: $D(R_b, R_i, S)$
- Arm's forms of memory addressing: $[R_b, D]$ \& $[R_b, R_i, \mathrm{lsl}\ s]$.
During the remaining time, the TAs will be available to answer questions.


### Which File Should You Edit?

When you initially configure the project,
CMake will detect your system's environment and identify the specific assembly code file that you should edit.

CMake will create *src/WHICH-FILE-TO-EDIT.txt* that identifies the file you should edit:
```text
Your system was detected as:

    Processor Architecture: XXX
    Operating System:       YYY

EDIT THIS FILE:

    src/caesarcipher-XXX-YYY.s

Editing other assembly code files will have no effect.
```


### Which Set of Instructions Should You Follow?

This assignment includes *02-caesar-cipher*, *03-capitalization*, and *04-cipher-validation* instructions for each available instruction set architecture.
Follow the instructions for your processor's instruction set (`XXX` in the example contents of *src/WHICH-FILE-TO-EDIT.txt*, above)


### Problem Description and Files

The code implements a simple [Caesar Cipher](https://en.wikipedia.org/wiki/Caesar_cipher).
The code consists of three functions:
- The Caesar Cipher function itself,
- A function to capitalize the plaintext, and
- A function to validate "cipher packages," checking for consistency between plaintext and ciphertext

The files are:

#### addressinglab.c

Do not edit *addressinglab.c*.

This file contains the driver code for the lab, as well as a couple of helper functions.

#### caesarcipher.h

Do not edit *caesarcipher.h*.

This header file contains a structure definition and the declarations of the three.

#### caesarcipher-XXX-YYY.s files

The files are:
- caesarcipher-A64-linux.s
- caesarcipher-x86-64-linux.s

These files contain the assembly code for the three functions.
The code is mostly-complete;
there are ten lines missing, which you will introduce.

> ❗️ **Important**
>
> Edit the file that corresponds to your system.
> If you do not see CMake's message that identified the correct file,
> you can double-check your system's architecture and operating system by looking at *submission_metadata.json*'s "environment" object.


---

|                 |      [⬆️](../README.md)      |                      [A64 ➡️](02-caesar-cipher-A64.md) <br> [x86-64 ➡️](02-caesar-cipher-x86-64.md)                       |
|:---------------:|:----------------------------:|:-------------------------------------------------------------------------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [Caesar Cipher Function (A64)](02-caesar-cipher-A64.md) <br> [Caesar Cipher Function (x86-64](02-caesar-cipher-x86-64.md) |
