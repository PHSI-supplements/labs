# Lab Assignments

This repository contains laboratory assignments useful in an undergraduate
computer organization or computer systems engineering course. I wrote these
assignments to complement material in
[*Programming at the Hardware/Software Interface*](https://www.greatriverlearning.com/product-details/1846); however, except for the
occasional mention of material in a specific chapter, these assignments can be
used independently of that textbook. (If you adopt some or all of these
assignments but not [*Programming at the Hardware/Software
Interface*](https://www.greatriverlearning.com/product-details/1846), then you
can easily edit the $\LaTeX$ files to refer to the appropriate chapter in whichever
textbook you use.)

## Contents

The directories `01.pokerlab`, `02.bitslab`, etc. correspond to the chapters
in the publication. If you are looking for a lab that reinforces concepts from
chapter *NN*, you will find it in a `NN.labname` directory.

Each `NN.labname` directory contains an `assignment` subdirectory that contains
the writeup describing the assignment, a `starter-code` subdirectory that
contains the starter code to provide to students, and a `package.sh` shell
script to generate the writeup pdf file and package it with the starter code
in a zip file and tarball to distribute to students.

## Customization

The `common/semester.tex` file defines some commands that you will set once,
or once per term.

-   **\\courseterm** The name of the current semester or quarter, such as
    *Spring 2021*
-   **\\coursenumber** The name of the course that the labs are being used in,
    such as *CSCE 231*
-   **\\runtimeenvironment** The computing environment students should use to
    complete most assignments, such as *your account on the* csce.unl.edu *Linux
    server* or *your Linux virtual machine*
    -   Some assignments may need this command to be renewed for a different
        computing environment
-   **\\filesource** Where students will download the packaged zip file and/or
    tarball, such as *Canvas* or *~cse231 on the Linux server*
-   **\\filesubmission** Where students will submit their lab deliverables,
    such as *Canvas* or *Web Handin*
-   **\\developmentboard** The name of the microcontroller board or single-board
    computer that has the CPU for the I/O labs
-   **\\cstwo** The course or courses that teach CS2 concepts, such as linked
    lists and event-driven programming

You may (or may not) want to instill some good development practices. In the
`common/semester.tex` you can set some booleans to add programming constraints.
(Right now there is only one such constraint.):

-   **allowspaghetticode** If `false` then students will be prohibited from
    using `goto` statements, `continue` statements, `break` statements to exit
    from loops, and `return` statements inside loops. If `true` then no mention
    of these practices will appear in the assignments.
    -   If you wish to prohibit some of these practices but not others, then
        you can edit `common/assignment.tex`.

Finally, `common/semester.tex` has a sequence of commands that allow you to
specify each lab assignment's lab number, collaboration rules, and due date.
Those that likely use a different computing environment than the default also
have a command to specify the computing environment.

## Sample Solutions and Autograders

While the labs' assignment sheets and starter code is available to anyone under
the Apache License, I am providing sample solutions and autograders only to
instructors who have adopted [*Programming at the Hardware/Software
Interface*](https://www.greatriverlearning.com/product-details/1846). Full
disclosure:

-   I'm rewriting the autograder core to allow finer control of runaway
    student code, after a couple of students' code brought our server to its
    knees.
-   Some labs require free-form answers; the free-form answers are not
    autograded.
-   Some labs do not lend themselves to autograding, much to my TAs'
    disappointment. These labs, as written, offer a small bonus to students to
    demonstrate the functionality on or before the due date, reducing the
    grading burden to only the non-functional requirements for most students'
    submissions.

## Contact Me

If you adopt some or all of these lab assignments, please send me a note at
bohn@unl.edu. I ask that you let me know that you've adopted some or all of the
lab assignments because being able to show the breadth to which my instructional
materials are being used by others will be useful for my future reappointment
and promotion packages. I promise not to badger you into adopting [*Programming
at the Hardware/Software
Interface*](https://www.greatriverlearning.com/product-details/1846) (I won't
even mention it unless you ask for sample solutions or autograders.)

Similarly, if you have any questions, comments, requests, or suggestions, I
welcome the feedback -- feel free to contact me at bohn@unl.edu.
