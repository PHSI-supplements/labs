# Interrupt-Driven Input/Output

[//]: # (ProximityAlarmLab © 2023-25 Christopher A. Bohn)

In this assignment, you will write code for a Cow&nbsp;Pi development board with a RP2040 microcontroller.
This code will use interrupts from external devices and from timers to control a piezoelectric buzzer and an ultrasonic rangefinder.

This assignment is worth 20 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of December 1, before the start of your lab section**.
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
- [Interrupt-Driven Input/Output](doc/02-interrupts.md)
- [Generating Tones with a Piezobuzzer](doc/03-piezobuzzer-intro.md)
- [Generating an Alarm](doc/04-alarm.md)
- [Measuring the Distance to an Object](doc/05-distance.md)
- [Building the Sensor's State Machine](doc/06-sensor-state-machine.md)
- [A Proximity Alarm](doc/07-proximity-alarm.md)
- [Turn-In and Grading](doc/08-grading.md)
- [Appendix A: Lab Checkoff](doc/AA-checkoff.md)
- [Appendix B: Attaching and Detaching the Seven-Segment Display Module](doc/BB-peripherals.md)
- [Appendix C: Re-Expressing the Distance Equation to use only Integer Arithmetic](doc/CC-distance-formulation.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Register an interrupt service routine
- Use interrupt-driven I/O to realize simple requirements

### Assignment Summary

This lab assignment has two parts.

In the first part, you use a timer interrupt to generate sound by repeatedly alternating the value on an output pin.

In the second part of the assignment, you will use a combination of a timer interrupt and a pin interrupt to manage the transitions of a state machine.
The particular transitions taken will allow you to determine whether the rangefinder is ready to emit an ultrasonic pulse and to determine whether the pulse echoed off of an object.
If there is an object, you will be able to calculate the distance to the object because the interrupts allow you to determine very precisely how much time elapsed between the pulse initiation and the echo detection.


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
