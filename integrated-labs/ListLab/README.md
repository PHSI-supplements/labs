# ListLab

The purpose of this assignment is to give you more confidence in C programming and to begin your exposure to pointers and to file input/output.

This assignment is worth 35 points.

## Front Matter

### Submission Deadline

This assignment is due **the week of September 15, before the start of your lab section**.
Your completed assignment must be pushed to git.unl.edu before it is due.
A portion of this assignment is on Canvas; that must also be completed before it is due.

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

You may use the CodeHelp.app "virtual TA" for help without restriction.
You may use other generative AI tools to translate this assignment into another human language.
No other use of generative AI is permitted on this assignment without explicit permission from Dr. Bohn.

### Table of Contents

- [Stray Values in Memory](doc/01-stray-values-in-memory.md)
- [Getting Started](doc/02-getting-started.md)
- [Word Entries](doc/03-word-entries.md)
- [Alphabetical Functions](doc/04-alphabetical-functions.md)
- [Preparing to Work with Lists](doc/05-preparing-to-work-with-lists.md)
- [Inserting Words](doc/06-inserting-words.md)
- [Linked List Overview](doc/07-linked-list-overview.md)
- [Creating and Attaching a Node](doc/08-create-and-attach-node.md)
- [Iterating](doc/09-iterating.md)
- [Insertion and Deletion at Arbitrary Locations](doc/10-insert-delete-node.md)
- [Examining Word Entries](doc/11-examine-word-entries.md)
- [Swapping and Merging Nodes, and Final Testing](doc/12-swap-merge-nodes.md)
- [Turn-In and Grading](doc/13-grading.md)
- [Appendix A: Differences and Similarities between Java and C that are Relevant to this Assignment](doc/AA-JavaVsC.md)
- [Appendix B: Linked List](doc/BB-data-structure.md)
- [Appendix C: Word Count Tables](doc/CC-word-tables.md)

### Learning Objectives

After successful completion of this assignment, students will be able to:
- Recognize the hazards of code with undefined behavior.
- Use C's string functions from [string.h](https://unl.grlcontent.com/compeng2e/page/appendixc#c16).
- Alias and reassign pointers.
- Create and traverse a linked list.

### Assignment Summary

This assignment is principally about getting comfortable when explicitly working with memory.
Being able to think about a value and a reference to that value distinctly will improve your programming skills in any language.

Before you do so, you will [examine Archie's code](doc/01-stray-values-in-memory.md).
Parts of Archie's programs use code that the C standard explicitly states will result in undefined behavior.
By understanding the mistakes that Archie made, we hope that you can avoid them in your own code.

As part of this assignment, you will build and use a linked list.
This will require you to allocate space for the list's nodes and manipulate pointers that connect the nodes to each other.

#### Constraints

There are no particular restrictions on uses of C's features in this assignment other than those common to most lab assignments in this course.

Some operations on a list have "undefined behavior" when performed using an invalid iterator.
When the behavior is undefined, any result is acceptable \textit{except} crashing the program.
Specifically, you may not dereference a null pointer.
The constraint-checking test will not check for this; however, you can test for it using the code provided to you.

### No Spaghetti Code Allowed

In the interest of keeping your code readable, you may not use any `goto` statements,
nor may you use any `break` statements to exit from a loop,
nor may you have any functions `return` from within a loop.
You can use the command `ctest --test-dir build --output-on-failure` to check whether you inadvertently violated this constraint.

---

|                 |                              |           [➡️](doc/01-stray-values-in-memory.md)           |
|:---------------:|:----------------------------:|:----------------------------------------------------------:|
|                 |                              | [Stray Values in Memory](doc/01-stray-values-in-memory.md) |

Assignment and starter code © Christopher A. Bohn,
licensed under the Creative Commons Attribution 4.0 International License
and under the Apache License Version 2.0, respectively.

<!-- [![License: CC BY 4.0](https://licensebuttons.net/l/by/4.0/80x15.png)](https://creativecommons.org/licenses/by/4.0/) -->
[![License: CC BY 4.0](https://img.shields.io/badge/License-CC_BY_4.0-lightgrey.svg)](https://creativecommons.org/licenses/by/4.0/)
[![License](https://img.shields.io/badge/License-Apache_2.0-blue.svg)](https://opensource.org/licenses/Apache-2.0)
