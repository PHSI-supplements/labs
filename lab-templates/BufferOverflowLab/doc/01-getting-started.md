## Getting Started

### TL;DR

- This is not a typical lab assignment.
  You will not need to edit anything in the `src/` directory,
  but you will need to [configure, build, and disassemble the project](#configuring-building-and-disassembling-the-project)
  *from the command line*.
- You will use [build/hex2raw](#hex2raw) to convert your attack strings from "hex format" into raw bytes.
- You will attack [build/target](#target) by exploiting a buffer overflow vulnerability to cause the program to run the target's checkpoint functions,
  one for each of the lab's stages.
- When you [run the target](#executing-the-target), if you provide no arguments then the target will print a help message.
  Otherwise, the possible command-line arguments are:
  - The stage number (`0`-`4`)
  - `print string` to print the "hex-formatted" input string
  - `print stack` to print stack snapshots
  - `print input stack` to print both
- You will [conduct your attacks](#conducting-an-attack) by using `build/hex2raw` to generate the raw bytes needed for your attack,
  and then send those bytes into `build/target`'s input stream.
  - [gdb](#using-gdb-during-your-attack) may be useful from time to time.
  - The [exit codes](#interpreting-exit-codes) encode information about what went right or wrong in your attack.

---

> 📇 **Scenario**
>
> You managed to keep the Pleistocene Petting Zoo from blowing to smithereens, but it turns out that Dr. Evil's minions weren't too careful when they put the bomb control software on the Zoo's Linux server.
> The software that controls many of the zoo's safety systems just unlocked all of the animal enclosure gates.
> The functions that control the safety systems are still present, but there's no way to activate those functions.
> Now the animals are out of their enclosures and are mingling with the guests.
> 
> The lead animal handler, Paul V. Love, suggests a plan.
> The animals are conditioned to go to their feeding pens when they hear a bell.
> Paul thinks that if we play the dinner bell over the PA system,
> then the specimens will return to their enclosures en route to their feeding pens.
> There's just the little problem that the software's user interface is now broken, so the necessary functions cannot be activated.
> 
> You then recall what Archie told you when he hired you: some expenses were spared. 
> You run the machine code through a disassembler and quickly see that it has a buffer overflow vulnerability. 
> Before the situation near the dire wolf enclosure gets too dire, you sit down and get to work.

During your lab period, the TAs will demonstrate how to construct and inject an exploit string.
The TAs will also demonstrate solving Stage 0.
During the remaining time, the TAs will be available to answer questions.


### Configuring, Building, and Disassembling the Project

> ❗️ **Important**
>
> The instructions are written assuming you will run the code on nuros.unl.edu.
> Specifically, the assembly code file is written for an x86-64 processor running a Linux operating system.
> If you wish, you may edit your attack strings in a different environment;
> however, you will not be able to generate a target executable on a Linux system,
> an attack designed for an Arm processor will not work on an x86 processor,
> and we will grade your attacks on nuros.

The project consists of the target's source code in the `src/` directory, and of <tt>stage*nn*.hex</tt> files in the `data/` directory.
You will not need to (and should not) edit the source code.
You *will* edit the <tt>stage*nn*.hex</tt> files, as these are where you will construct your buffer overflow attacks.

You may use any editor you wish, including an IDE, to edit the <tt>stage*nn*.hex</tt> files,
but your attacks are best conducted from the command line, and the instructions assume that you will do so.

#### Configuring the Project from the Command Line

- `cmake --preset default`

#### Building a Target from the Command Line

- `cmake --build build`

This will create two executable binaries, `build/target`, which is the program you will attack,
and `build/hex2raw`, which is a tool you will use during your attacks.

#### Disassembling the Target

- `objdump -d build/target > data/target.d`

This will provide you with the assembly code for your target.
More than that: it will provide you with the addresses of each function and each instruction,
and it will provide you with the encoding of each instruction (which may be useful when looking for ROP gadgets).


### Understanding the Project's Binaries

#### hex2raw

The `hex2raw` tool reads a "hex-formatted" input and produces the raw bytes that correspond to the input string.
The input is read from `stdin`, and the output is printed on `stdout`,
so you can use Unix input/output redirection or piping to send those bytes into the target's input stream.
For example:
```shell
% build/hex2raw < data/stage0.hex > data/stage0.raw
% build/target 0 < data/stage0.raw
```
or
```shell
% build/hex2raw < data/stage0.hex | build/target 0
```

The "hex-format" is a string of hex digits separated by horizontal or vertical whitespace.
For example, the string "Hello" could be entered in hex format as `48 65 6C 6C 6F 00`
(these being the hexadecimal ASCII values for the letters, followed by string's terminating `NUL` byte.)
As shown in the [example.hex](../data/example.hex) file, you can include comments and arbitrary spacing to make it easier for you to construct and remember the contents of your attack strings.


#### target

The target of your attacks is a program that has been designed to be vulnerable to a buffer overflow attack, but with guardrails.
Depending on the lab stage, certain vulnerabilities will be present or absent, and certain protections will be present or absent.

At the core, however, is the buffer overflow vulnerability in this function:

```c
size_t get_input(void) {
    char buffer[BUFFER_SIZE];
    printf("\nSYSTEM READY > ");
    gets(buffer);
    printf("\n\n");
    return get_input_size();
}
```

The actual `get_input` function has more code as part of those guardrails and some instrumentation.
The actual call to `gets` is actually a call to a `get_s` function that behaves like `gets` but also captures information about the input string so that helpful diagnostic information can be provided to you if you need it.

Your task in each of the lab stages is to cause the program to run one of the checkpoint functions,
most of which expect an argument.
The checkpoint function will check to see if your attack gives it what it expects, generating an exit code based on what happens.
If you cause the program to terminate with an exit code of `0` (the standard exit code for "success"),
then you will have cleared the stage.

The checkpoint functions are:
- Stage 0: `activate_pa_system`
- Stage 1: `ring_dinner_bell`
- Stage 2: `lock_carnivore_enclosures`
- Stage 3: `lock_herbivore_enclosures`
- Stage 4: `unlock_zoo_gates`


### Executing the Target

If you execute the target without any arguments, it will provide a help message:

```
% build/target

[INFO] Usage:
[INFO]   target <stage-number> [print (input|stack)+]
[INFO]
[INFO] Arguments:
[INFO]   <stage-number>  Required integer in the range [0, 4]
[INFO]   print           Enable printing of diagnostic data
[INFO]     input         Print your input
[INFO]     stack         Print stack snapshots

[INFO] Student ID (integer):  1234567 (0x0012d687)
[INFO] Student ID (string): "01234567"

[SCENARIO]
...

[GRADING] Stage 0 not cleared: diagnostic 40.
```

BufferOverflowLab has five stages, numbered 0 through 4.
Each stage requires a different attack.
You specify which stage you're attacking with a command-line argument.
For example, to attack stage 0:

```
% build/target 0
[SCENARIO]
...

SYSTEM READY >
```

The system is waiting for an input from `stdin`.
We can provide it with an input (this example does not overflow the buffer):

```
SYSTEM READY > hello

[ERROR] There was no exploit.
[INFO] The input consisted of 6 bytes.

[SCENARIO]
...

[GRADING] Stage 0 not cleared: diagnostic 2.
```

You can also direct the target to print out your input and/or snapshots of the program stack;
these may be useful when troubleshooting a failed attack:
```
% build/target 0 print input
...
SYSTEM READY > hello

[INFO] Your input:
[INFO] 68 65 6C 6C 6F 00
[INFO] (6 bytes)
...
```

When printing stack snapshots, you'll see three snapshots:
- The left column is the stack before the call to `get_s` (higher addresses are in the upper-left; lower addresses are in the lower-right)
- The middle column is the stack after the call to `get_s` (in the lower-right, you can see the bytes for "Hello")
- If the program had reached a checkpoint function, then the right column would show the stack after that function's prologue had executed 

```
% build/target 0 print stack
...
SYSTEM READY > hello
...
[INFO]
  initial stack             resulting stack           after (null)'s prologue
| 6B 63 61 74 73 00 74 6E | 6B 63 61 74 73 00 74 6E | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 40 1D 90 | 00 00 00 00 00 40 1D 90 | 00 00 00 00 00 00 00 00 |
| 00 00 00 07 FF EF 3B D0 | 00 00 00 07 FF EF 3B D0 | 00 00 00 00 00 00 00 00 |
| 00 30 00 00 00 40 10 3C | 00 30 00 00 00 40 10 3C | 00 00 00 00 00 00 00 00 |
| 00 00 00 07 FF EF 3B E0 | 00 00 00 07 FF EF 3B E0 | 00 00 00 00 00 00 00 00 |
| 1F 28 C0 24 FC C4 C9 00 | 1F 28 C0 24 FC C4 C9 00 | 00 00 00 00 00 00 00 00 |
| FF FF FF 80 FF FF FF D0 | FF FF FF 80 FF FF FF D0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 07 FF EF 3B B0 | 00 00 00 07 FF EF 3B B0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 07 FF EF 3B E0 | 00 00 00 07 FF EF 3B E0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 07 FF EF 3B E0 | 00 00 00 07 FF EF 3B E0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |
| FF FF FF 80 FF FF FF D0 | FF FF FF 80 FF FF FF D0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 40 1C D0 | 00 00 00 00 00 40 1C D0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 07 FF EF 3B 30 | 00 00 00 07 FF EF 3B 30 | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 40 0E F4 | 00 00 00 00 00 40 0E F4 | 00 00 00 00 00 00 00 00 |
| 00 00 FF FF BE 3B 9C A0 | 00 00 FF FF BE 3B 9C A0 | 00 00 00 00 00 00 00 00 |
| 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 | 00 00 00 00 00 00 00 00 |
| 00 00 FF FF E2 2E 2B 40 | 00 00 00 6F 6C 6C 65 68 | 00 00 00 00 00 00 00 00 |
  buffer = 0x7ffef3ab0                                             sp = (nil)
```


### Conducting an Attack

For stage *nn*, place your attack string in the <tt>data/stage*nn*.hex</tt> file.
You will use the `hex2raw` tool to convert the string into the raw bytes that you want to inject
and use Unix input/output redirection or piping to send those bytes into the target's input stream.
For example:
```shell
% build/hex2raw < data/stage0.hex > data/stage0.raw
% build/target 0 < data/stage0.raw
```
or
```shell
% build/hex2raw < data/stage0.hex | build/target 0
```

#### Using gdb during your attack

You can run your attack inside gdb:
```shell
% gdb build/target
```

In gdb, after setting breakpoint(s), launch the attack:
```
(gdb) run 0 < stage0.raw
```

You can monitor the initial part of the attack at the C level:
```
(gdb) layout src
```
or at the assembly level:
```
(gdb) layout asm
```

If you're only running the attack in gdb to learn the buffer's address, either will work.

If you want to observe your injected code run, or observe the ROP gadgets run, then you will need to observe it at the assembly level.


#### Interpreting exit codes

At the end of your attack, the program will tell you whether you succeeded or not and, if not, why not.
For example:
```
[SUCCESS] Congratulations! You reached activate_pa_system, successfully clearing stage 0.
...
[GRADING] Stage 0 cleared.
```
or
```
[WARNING] The pointer to your string is a dangling pointer.
[ERROR] You reached lock_carnivore_enclosures with student id "iu*&^S13JK*()p", which is not the correct student id.
[INFO] This error might have been caused by your string getting clobbered.
...
[GRADING] Stage 2 not cleared.
```

You can also check the exit code, which (unless things go very badly) is a bitwise-OR of possible errors:
- 0x00 - success
- 0x01 - (not used)
- 0x02 - no exploit (either there was no buffer overflow, or the overflow was insufficient to affect the program's flow of control)
- 0x04 - misaligned stack pointer
- 0x08 - incorrect function argument
- 0x10 - incorrect checkpoint function
- 0x20 - detected an attempt to skip over some of the checks made by the checkpoint function
- 0x40 - unsuccessful initialization (not a problem with your attack)

If bit7 is a 1 (0x80-0xFF) then something happened that required the operating system to intervene.
The program's ability to provide diagnostic information is limited in this situation, *because* the OS briefly took control.
The program can, however, provide the category of error:
- 0x82 - you pressed control-C
- 0x83 - you pressed control-\
- 0x84 - the processor attempted to read an instruction, but the bytes do not correspond to an assembly code instruction
- 0x86 - the program received an "abort" signal
- 0x87 - an error happened on the memory bus
- 0x88 - a math error happened, such as division by zero
- 0x89 - the program received a "kill" signal
- 0x8B - segmentation fault
- 0x8F - the program received a "terminate" signal


---

|                 |      [⬆️](../README.md)      |                  [➡️](02-stack-frame.md)                  |
|:---------------:|:----------------------------:|:---------------------------------------------------------:|
|                 | [Front Matter](../README.md) | [What Does the Stack Frame Look Like?](02-stack-frame.md) |
