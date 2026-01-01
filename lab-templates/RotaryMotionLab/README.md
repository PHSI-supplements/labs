# Converting Rotary Motion Input into Rotary Motion Output Lab

[//]: # (RotaryMotionLab © 2025 Christopher A. Bohn)

In this assignment, you will write code that will accept input from a rotary encoder and use that input to actuate a servo.
In part of the assignment, you will demonstrate that you have retained knowledge that you honed in earlier assignments;
in another part of the assignment you will learn to *sample* an input.

This assignment is worth 25 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of December 7, before the start of your lab section**.
Your completed assignment must be pushed to git.unl.edu before it is due.

If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt](LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt) file and including the update with your code.

> 📝 **Grading Note**
> 
> You are not eligible for the early check-off bonus if you use a late day on this assignment.

### Collaboration Rules

During your scheduled lab time, you may, **but are not required to**, form a partner group of 2 students.
When necessary, there may be a group of 3 students.
During your scheduled lab time, and until the end of your lab day, you may discuss problem decomposition and solution design with your lab partner.
After your scheduled lab day, you may discuss concepts and syntax with other students, but you may discuss solutions only with the professor and the TAs.
Sharing code with or copying code from another student or the internet is prohibited.

If you work with a lab partner, be sure to commit your code at the end of lab, and also at the end of the day if you continue to work with them after lab.

### Generative AI Rules

You may use the CodeHelp.app "virtual TA" for help, and
you may use "Oscar the AI Tutor" built into the course's textbook.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents

- [Getting Started](doc/01-getting-started.md)
- [Setting up the Timer and the I/O Port Pointer](doc/02-initializing.md)
- [Controlling a Servomotor: Theory of Operation](doc/03-servo-theory.md)
- [Control the Servomotor](doc/04-servo-implementation.md)
- [Reading the Rotary Encoder: Theory of Operation](doc/05-rotary-encoder-theory.md)
- [Read the Rotary Encoder](doc/06-rotary-encoder-implementation.md)
- [Remotely Operating an Arm](doc/07-input-to-actuator.md)
- [Turn-In and Grading](doc/08-grading.md)
- [Appendix A: Lab Checkoff](doc/AA-checkoff.md)
- [Appendix B: Attaching and Detaching Peripheral Devices](doc/BB-peripherals.md)


### Learning Objectives

After successful completion of this assignment, students will be able to:
- Formulate memory-mapped I/O for a new device
- Create an asymmetrical waveform using a timer interrupt
- Use a timer interrupt to sample an input

### Assignment Summary

This lab assignment has three parts.

In the first part, you will show that you recall how to set up and use memory-mapped I/O by creating a function to read a new type of input.
You will also show that you recall how to set up a timer interrupt.

In the second part of the assignment, you will implement *pulse-width modulation*, a technique to encode information in a periodic signal by varying the length of its peak without changing the signal's frequency. 

In the final part of the assignment, you will practice *sampling* an input, a technique that has properties of polling and properties of interrupt handling.

#### Constraints

You may use any features that are part of the C standard if they are supported by the compiler.

> ⓘ **Note**
> 
> The compiler currently used by PlatformIO for the RP2040 microcontroller does not support many C23 features.
> It does support binary literals, but in most other regards you should consider it to be a C11 compiler.

You may use the constants and functions provided in the starter code.

You may not use any libraries, functions, macros, types, or constants from the [Arduino core](https://www.arduino.cc/reference/en/).
You may not use any functions, macros, types or constants from the [Pico SDK](https://www.raspberrypi.com/documentation/pico-sdk/) that have been imported by Mbed OS.
You may not use any functions, macros, types or constants from [Mbed OS](https://os.mbed.com/docs/mbed-os/v6.16/introduction/index.html) that are not part of the C standard.

You *may* use any functions described in the [CowPi datasheet](https://cow-pi.readthedocs.io/).

You may not use any libraries beyond those explicitly identified here.

> 🔗 **Running the Constraint Checker**
> 
> In earlier lab assignments, you had to run the constraint checker by invoking the `ctest` command.
> In the hardware-based lab assignments, the constraint checker automatically runs at the end of the build process.
> After a successful build, any constraint violations will be listed after any compiler warnings and before the `[SUCCESS]` message.


### No Spaghetti Code Allowed

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.
Violations of this constraint will be included in the report generated by the constraint checker

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
