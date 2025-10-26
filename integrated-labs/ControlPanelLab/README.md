# Memory-Mapped I/O Lab

[//]: # (ControlPanelLab © 2021-25 Christopher A. Bohn)

In this assignment, you will write functions to use the input and output devices on a Cow Pi development board with a RP2040 microcontroller.

This assignment is worth XX points.

## Front Matter

### Submission Deadline

This assignment is due **the week of November 10, before the start of your lab section**.
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

You may use the CodeHelp.app "virtual TA" for help, and
you may use "Oscar the AI Tutor" built into the course's textbook.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents

- [Getting Started](doc/01-getting-started.md)
- [Debouncing and Debugging](doc/02-debouncing-debugging.md)
- [Initial Changes to the Code](doc/03-labtime.md)
- [Time, and Simple Memory-Mapped Input/Output](doc/04-simple-io.md)
- [Scanning the Matrix Keypad](doc/05-keypad.md)
- [Turn-In and Grading](doc/06-grading.md)
- [Appendix A: Lab Checkoff](doc/AA-checkoff.md)
- [Appendix B: Links to the Cow Pi Datasheet](doc/BB-datasheet-links.md)
- [Appendix C: Variable Modifiers](doc/CC-variable-modifiers.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Use memory-mapped I/O to obtain inputs from peripheral devices
- Use memory-mapped I/O to send outputs to peripheral devices
- Scan a matrix keypad

### Assignment Summary

This lab assignment requires you to think about valid interleavings of a concurrent program.
Being able to think about how concurrent processes interleave, and how to constrain those interleavings, will be very valuable in later courses and in your future career.

You will use valid interleavings to demonstrate that a race condition is present in the starter code, and
you will use valid interleavings to find suitable locations to lock and unlock a mutual exclusion token to remove that race condition.

This assignment also introduces a couple of concepts that aren’t central this assignment’s objectives but will re-appear in the input/output lab assignments.

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

To receive credit for the memory-mapped I/O portion of this lab, all input and output must be accomplished using the memory-mapped I/O registers.
The starter code calls `cowpi_setup()` for you.
You also may use [`cowpi_debounce_byte()` and `cowpi_debounce_long()`](https://cow-pi.readthedocs.io/en/latest/CowPi/inputs.html#debouncing).
You may not use any other functions described in the [CowPi Library](https://cow-pi.readthedocs.io/en/latest/library.html) portion of the Cow&nbsp;Pi datasheet.

You may not use any libraries beyond those explicitly identified here.


### No Spaghetti Code Allowed

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.
<!--
You can use the command `ctest --test-dir build --output-on-failure` to check whether you inadvertently violated this constraint.
-->

[//]: # (TODO: get the test to work, or replace with the old-style python command)

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
