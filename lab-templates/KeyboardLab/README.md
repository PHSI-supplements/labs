# KeyboardLab

[//]: # (KeyboardLab © 2021-26 Christopher A. Bohn)

The purpose of this assignment is to give you more confidence in C programming and to begin your exposure to the underlying bit-level representation of data.

This assignment is worth 20 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of January 26, before the start of your lab section**.
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

- [Lab Time Discussion](doc/01-lab-time.md)
- [Treating Numbers as Characters](doc/02-numbers-as-characters.md)
- [Treating Characters as Numbers](doc/03-characters-as-numbers.md)
- [Using Bitmasks and Shifting Bits](doc/04-bit-operations.md)
- [Turn-In and Grading](doc/05-grading.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Use the ASCII table to determine the corresponding integer values of C `char` values.
- Apply arithmetic operators and comparators to C `char` values.
- Construct and use a bitmask.
- Use bitwise operators and bit shift operators to create and modify values.

### Assignment Summary

In this assignment, you will write five functions, each solving a simple problem that, if not for your "broken keyboard," you would be able to solve easily.
The "damage" to your keyboard as the scenario progresses will require you to treat data differently than you have in the past.

First, you will need to use some characters' ASCII values -- that is, integers -- in place of the characters when constructing a string.
Next, you will need to use characters as though they were integers and perform arithmetic upon them.
Finally, you will manipulate integers using bit operations.

#### Constraints

Each section restricts the use of certain characters on your keyboard.
These restrictions do not prohibit the use of those characters in comments, but you may not use those characters in your code.
You can use the command `ctest --test-dir build --output-on-failure` to check whether you inadvertently used one of those characters.

### Structured Control Flow Only

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.
You can use the command `ctest --test-dir build --output-on-failure` to check whether you inadvertently violated this constraint.

---

|                 |                              |         [➡️](doc/01-lab-time.md)          |
|:---------------:|:----------------------------:|:-----------------------------------------:|
|                 |                              | [Lab Time Discussion](doc/01-lab-time.md) |

Assignment and starter code © Christopher A. Bohn,
licensed under the Creative Commons Attribution 4.0 International License
and under the Apache License Version 2.0, respectively.

<!-- [![License: CC BY 4.0](https://licensebuttons.net/l/by/4.0/80x15.png)](https://creativecommons.org/licenses/by/4.0/) -->
[![License: CC BY 4.0](https://img.shields.io/badge/License-CC_BY_4.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
