# AddressingLab

[//]: # (AddressingLab © 2021-25 Christopher A. Bohn)

In this assignment, you will practice creating the source and destination for x86 assembly language instructions.
There is no design effort required for this lab assignment,
and **you should be able to complete it during lab time**.

> ❗️ **Important**
> 
> The instructions are written assuming you will edit and run the code on nuros.unl.edu.
> Specifically, the assembly code file is written for an x86-64 processor running a Unix (Linux or macOS) operating system.
> If you wish, you may edit the code in a different environment; 
> however, you will not be able to assemble and link an executable on Arm processors (including Apple M1/M2/M3/M4 processors), nor on a system running a Windows operating system.

This assignment is worth 10 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of October 6, before the start of your lab section**.
Your completed assignment must be pushed to git.unl.edu before it is due.

If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt](LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt) file and including the update with your code.

### Collaboration Rules

During your scheduled lab time, you may, **but are not required to**, form a partner group of 2 students.
When necessary, there may be a group of 3 students.
During your scheduled lab time, and until the end of your lab day, you may discuss problem decomposition and solution design with your lab partner.
After your scheduled lab day, you may discuss concepts and syntax with other students, but you may discuss solutions only with the professor and the TAs.
Sharing code with or copying code from another student or the internet is prohibited.

If you work with a lab partner, be sure to commit your code at the end of lab, and also at the end of the day if you continue to work with them after lab.

### Generative AI Rules

You may use the CodeHelp.app "virtual TA" for help without restriction.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents

- [Getting Started](doc/01-getting-started.md)
- [Caesar Cipher Function](doc/02-caesar-cipher.md)
- [Sentence to Uppercase Function](doc/03-capitalization.md)
- [Cipher Validation Function](doc/04-cipher-validation.md)
- [Turn-In and Grading](doc/05-grading.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Write assembly instructions using an immediate value as the source
- Write assembly instructions using registers as the source and/or destination
- Write assembly instructions using memory as the source or destination
- Use the common memory addressing modes

### Assignment Summary

In this assignment, you won't have to write the entire functions in assembly language;
most of that has already been done for you.
Instead, there are ten lines of assembly code that you will need to complete, demonstrating an understanding of x86 operands and memory addressing modes.
The assembly code has a few optimizations, so some of it may not be immediately recognizable.

**You should be able to complete this lab assignment during lab time**;
however, it is not due until the week of October 6, before the start of your lab section.

#### Constraints

Do not add any lines of code other than those specified by the assignment.
Do not edit, delete, or move any lines of code that are present in the starter code.


---

|                 |                              |       [➡️](doc/01-getting-started.md)        |
|:---------------:|:----------------------------:|:--------------------------------------------:|
|                 |                              | [Getting Started](doc/01-getting-started.md) |

Assignment and starter code © Christopher A. Bohn,
licensed under the Creative Commons Attribution 4.0 International License
and under the Apache License Version 2.0, respectively.

<!-- [![License: CC BY 4.0](https://licensebuttons.net/l/by/4.0/80x15.png)](https://creativecommons.org/licenses/by/4.0/) -->
[![License: CC BY 4.0](https://img.shields.io/badge/License-CC_BY_4.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
