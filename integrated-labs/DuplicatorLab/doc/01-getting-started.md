## Getting Started

> 📇 **Scenario**
>
> Archie seems genuinely surprised that H.Awk&nbsp;Aye is refusing to go back to work.
> "You would think that he'd be grateful for being rescued from that flock of terror birds."
> Before you can wonder out-loud whether it would be a good idea to trust someone who had just tried to sell trade secrets to a competitor, Archie gives you your new task.
> 
> "Because H.Awk isn't cooperating, I need you to finish the project he was working on.
> As you can imagine, duplicating the genetic information for our exhibits can take a long time, and H.Awk realized that we might be able to duplicate the data faster if we had a concurrent program which has one thread reading from the original data and another thread writing the copy.
> Unfortunately, he ran off to sell samples to the  Supersized Safari Syndicate before finishing the duplicator.
> Right now the duplicator seems to work, but it usually makes imperfect copies.
> Have you ever seen a paleolama with two noses, four eyes, and no ears!?"

During your lab period, the TAs will explain how the code is designed to work.
During the remaining time, the TAs will be available to answer questions.


### Configuring the Project

#### From VS Code

If you open *only* the `DuplicatorLab` directory in VS Code, then VS Code will automatically configure the project.
If instead you open the whole lab repository (so `DuplicatorLab` is just a subdirectory), then VS Code will *not* configure the `DuplicatorLab` project automatically.
If autoconfiguration doesn't happen, then open the Command Palette.
From the Command Palette, select `CMake: Select Configure Preset`.
Then select the preset of your choice:

- `default` -- developing on nuros
- `personal-computer` -- developing on your computer

#### From the Command Line

- `cmake --preset default` -- developing on nuros
- `cmake --preset personal-computer` -- developing on your computer

<!--

### How the Program will Parse Numbers

When you run the *build/floatlab*, you will be prompted:

```
Enter a value, a two-operand arithmetic expression,
    "decode <value>", "recode <value>",
    or "quit":
```

When you enter a value, if it is prepended with ***`0x`*** then the parser will treat it as a bit vector;
otherwise, the parser will treat it as a floating point value.

For now, type ***`quit`*** to exit the program.


### Problem Decomposition

As was the case with IntegerLab -- as is the case for a great many problems -- FloatLab is best solved by decomposing it into smaller, manageable problems and then using the solutions to the smaller problems to solve the larger problem.
While the TAs' review of the IEEE 754 format is fresh on your minds, we recommend that you and your partner think about some bitmasks that would be useful for this lab.
After that, create some constants based on your understanding of IEEE 754.
You can then use some of the bitmasks and your understanding of IEEE 754 to create some simple functions to test qualities of an IEEE 754 formatted value.

With those small problems taken care of, you can use them to determine an IEEE 754 formatted value's mathematical value.
You'll first do this to be able to print a floating point value, and then you'll do this to convert a floating point number into a form that will make arithmetic easier.
Then you'll use your understanding of IEEE 754 to place a floating point value into the IEEE 754 format.

With those tasks complete, you have everything you need to apply your understanding of floating point arithmetic to implement the `add()`, `subtract()`, `multiply()`, and `divide()` functions.

-->

### Descriptions of DuplicatorLab Files

#### duplicatorlab.c

Do not edit *duplicatorlab.c*.

This file contains the driver code for the lab.
It checks whether the source file exists, creates file pointers for the two files, and calls the `duplicate()` function (described below).

#### duplicator.h

Do not edit *duplicator.h*.

This header file contains a named constant (`BUFFER_SIZE`) and function declarations for the functions in *duplicator.c*.

#### duplicator.c

This file contains the nearly-complete code that you will edit, as well as variables shared by the program's reading and writing threads.

The `duplicate()` function is called by *duplicatorlab.c*'s `main()` function, launches `read_original()` and `write_copy()` in their own threads, and keeps the process alive until copying is complete.
The `read_original()` function continuously reads lines from the source file and writes them to the shared buffer, while the `write_copy()` function continuously reads from the shared buffer and writes those lines to the destination file.

---

|                 |      [⬆️](../README.md)      |          [➡️](02-about-duplicator.md)          |
|:---------------:|:----------------------------:|:----------------------------------------------:|
|                 | [Front Matter](../README.md) | [About the Duplicator](02-about-duplicator.md) |
