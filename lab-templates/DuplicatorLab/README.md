# Race Condition Elimination Lab

[//]: # (DuplicatorLab © 2022-25 Christopher A. Bohn)

In this assignment, you will remove a race condition in concurrent code by using a mutual exclusion token.
There is only a small amount of design effort required for this lab assignment, and you should be able to complete much of it during lab time.

This assignment is worth 20 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of March 30, before the start of your lab section**.
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
- [About the Duplicator](doc/02-about-duplicator.md)
- [Understand the Starter Code](doc/03-understanding-code.md)
- [Understand the Race Condition](doc/04-understand-race-condition.md)
- [Remove the Race Condition](doc/05-remove-race-condition.md)
- [Turn-In and Grading](doc/06-grading.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Describe valid interleavings of concurrent systems
- Explain how mutual exclusion techniques can prevent undesired interleavings
- Manage a mutual exclusion token provided by the POSIX `pthreads` library

### Assignment Summary

This lab assignment requires you to think about valid interleavings of a concurrent program.
Being able to think about how concurrent processes interleave, and how to constrain those interleavings, will be very valuable in later courses and in your future career.

You will use valid interleavings to demonstrate that a race condition is present in the starter code, and
you will use valid interleavings to find suitable locations to lock and unlock a mutual exclusion token to remove that race condition.

This assignment also introduces a couple of concepts that aren’t central this assignment’s objectives but will re-appear in the input/output lab assignments.

#### Constraints

Do not add any lines of code other than those specified by the assignment.
Do not edit, delete, or move any lines of code that are present in the starter code.

### Unit Tests

DuplicatorLab's driver code opens a file stream to the source file and a file stream to the destination file.
The lab is designed to attempt to copy the source file into the destination file and then use the `diff` command to determine if there's a difference.
You may, if you wish, create automated unit tests.
The file *test/unit-tests.h* provides a simple framework.
Add a test to *test/unit-tests.c* by bounding the test function body with the `TEST()` and `END_TEST` macros, providing a test function name as the argument to `TEST()`.
The available assertions are:
```
ASSERT_TRUE(expression)
ASSERT_FALSE(expression)
ASSERT_EQUAL(expected, actual)
ASSERT_ALMOST_EQUAL(expected, actual, delta)
ASSERT_EQUAL_STRINGS(expected, actual)
ASSERT_EQUAL_MEMORY(expected_ptr, actual_ptr, size_bytes)
```
Alternatively, you can return `true` when the test passes, and `false` when the test fails.
You *may* violate the assignment's constraints in *test/unit-tests.c*, because this file will not be graded.

The file *test/example-tests.c* contains two unit tests that correspond to the example tests included in the assignment's write-up.

After compiling the project, you can use the command `ctest --test-dir build --output-on-failure` to run the automated unit tests.

> ❗️ **Important**
> 
> Running the unit tests once is ***not*** sufficient to demonstrate the absence of a race condition.
> If you can run the unit tests several times without any failures, then you probably have eliminated the race condition in *duplicator.c*. 

<!--
### Structured Control Flow Only

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.
You can use the command `ctest --test-dir build --output-on-failure` to check whether you inadvertently violated this constraint.
-->

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
