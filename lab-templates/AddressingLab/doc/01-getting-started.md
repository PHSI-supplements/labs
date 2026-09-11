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


### Configuring the Project

> ⓘ **Note**
>
> When you initially configure the project,
> CMake will detect your system's environment and identify the specific assembly code file that you should edit.
> ```
> -- The C compiler identification is ...
> -- The ASM compiler identification is ...
> -- Found assembler: ...
> -- Detecting C compiler ABI info
> -- Detecting C compiler ABI info - done
> -- Check for working C compiler: ...
> -- Detecting C compile features
> -- Detecting C compile features - done
> --
> -- ================ Assembly file selection ================
> -- Processor Architecture: XXX
> -- Operating System:       YYY
> -- EDIT THIS FILE: /path/to/AddressingLab/src/caesarcipher-XXX-YYY.s
> -- =========================================================
> --
> -- Configuring done (0.2s)
> -- Generating done (0.1s)
> -- Build files have been written to: /path/to/AddressingLab/build
> ```
> Editing other assembly code files will have no effect.
> 
> If you do not see this message, you can double-check your system's architecture and operating system by looking at *submission_metadata.json*'s "environment" object.

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

#### caesarcipher-XXX-YYY.s files

The files are:
- caesarcipher-A64-linux.s
- caesarcipher-A64-macos.s
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

|                 |      [⬆️](../README.md)      |           [➡️](02-caesar-cipher.md)           |
|:---------------:|:----------------------------:|:---------------------------------------------:|
|                 | [Front Matter](../README.md) | [Caesar Cipher Function](02-caesar-cipher.md) |
