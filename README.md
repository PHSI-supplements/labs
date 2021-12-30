# textbook-code

This repository contains laboratory assignments that complement material in
[*Programming at the Hardware/Software Interface*](https://www.greatriverlearning.com/product-details/1846)
by Christopher A. Bohn.

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

The `common/assignment.tex` file defines some commands that you will set once,
or once per term.

-   **\\courseterm** The name of the current semester or quarter, such as
    *Spring 2021*
-   **\\coursenumber** The name of the course that the labs are being used in,
    such as *CSCE 231*
-   **\\runtimeenvironment** The computing environment students should use to
    complete the assignment, such as *your account on the* csce.unl.edu *Linux
    server* or *your Linux virtual machine*
-   **\\filesource** Where students will download the packaged zip file and/or
    tarball, such as *Canvas* or *~cse231 on the Linux server*
-   **\\filesubmission** Where students will submit their lab deliverables,
    such as *Canvas* or *Web Handin*

Each lab assignment's LaTeX file redefines commands for that particular lab
assignment.

-   **\\labnumber** The lab assignment number
-   **\\collaborationrules** Your policy for whether and under what conditions
    students can work together.
    -   `common/assignment.tex` defines a couple of pre-defined collaboration
        rules, \\individualeffort and \\teameffort; however, particular you
        can specify custom conditions as well
-   **\\duedate** When the lab assignment is due

## Sample Solutions and Autograders

While the labs' assignment sheets and starter code is available to anyone under
the Apache License, I am providing sample solutions and autograders only to
instructors who have adopted [*Programming at the Hardware/Software
Interface*](https://www.greatriverlearning.com/product-details/1846). (Full
disclosure: the autograders are works-in-progress, much to my TAs'
disappointment.)
