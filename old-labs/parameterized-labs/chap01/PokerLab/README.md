# PokerLab

This assignment is designed to help students get started (or re-familiarize themselves) with C programming.
Its purpose is threefold:
- Provide relatively simple assignment that students can use to (re)familiarize themselves with C
- Get students set up in the development and runtime environment(s)
- Make the initial assignment short enough that students who arrive to campus a few days late can pick it up and still finish on time

Students will see code that has some of C's quirks: integers as booleans, strings as arrays, arrays as pointers, explicitly allocating memory, `printf` format strings -- all sorts of C goodness.
They'll then apply what they learned (and learn from mistakes) by finishing the program's implementation.

There is no autograder for this lab -- I made it a low-pressure assignment by keeping it as having an effort-based grade. 
If you adopt this assignment, you're free to change that to a correctness-based grade, and if you ask I'll probably write an autograder for you (at least for the part that *can* be autograded).

## Customization

Most of the assignments are usable out-of-the-box with perhaps some tweaking of the customization json files.
Part of this assignment, however, is students getting up and going in the development environment.
There are two files that you should customize for the development and runtime environment(s) that your students will use for (most of) the assignments in your course:
- `assignment/connecting.tex` -- describe what your students need to be able to do in order to run the assignments in the intended environment
- `assignment/demonstration-of-connection.tex` -- describe how your students can demonstrate that they can connect to the runtime environment
  - Be sure to include (and customize!) the `\newcommand{\connectingrubricitem}{...}` line so that the rubric entry makes sense.

I have included as examples the files that I use in my course.
