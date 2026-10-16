# BufferOverflowLab

[//]: # (Buffer Overflow Lab © 2025-26 Christopher A. Bohn)

In this assignment, you will gain firsthand experience with methods used to exploit security weaknesses in operating systems and network servers.

> 🤠 **No Blackhats**
>
> Our purpose is to help you learn about the runtime operation of programs and to understand the nature of these security weaknesses so that you can avoid them when you write programs, especially when you write system code.
>
> We do not condone the use of a buffer overflow attack nor any other form of attack to gain unauthorized access to any system resources.

> ❗️ **Important**
> 
> The instructions are written assuming you will run the code on nuros.unl.edu. 
> Specifically, the assembly code file is written for an x86-64 processor running a Linux operating system. 
> If you wish, you may edit your attack strings in a different environment;
> however, you will not be able to generate a target executable on a Linux system,
> an attack designed for an Arm processor will not work on an x86 processor, 
> and we will grade your attacks on nuros.

The attack portion of this assignment is worth 32 points, and identifying how to fix the vulnerability is worth 1 point.

<!--
[//]: # (TODO: update CMakeLists.txt to accommodate this feature)
> 🔬 **Experimental Feature**
>
> The *submission_metadata.json* file includes an "environment" object:
> ```
>  "environment": {
>    "architecture": "@ARCH@",
>    "os": "@OS@"
>  },
> ```
> CMake *should* replace the placeholder values with the actual values for nuros.
> **Please do not manually edit the "environment" object.**
> You may edit the other values as before.
-->

## Front Matter

### Submission Deadline

This assignment is due **the week of March 23, before the start of your lab section**.
Your completed assignment must be pushed to git.unl.edu before it is due.

If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [submission_metadata.json](submission_metadata.json) file and including the update with your code.

### Collaboration Rules

During your scheduled lab time, you may, **but are not required to**, form a partner group of 2 students.
When necessary, there may be a group of 3 students.
During your scheduled lab time, and until the end of your lab day, you may discuss problem decomposition and solution design with your lab partner.
After your scheduled lab day, you may discuss concepts and syntax with other students, but you may discuss solutions only with the professor and the TAs.
Sharing code with or copying code from another student or the internet is prohibited.

If you work with a lab partner, be sure to:
- Add your partner to [submission_metadata.json](submission_metadata.json),
- Commit your code (including submission_metadata.json) at the end of lab, and
- Commit your code at the end of the day if you continue to work with your partner after lab.

**After** you and your partner have both completed stages 0-4 under the normal collaboration rules,
you may work together on the bonus credit up until the assignment is due. 

### Generative AI Rules

You may use the CodeHelp.app "virtual TA" for help, and
you may use "Oscar the AI Tutor" built into the course's textbook.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents

- [Getting Started](doc/01-getting-started.md)
- [What Does the Stack Frame Look Like?](doc/02-stack-frame.md)
- [Stage 0: Simple Buffer Overflow on the Stack](doc/03-stage0.md)
- [What is Your Student ID?](doc/04-student-id.md)
- [Stage 1: Code Injection with Integer Argument](doc/05-stage1.md)
- [Stage 2: Code Injection with String Argument](doc/06-stage2.md)
- [Return-Oriented Programming](doc/07-rop.md)
- [Stage 3: Return-Oriented Programming with Integer Argument](doc/08-stage3.md)
- [Stage 4: Return-Oriented Programming with String Argument](doc/09-stage4.md)
- [Fixing the Code](doc/10-fixing-code.md)
- [Bonus Credit](doc/11-bonus.md)
- [Turn-In and Grading](doc/12-grading.md)
- [Appendix A: Generating Instruction Encodings Using Tools](doc/AA-assemble-disassemble.md)
- [Appendix B: x86-64 Instruction Encodings](doc/BB-x86-64-encoding.md)
- [Appendix C: A64 Instruction Encodings](doc/CC-A64-encoding.md)
<!--
- [Appendix A: Using `hex2raw`](doc/AA-using-hex2raw.md)
-->

### Learning Objectives

After successful completion of this assignment, students will be able to:

- Describe different ways that attackers can exploit security
  vulnerabilities when programs do not safeguard themselves well enough against buffer overflows
- Understand how to write programs that are more secure, as well as some of the features provided by compilers and operating systems to make programs less vulnerable
- Understand the stack and parameter-passing mechanisms of either x86-64 or A64 assembly code
- Describe how either x86-64 or A64 assembly language instructions are encoded
- Use debugging tools such as `gdb` and `objdump`

### Assignment Summary

[//]: # (TODO: link "code injection" to the relevant discussion if we add a page for that)
In this assignment, you will cause a buffer on the program stack to overflow, allowing you to overwrite a function call's return address.
In the code injection portion of the assignment, you will change the return address to point to a snippet of assembly code that you have written to change the program's behavior.
In the [return-oriented programming](doc/07-rop.md) portion of the assignment, you will create a series of pointers that point to pre-existing instructions, each of which will achieve part of the desired new behavior.  

> 🤠 **No Blackhats**
>
> Our purpose is to help you learn about the runtime operation of programs and to understand the nature of these security weaknesses so that you can avoid them when you write programs, especially when you write system code.
>
> We do not condone the use of a buffer overflow attack nor any other form of attack to gain unauthorized access to any system resources.


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
