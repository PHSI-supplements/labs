## Defusing a Bomb

Your job for this lab is to defuse your bomb.

[//]: # (You must do the assignment on nuros. )
[//]: # (In fact, there is a rumor that Dr.&nbsp;Evil really is evil, and the bomb will always blow up if run elsewhere.  )
[//]: # (There are several other tamper-proofing devices built into the bomb as well, or so we hear.)

You can use many tools to help you defuse your bomb. 
The best way is to use your favorite debugger to step through the disassembled binary.

[//]: # (TODO: VS Code wants a launch.json file -- see the video I prepared a few years ago -- and we'll have to figure out how to prevent premature explosions &#40;not this semester&#41;)
[//]: # (TODO: CLion wants a predefined target -- and we'll have to test whether it has VS Code's premature explosion problem &#40;not this semester&#41;)

[//]: # (Each time your bomb explodes it notifies the bomblab server, and you lose $\frac{1}{4}$ point &#40;up to a max of 25 points&#41; in the final score for the lab.)
[//]: # (So there are consequences to exploding the bomb. )
[//]: # (You must be careful!)

- The first four phases are worth 6-9 points each, for a total of 30 points.
- Phases 5 and 6 are a little more difficult, so they are worth 10 points each, for a total of 20 points.
- There is also extra credit, and you will discover how to obtain the extra credit only by thoroughly studying the bomb code to glean its secrets.

Although phases get progressively harder to defuse, the expertise you gain as you move from phase to phase should offset this difficulty. 
However, the last phase will challenge even the best students, so please don't wait until the last minute to start.

The bomb ignores blank input lines. 
If you run your bomb with a command line argument, for example,
```shell
build/bomb data/inputs.txt
```
then it will read the input lines from *data/inputs.txt until it reaches `EOF` (end of file), and then switch over to `stdin`. 
In a moment of weakness, Dr.&nbsp;Evil added this feature so you don't have to keep retyping the solutions to phases you have already defused.

> 📝 **Grading Note**
>
> We will look for your inputs in *data/inputs.txt*.
> Even if you use `stdin` for all of your inputs when defusing the bomb,
> be sure that your inputs are in *data/inputs.txt* and that you push it to your repository so that we can confirm your inputs for grading.

To avoid accidentally detonating the bomb, you will need to learn how to single-step through the assembly code and how to set breakpoints.
You will also need to learn how to inspect both the registers and the memory states.
***The TAs will demonstrate how to do these during lab time.***
One of the nice side effects of doing the lab is that you will get very good at using a debugger.
This is a crucial skill that will pay big dividends the rest of your career.


### Approaches

There are many ways of defusing your bomb.
- You can examine it in great detail without ever running the program, and figure out exactly what it does.  
  This is a useful technique, but it not always easy to do.
- You can run it under a debugger, watch what it does step by step, and use this information to defuse it.
  This is probably the fastest way of defusing it.
- Do not attempt to brute force the bomb.
  - We haven't told you how long the strings are, nor have we told you what characters are in them.  
    Even if you made the (incorrect) assumptions that they all are less than 80 characters long and only contain letters, then you will have $26^{80}$ guesses for each phase.
    This will take a very long time to run, and you will not get the answer before the assignment is due.

### Tools

There are many tools which are designed to help you figure out both how programs work, and what is wrong when they don't work.  
Here is a list of some of the tools you may find useful in analyzing your bomb, and hints on how to use them.

- **gdb** <br>
  The GNU debugger, this is a command line debugger tool available on virtually every platform.
  You can trace through a program line by line, examine memory and registers, look at both the source code and assembly code (we are not giving you the source code for most of your bomb), set breakpoints, set memory watch points, and write scripts.
  Here are some tips for using `gdb`.
  - To keep the bomb from blowing up every time you type in a wrong input, you'll want to learn how to set breakpoints.
  - Canvas has useful documents on gdb available on this lab's assignment page.
  - For online documentation, type `help` at the gdb command prompt,
    or type `man gdb`, or `info gdb` at a Unix prompt.
  - Some people also like to run gdb under `gdb-mode` in emacs.
    - *n.b.*, The course container does not include emacs because relatively few people use it.
      If you prefer emacs, talk with Dr. Bohn before modifying the Dockerfile.
- **objdump -d** <br>
  Use this to disassemble all of the code in the bomb.
  You can also just look at individual functions.
  Reading the assembler code can tell you how the bomb works.
  <!--
  - Although `objdump -d` gives you a lot of information, it doesn't tell you the whole story.
    Calls to system-level functions are displayed in a cryptic form.
    For example, a call to `sscanf` might appear as:
    ```asm
    16e7:       e8 44 fb ff ff          call   1230 <__isoc23_sscanf@plt>
    ```
    for x86-64, or
    ```asm
    1564: 97fffeb3      bl      0x1030 <__isoc23_sscanf@plt>
    ```
    for A64.
    To determine that the call was to `sscanf`, you would need to disassemble within gdb. -->
- **objdump -t** <br>
  This will print out the bomb's symbol table.
  The symbol table includes the names of all functions and global variables in the bomb, the names of all the functions the bomb calls, and their addresses.
  You may learn something by looking at the function names!
- **strings** <br>
  This utility will display the printable strings in your bomb.

Looking for a particular tool?
How about documentation?
Don't forget, the commands `apropos`, `man`, and `info` are your friends.
In particular, `man ascii` might come in useful. 
`info gas` will give you more than you ever wanted to know about the GNU Assembler.
If you get stumped, feel free to ask your TA for help.


---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |         [➡️](03-bomb.c.md)          |      
|:----------------------------------------:|:----------------------------:|:-----------------------------------:|      
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Partial Source Code](03-bomb.c.md) |      
