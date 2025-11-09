# Digital Logic Design, and Polling Lab

[//]: # (CalculatorLab © 2020-25 Christopher A. Bohn)

In this assignment, you will design simple digital logic circuits by using a Karnaugh map to arrive at minimal sum-of-products expressions that can be programmed into a programmable logic array.
You will also implement a simple system that makes use of the development board’s buttons, switches, keypad, LEDs, and display module. 
You will implement this system by polling inputs.

This assignment is worth 25 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of November 17, before the start of your lab section**.
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
- [Seven Segment Display](doc/02-seven-segment.md)
- [Digital Logic Design](doc/03-digital-logic-design.md)
- [Polling Discussion](doc/04-polling.md)
- [Implementing the Number Builder](doc/05-number-builder.md)
- [A Four-Function Calculator](doc/06-calculator.md)
- [Turn-In and Grading](doc/07-grading.md)
- [Appendix A: Lab Checkoff](doc/AA-checkoff.md)
- [Appendix B: Attaching and Detaching the Seven-Segment Display Module](doc/BB-peripherals.md)


### Learning Objectives

After successful completion of this assignment, students will be able to:
- Use a Karnaugh map to design a simple digital logic circuit
- Poll an input to determine when it has taken on a value of interest

### Assignment Summary

This lab assignment has two parts.

In the first part, you will practice using Karnaugh maps to arrive at boolean expressions expressed in a minimal disjunctive normal form.
When working with discrete logic gates, you can arrive at even-more minimal expressions by introducing XOR gates (found by looking at diagonals in the Karnaugh map),
but keeping the expression in the disjunctive normal form (sum-of-products) would allow the digital logic to be encoded in a programmable logic array, a great time saver over working with discrete logic gates.
As you saw in class, using a Karnaugh map to produce a minimal DNF expression can also be used to write a function  more compactly than chained `if`/`else` statements.
(The resulting function may or may not be more readable than chained `if`/`else` statements and may or may not be more performant -- but it will be more compact.)

In the second part of the assignment, you will practice *polling* inputs, both physical inputs on the Cow&nbsp;Pi board and the RP2040's timer.
Polling is a mechanism very commonly used in embedded systems, as well as in long-running desktop and server applications -- particularly when concurrency is involved.
In a future assignment, we will look at another mechanism to work with inputs.


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
