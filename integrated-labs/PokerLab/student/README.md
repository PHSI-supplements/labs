# PokerLab

The purpose of this assignment is to (re)familiarize you with some aspects of C that may not be intuitive to students who are new to C.
Even if you know C, work this assignment to re-familiarize yourself.

## Front Matter

### Submission Deadline

This assignment is due **the week of September 1, before the start of your lab section**.  
If you have late days available, you may use one or more to extend your deadline.

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

- [Poker Terminology](doc/1-terminology.md)
- [Getting Started](doc/2-getting-started.md)
- [Print Conversion Specifier](doc/3-print-conversion-specifier.md)
- [Creating a Deck of Cards](doc/4-creating-deck-of-cards.md)
- [Study the Code in *poker.c*](doc/5-code-reading.md)
- [Characterizing a Poker Hand](doc/6-characterize-hands.md)
- [Turn-In and Grading](doc/7-grading.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Edit and compile a C program.
- Understand the similarities between Java and C code.
- Adapt to some differences between Java and C code, specifically those associated with arrays, strings, and boolean values.

### Assignment Summary

In this assignment, you will either re-familiarize yourself with the C programming language, or you will begin your initial familiarization with C.
The syntax of C syntax is very similar to Java's syntax, which is to say that Sun Microsystems borrowed much of C's syntax when they created the Java language to give C developers something familiar.
There are notable differences in the languages, as detailed in the textbook's Chapter 1 and Appendix C.
In this assignment you will encounter some of those differences, such as integers as booleans, strings as arrays, arrays as pointers, explicitly allocating memory, and `printf` format strings.

One notable difference between Java and C is that Java's behavior is completely specified;
the C standard explicitly identifies some parts of the language as having "implementation-defined behavior" and some other parts as having "undefined behavior."
Undefined behavior occurs in scenarios in which you attempt to have the program do something in which the behavior cannot be well-defined, such as accessing memory that hasn't been allocated.

Implementation-defined behavior means that the program might do something different if you change to a different compiler, operating system, version of either, processor, or optimization level.
For this reason, each lab assignment specifies the runtime environment and provides specific instructions to build your program;
<font color="red">**following those instructions and testing your code in the specified environment will ensure that we see the same behavior during grading that you saw during testing**</font>.

There are other differences beyond what we'll see in this course's labs;
our coverage of the C language is necessarily focused on what you need for this course.
We encourage you to learn more about the C language on your own.

### No Spaghetti Code Allowed

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.

---

|                 |                              |        [➡️](doc/1-terminology.md)         |
|:---------------:|:----------------------------:|:-----------------------------------------:|
|                 |                              | [Poker Terminology](doc/1-terminology.md) |

