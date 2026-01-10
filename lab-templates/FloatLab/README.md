# FloatLab

[//]: # (FloatLab © 2019-25 Christopher A. Bohn)

In this assignment, you will become more familiar with bit-level representations of floating point numbers.
You'll do this by implementing floating point arithmetic for 32-bit floating point numbers using only bitwise operators and integer arithmetic.

This assignment is worth 35 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of February 16, before the start of your lab section**.
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

### Generative AI Rules

You may use the CodeHelp.app "virtual TA" for help, and
you may use "Oscar the AI Tutor" built into the course's textbook.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents

- [Getting Started](doc/01-getting-started.md)
- [`unnormal_t` and Its Functions](doc/02-unnormal_t.md)
- [Constants and Queries](doc/03-constants-queries.md)
- [Examining IEEE 754-Compliant Values](doc/04-examining-numbers.md)
- [Encoding Numbers into the IEEE 754 Format](doc/05-normalization.md)
- [Multiplication and Division](doc/06-multiply-divide.md)
- [Addition and Subtraction](doc/07-add-subtract.md)
- [Rounding](doc/08-rounding.md)
- [Bonus Credit: Arbitrary Division](doc/09-arbitrary-division.md)
- [Turn-In and Grading](doc/10-grading.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Identify the bit fields of an IEEE&nbsp;754-compliant floating point number
- Obtain the value of an IEEE&nbsp;754-compliant floating point number
- Perform floating point arithmetic
- Apply IEEE&nbsp;754 "round-to-nearest-even" rounding

### Assignment Summary

In this assignment, you will implement a 32-bit FPU.
You will implement floating point arithmetic using integer operations and bit-level operations, an encapsulated data type and a small amount of other starter code that we will provide, and other code that you will write.
Specifically, the FPU's operations are:
- Some query functions to determine characteristics of a floating point value
- Normalization and denormalization
- Negation
- Addition and Subtraction
- Multiplication
- Division, only when the dividend's significand is a multiple of the divisor's significand

You will *not* be required to implement a square root function, which is also commonly found in FPUs.

We have provided an encapsulated data type, `unnormal_t`, to simplify some of the steps that will be necessary in your arithmetic functions.

#### Constraints

You may not use C's built-in floating point types or operations.
Specifically, you may not declare any variable to be of type `float` or `double`, you may not cast any value to either of these types, nor may you use floating point literals.

You may not use unions.
You may not use inline assembly code.

You may not use any libraries other than the *libc* library.
This prohibition includes, but is not limited to, C's *math* library.
If you find yourself `#include`ing any header files other than *fpu.h*, *unnormal.h*, *assert.h*, *stdbool.h*, *stdint.h*, and *stdio.h*, you are probably violating this constraint.

The time-complexity of all operations must be linear (or constant) in the number of bits required to represent the values.
Inefficient solutions, such as (but not limited to) implementing multiplication by repeatedly adding the multiplicand to itself $multiplier$ times, or implementing division by repeatedly subtracting the divisor from the dividend, are prohibited.

You may not change the signatures of any functions that you are required to complete for this assignment.
If you write helper functions that are not required, then they may have any signature that you deem necessary
(your helper functions must also comply with the assignment's constraints).

You are permitted to use C's integer comparators, integer arithmetic, bitwise operations, bit shift operations.
You may cast between integer types.
You may use loops, conditionals, function calls, structs, and arrays.
And, of course, you may use any of the provided starter code and any code that you write by yourself for this assignment.

You can use the command `ctest --test-dir build --output-on-failure` to check whether you're using `float` or `double`, whether you're defining a `union`, and whether you're using a floating point literal.

### Structured Control Flow Only

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.
You can use the command `ctest --test-dir build --output-on-failure` to check whether you inadvertently violated this constraint.

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
