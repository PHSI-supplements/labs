## Getting Started

> 📇 **Scenario**
>
> In a jarring collision of movie franchises, the CEO of Virtucon makes a Zoom call to the Pleistocene Petting Zoo.
> For some reason that nobody really explains, you're the only person available to handle the situation. 
> The guy, who sounds kind of like an animated ogre, demands that the Pleistocene Petting Zoo deliver to him a megalodon shark with a head-mounted laser capable of emitting a beam of pure antimatter.
> 
> You blurt out, "Then it's not a laser," 
> and then try to explain to him that megalodons are from the Miocene epoch, 
> and expecting to find them at the Pleistocene Petting Zoo would be as ridiculous as a Cretaceous-period tyrannosaur at a Jurassic-themed park.
> 
> "Zip it!" commands the guy who kind of looks like the host of a public-access show you used to watch.
> "Since you won't meet my demand, my minions have placed a 'binary bomb' under your zoo. 
> Because I like really convoluted plans, we put software on your Linux server that controls the bomb. 
> If you do nothing, the bomb will explode.
> If you turn off the Linux server, the bomb will explode.
> If you go slower than 50mph, the bomb will -- no, never mind that last part.
> 
> "The bomb software consists of a sequence of phases. 
> Each phase expects you to type a particular string on `stdin`.  
> If you type the correct string, then the phase is *defused* and the bomb proceeds to the next phase.
> Otherwise, the bomb *explodes*. The bomb is defused when every phase has been defused.
> 
> 
> "Your mission, which you have no choice but to accept, is to defuse your bomb before the due date.  
> Good luck, and welcome to the bomb squad!"

During your lab period, the TAs will demonstrate how to disassemble a program and how to use gdb to examine the state of a process and to step through its execution. 
The TAs will also demonstrate solving Phase 1.
During the remaining time, the TAs will be available to answer questions.


### Explosions

To encourage understanding the bomb's assembly code, and to discourage brute-forcing the bomb, each time you enter an incorrect input, the bomb will ***<font color="red">EXPLODE!</font>***
While this isn't a literal explosion, the `explode_bomb()` function will terminate the program.


### *Inputs.txt*

The bomb is designed to be able to take all of its input from the keyboard, or to take some of its input from *data/inputs.txt* and the rest from the keyboard.
When you have the input to solve a phase, put it in *data/inputs.txt* for two reasons:

- It will save you the hassle of re-typing that input as you solve subsequent phases, and
- We will use your *data/inputs.txt* for grading

> 📝 **Grading Note**
>
> We will look for your inputs in *data/inputs.txt*.
> Even if you use `stdin` for all of your inputs when defusing the bomb,
> be sure that your inputs are in *data/inputs.txt* and that you push it to your repository so that we can confirm your inputs for grading.


### Run BombLab in the Terminal Only

You can edit *data/inputs.txt* in your editor of choice, but **you must run BombLab in the terminal**, in the course container.
(There's no pedagogical reason for this; it's simply that activating VS Code's memory view, which should be very useful for BombLab, interferes with the debugger's behavior.)

After [rebuilding the container image](../README.md#rebuild-the-docker-image), launching the container, and descending into the *BombLab* directory:

- Do once
  ```bash
  cmake --preset default
  objdump -d build/bomb > data/bomb.d
  ```
- Do everytime
  ```bash
  gdb build/bomb
  ```

Elsewhere, we have documented some [useful GDB commands](04-tips.md#useful-gdb-commands).

> ⓘ **Note**
>
> When you run the bomb in GDB, you will see this warning:
> ```text
> warning: Error disabling address space randomization: Operation not permitted
> ```
> You can ignore that for now.
> We'll discuss what that means when we go over the Chapter 7 material.


---

|                 |      [⬆️](../README.md)      |       [➡️](02-defusing-a-bomb.md)        |
|:---------------:|:----------------------------:|:----------------------------------------:|
|                 | [Front Matter](../README.md) | [Defusing a Bomb](02-defusing-a-bomb.md) |
