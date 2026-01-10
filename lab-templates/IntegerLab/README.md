# IntegerLab

[//]: # (IntegerLab © 2018-25 Christopher A. Bohn)

In this assignment, you will become more familiar with bit-level representations of integers.
You'll do this by implementing integer arithmetic for 16-bit signed and unsigned integers using only bitwise operators.

This assignment is worth 36 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of February 9, before the start of your lab section**.
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
- [Utility Functions](doc/02-utility-functions.md)
- [Checking the Sign, and Testing for Equality](doc/03-negative-and-equality.md)
- [Logical Operations](doc/04-logical-operations.md)
- [Adder "Hardware"](doc/05-adders.md)
- [Addition and Subtraction](doc/06-addition-subtraction.md)
- [Unsigned Multiplication and Division](doc/07-unsigned-multiplication-division.md)
- [Signed Multiplication and Division (Bonus Credit)](doc/08-signed-multiplication-division.md)
- [Turn-In and Grading](doc/09-grading.md)
- [Appendix: Example Tests](doc/AA-example-tests.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Recognize several powers of two
- Apply bit operations in non-trivial applications
- Illustrate ripple-carry binary addition
- Express common boolean and comparison operations in terms of other functions
- Recognize whether integer overflow has occurred
- Explain the relationship between multiplication, division, and bit shifts
- Express multiplication as an efficient use of other functions

### Assignment Summary

In this assignment, you will implement a 16-bit ALU.
You will implement logical boolean operations and arithmetic using only bitwise operations, bit shift operations, a small amount of starter code, and other code that you will write.
Specifically, the ALU's functions are:
- Logical NOT
- Logical AND
- Logical OR
- Comparisons, both equality and inequality
- Addition, both signed and unsigned values
- Subtraction, both signed and unsigned values
- Multiplication, unsigned values only
- Division, unsigned values only, and only when the divisor is a power of two

The operands for the arithmetic and comparison functions will be 16-bit integers.
The arguments for the logical boolean functions are declared to be 32-bit values because that may make some of your code easier to implement;
however, we will only grade these functions with 16-bit operands.
The utility and "building block" functions that you will implement along the way will have arguments sized according to the functions' needs.

#### Constraints

You may not use C's built-in arithmetic and logical boolean operations.
Specifically, you may not use addition (+), increment (++), subtraction(-), decrement(--), multiplication(*), division(/), modulo (%), logical NOT (!), logical AND (&&), or logical OR (||).
You may not use arithmetic-and-assignment operators (`+=`, `-=`, `*=`, `/=`, `%=`).
You may not use C's comparators;
specifically, you are not permitted to use equals (==), not-equals (!=), less-than (<), less-than-or-equal-to (<=), greater-than-or-equal-to (>=), or greater-than (>).
You may not use floating-point operators as a substitute for integer operators.

You may not use arrays as truth tables.
You may not use inline assembly code.

You may not use any libraries.
This prohibition includes, but is not limited to, C's *math* and *stdbit* libraries.
(You also may not use GCC's and Clang's `__builtin...` functions that correspond to the *stdbit* functions.)
If you find yourself `#include`ing any header files other than *alu.h*, you are violating this constraint.

The time-complexity of all operations must be polynomial (or constant) in the number of bits required to represent the values.
Inefficient solutions, such as (but not limited to) implementing multiplication by repeatedly adding the multiplicand to itself $multiplier$ times, or implementing division by repeatedly subtracting the divisor from the dividend, are prohibited.

You may not change the signatures of any functions that you are required to complete for this assignment.
If you write helper functions that are not required, then they may have any signature that you deem necessary
(your helper functions must also comply with the assignment's constraints).

You are permitted to use C's bitwise operations and bit shift operations, including bitwise complement (~), bitwise AND (&), bitwise inclusive OR (|), bitwise XOR (^), left shift (<<), and arithmetic and logical right shift (>>), and their corresponding assignment operators.
You may cast between integer types.
You may use loops, conditionals, function calls, structs, and (except as noted above) arrays.
And, of course, you may use any of the provided starter code and any code that you write by yourself for this assignment.

You can use the command `ctest --test-dir build --output-on-failure` to check whether you're using a disallowed arithmetic, logical, or comparison operator.

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
