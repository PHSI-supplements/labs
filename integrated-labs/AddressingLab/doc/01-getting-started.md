## Getting Started

> 📇 **Scenario**
>
> You've settled into a comfortable routine at the Pleistocene Petting Zoo.
> While your job isn't quite as exciting as that of the saber-toothed tigers' dentist,
> it still has something new and interesting almost every day.
> 
> Archie announces that he heard that hand-crafted assembly code can be faster than high-level language code.
> You try to explain that while this may have been true decades ago,
> modern optimizing compilers generate code faster than what a typical programmer can achieve with assembly code.
> Archie doesn't believe you and insists that you write the zoo's new cipher program in x86 assembly code.

During your lab period, the TAs will provide a refresher on
the format of x86 assembly instructions, including `mov` instructions and arithmetic instructions,
of the nomenclature used to specify the operand sizes, 
and of the role of each component of the most-general form of memory addressing: $D(R_b, R_i, S)$.
During the remaining time, the TAs will be available to answer questions.


### Configuring the Project

> ❗️ **Important**
>
> The  assembly code file is written for an x86-64 processor running a Unix (Linux or macOS) operating system.
> You will not be able to assemble and link an executable on Arm processors (including Apple M1/M2/M3/M4), nor on a system running a Windows operating system.

#### From VS Code

If you open *only* the `AddressingLab` directory in VS Code, then VS Code will automatically configure the project.
If instead you open the whole lab repository (so `AddressingLab` is just a subdirectory), then VS Code will *not* configure the `AddressingLab` project automatically.
If autoconfiguration doesn't happen, then open the Command Palette.
From the Command Palette, select `CMake: Select Configure Preset`.
Then select the preset of your choice:

- `default` -- developing on nuros
- `personal-computer` -- developing on your computer

#### From the Command Line

- `cmake --preset default` -- developing on nuros
- `cmake --preset personal-computer` -- developing on your computer


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

#### caesarcipher.s

This file contains the assembly code for the three functions.
The code is mostly-complete;
there are ten lines missing, which you will introduce.


---

|                 |      [⬆️](../README.md)      |           [➡️](02-caesar-cipher.md)           |
|:---------------:|:----------------------------:|:---------------------------------------------:|
|                 | [Front Matter](../README.md) | [Caesar Cipher Function](02-caesar-cipher.md) |
