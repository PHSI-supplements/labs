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

In the interest of a little humor and a contrivance to justify some of the
tasks ("why can't I use the letter *W*?"), each lab has a scenario taking place
at or adjacent to "The Pleistocene Petting Zoo" 🦣 (a very-thinly veiled mirror
of "Jurassic Park" 🦖). If you don't care for the scenarios, you can change (or
even remove) them.

## Contents

Each `XyzLab` directory contains an `assignment` subdirectory that contains
the writeup describing the assignment, a `starter-code` subdirectory that
contains the starter code to provide to students, and a `package.sh` shell
script to generate the writeup pdf file and package it with the starter code
in a zip file and tarball to distribute to students.

The `common` directory contains a couple of files with definitions that are
used in the assignment sheets. The `common/assignment.tex` contains general
definitions that you are unlikely to change, and the `common/semester.tex`
contains definitions that allow you to make necessary changes in a single
file.

There are a couple of legacy labs that we're still using that I'm in the process
of replacing since I don't hold the copyright on them -- I'll have those
replacements available soon enough.

### Customization

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

### Descriptions

As part of the customization, you can decide which labs you want your students to
do and in which order you want your students to do the labs in.

-   **PokerLab** serves two purposes. Its principal purpose is to (re)introduce
    students to C -- at one time, our computer science and software engineering
    students were not curricularly introduced to C before this course; for the
    past few years, somewhere between half and two-thirds had learned C, and
    we're transitioning back to only the computer engineering students learn C
    in their first year. The secondary purpose is to give students a very
    low-stakes assignment so that they can set up their development environments
    during the first week when some students (particularly international
    students) might still be arriving on-campus. PokerLab can be completed
    during lab time, and most students do so. To keep the assignment low-stakes,
    we grade PokerLab as an effort-based assignment.
-   **KeyboardLab** gets students used to the idea of data having an underlying
    representation, and gives them a taste of examining and manipulating that
    data at the bit level. KeyboardLab isn't specifically designed to be
    completed during lab time, but about half of the students do so. Something
    to watch out for is students who turn in more-general solutions than the
    assignment asks for -- for example, a student who is unable to use bit
    manipulation to subtract 1 from an odd number by setting the LSB to 0 (as
    instructed) is unlikely to have developed their own code to subtract 1 from
    any number (or subtract any number from any other number).
-   **PointerLab** encourages students to think about the difference between
    data and references to data. I'm working on reducing the scope without
    sacrificing learning objectives, as many students struggle with this lab.
-   **IntegerLab** has students make use of bit manipulation to implement
    integer arithmetic. I'm redesigning the lab, as many students are now
    copying an algorithm out of the textbook for the extra-credit portion of
    the assignment.
-   **FloatLab** has students implement floating point normalization and
    arithmetic. For the past few years (okay, I paused work on FloatLab while
    working on the textbook), I'd been trying to arrive at a 16-bit floating
    point lab but struggled with a bootstrapping problem of being able to get
    students started without giving them a worked solution. I've finally given
    up on that and wrote a 32-bit floating point lab.
-   **AddressingLab** guides students through creating operands for x86-64
    assembly code using immediate values, register operands, and memory operands
    (using direct, indexed, and offset addressing). To give students a low-effort
    lab when they have their first exam, I wrote AddressingLab to be completed
    during lab time and a little over half do so. (My TAs tell me that the low
    rate of in-lab completion is a combination of some students starting to
    skip lab time and some students choosing to leave lab shortly after the
    lab introduction).
-   (There are a couple of legacy labs that I don't hold the copyright for. If
    you ask, I'll point you to where they came from and how to modify the
    assignment sheets to match those of these labs. Soon enough, I'll have
    replacement labs written.)
-   **ConcurrencyLab** was meant to get students thinking about concurrent flows
    of control. *I recommend that you do not use this lab until I've completely
    redesigned it*: I've only used it once because it suffers from the problem
    of not having realistic partial credit: either you see how to do the lab and
    are able to get full credit, or you don't and get very little credit. That
    can't be fixed without starting over from scratch.
-   **I/O PreLab** is assigned several weeks before the I/O labs to give
    students plenty of time to assemble their hardware kits.
-   **PollingLab** is the first I/O lab. Students are introduced to
    memory-mapped I/O and to polling inputs. I'm in the process of rewriting
    this lab because it is also one that students struggle with.
-   **InterruptLab** introduces students to interrupt-driven I/O. They work both
    at the register level and also at a higher level of abstraction.
-   **SSBCLabs** (Simulated Single-Board Computer) were kludges that I wrote for
    students to use during the pandemic year for the I/O labs. *I'll soon remove
    them from this repo* because they need more work to make them less hacky,
    and the direction we went with the new I/O hardware offers us better
    options in the unlikely event that we have another pandemic year.
-   **CapstoneLab**, also known as GroupLab, is one of a handful of labs that
    have students develop a simple embedded system. This is typically a two-week
    assignment.
-   **MemoryLab** has students run some code to take measurements and draw
    conclusions from those measurements. They use their microcontroller to
    measure relative speeds of different types of memory (okay, really only
    SRAM vs flash), and they try to determine cache characteristics on a
    microprocessor's cache by running code that uses progressively larger
    data chunks and that accesses data in progressively larger strides.
    MemoryLab is designed to be completed during lab time since it we generally
    use it during the final week of the semester. Since there's no code to
    write, the only students who do not complete it during lab time are those
    who skip lab time. We grade MemoryLab as an effort-based assignment: we
    only require that their conclusions are *reasonable* given the data that
    they collect.

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
even mention it unless you ask for sample solutions or autograders).

Similarly, if you have any questions, comments, requests, or suggestions, I
welcome the feedback -- feel free to contact me at bohn@unl.edu.
