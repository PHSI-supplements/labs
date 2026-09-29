## Tips, Tricks, and Gotchas

### Useful GDB Commands

Launch GDB: `gdb build/bomb`

#### You'll probably want these commands immediately after launching gdb

| GDB Command                | What it does                                                                                                                                                                                                                                                                                      |
|:---------------------------|:--------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------------|
| `tui enable`               | Activates the text user interface for a more interactive experience                                                                                                                                                                                                                               |
| `layout asm`               | Instructs the TUI to show assembly code instead of C code (GDB doesn't have the C code for phases.c)                                                                                                                                                                                              |
| `set step-mode`            | Instructs GDB to advance assembly instruction-by-assembly instruction instead of trying to find HLL debugger symbols                                                                                                                                                                              | 
| `break phase_1`            | Sets a breakpoint at the start of `phase_1()` (obviously, use whichever phase you're about to tackle)                                                                                                                                                                                             |
| `break explode_bomb`       | Sets a breakpoint at the start of `explode_bomb()` -- if we were penalizing explosions, this would stop the program before running the code that records the explosion (this semester we are not penalizing explosions)                                                                           |
| `tui reg general`          | Adds a sub-window to the TUI to show all of the general-purpose registers and highlight changes with each step -- if your terminal is tall enough, having a sub-window for the registers, a sub-window for the assembly code, and a sub-window for commands is a powerful combination for BombLab |
| `set args data/inputs.txt` | Sets "data/inputs.txt" as the first command-line argument to the program (be sure to set this *before* using the `run` command)                                                                                                                                                                   |
| `run` or `r`               | Launches the program in the debugger                                                                                                                                                                                                                                                              |

#### Stepping through the program

| GDB Command                                                         |                      abbreviation                      | What it does                                                                 |
|:--------------------------------------------------------------------|:------------------------------------------------------:|:-----------------------------------------------------------------------------|
| `refresh`                                                           |                                                        | Redraws the TUI, which may get garbled after the program prints              |
| `break <where>`                                                     |                      `b <where>`                       | Sets a breakpoint at `<where>` in the program                                |
| `delete <number>`                                                   |                      `d <number>`                      | Deletes breakpoint `<number>`                                                |
| `clear`                                                             |                                                        | Deletes all breakpoints                                                      |
| `tbreak <where>`                                                    |                      `tb <where>`                      | Temporarily sets a breakpoint at `<where>` that gets deleted after one break |
| `info break`                                                        |                                                        | Lists the breakpoings that you have set                                      |
| `step`                                                              |                          `s`                           | Advance one instruction, stepping into function calls                        |
| `next`                                                              |                          `n`                           | Advance one instruction, stepping over function calls                        |
| `finish`                                                            |                          `f`                           | Finishes executing the current function and then breaks                      |
| `continue`                                                          |                          `c`                           | Continues execution until the next breakpoint                                |
| `print <expression>` or `print/[format-specifier] <expression>`     | `p <expression>` or `p/[format-specifier] <expression` | Prints `<expression>` as a value (or address); does not dereference pointers |
| `x <expression>` or `x/[format-specifier> <expression>`             |                                                        | Dereferences `<expression>` to show the contents of memory                   |
| `display <expression>` or `display/[format-specifier] <expression>` | `d <expression>` or `d/[format-specifier] <expression` | Runs `x ...` after each step                                                 |
| `undisplay <number>`                                                |                   `undisp <number>`                    | Stops displaying display `<number>`                                          |
| `kill`                                                              |                          `k`                           | Kills the program in the debugger                                            |
| `run`                                                               |                          `r`                           | Launches the program in the debugger                                         |
| `quit`                                                              |                          `q`                           | Exits the debugger                                                           |

In BombLab,
- `<where>` can be:
  - A function name (`break phase_2`)
  - An address (`break *0xAAAAE752E78C`)
- `<number>` is a literal number
- `<expression>` can be:
  - A register (`p/c $rbx` prints the contents of $rbx as a character; `x/dw $sp` prints the 32-bit value at the top of the stack in decimal)
  - An address (`x/s 0xAAAAE752E78C` prints the string that starts at address 0xAAAAE752E78C)
  - A register plus an offset (`x/xw $sp+4` prints the 32-bit value that's 4 bytes above the top of the stack in hexadecimal)
  - A previously-used expression (`p $3` prints the third expression to have been printed)
- The optional `[format-specifier]` is described in the next subsection

#### Format specifiers for `print` and `x` and `display`

When specifying how to output a value or address you're inspecting, the general form is
```text
command/[length][format][size] <expression> 
```

- **Format** (`print`, `x`, and `display`)
  - Address: `a`
  - Binary: `t` ('t' for "two")
  - Character: `c`
  - Floating point value: `f`
  - Decimal: `d` ; unsigned decimal: `u` 
  - Hexadecimal: `x` ; zero-padded hexadecimal: `z`
  - Instruction: `i`
  - String (NUL-terminated: `s`)
- **Size** (`x` and `display`)
  - Byte (8 bits): `b`
  - Halfword (16 bits): `h`
  - Word (32 bits): `w`
  - Giant word (64 bits): `g`
- **Length** (`x` and `display`)
  - number indicating how many bytes/halfwords/words/giant words should be displayed

Examples:
- Show a string at address 0x123456
  - `x/s 0x123456`
- Show a character in register rax
  - `p/c $rax`
- Show four integers in memory starting at the address in register rdi
  - `x/4d $rdi`
- After each step, show the 16 words in hexadecimal that are at the top of the stack
  - `display/16xw $sp`


### Useful Extras

A file with the disassembled code can be useful for a big-picture view, when you want to see more of the program than can fit in your terminal.
If you run the command
```bash
objdump -d build/bomb > data/bomb.d
```
Then you can open *data/bomb.d* in an editor (or print it out) for reference.
If you print it out on paper, don't print out the whole thing, only the program's functions that are called by *bomb.c*'s `main()` function, and any function whose name begins with "fun".

Pen and paper, or a whiteboard (physical or electronic) can be useful for making notes as you step through the program.


### Tips from the TAs

- If you see assembly instruction that you don't recognize, consult the textbook's [Appendix A](https://unl.grlcontent.com/compeng2e/page/appendixa) or ask CodeHelp.
  - If the instruction doesn't appear in Appendix A, you can claim it as a bug bounty (unless someone else claimed it first).
- You do not need to understand every instruction before you can understand the phase.
  - Identify the comparisons and control flow that determine whether the function returns or calls `explode_bomb()`.
    Focus on calculations and memory accesses that matter to that.
- Don't step into library functions like `sscanf()` or support functions like `read_six_numbers()`.
  There's nothing there that will help you with the lab.
  - If you do step into a library or support function, use GDB's `finish` to exit the function.
- Pay attention to the function signatures for `sscanf()` and `read_six_numbers()`, so you know where the inputs end up at.
  - The convention for which registers are used for each argument are in the textbook's [Chapter 6](https://unl.grlcontent.com/compeng2e/page/appendixa) and [Appendix A](https://unl.grlcontent.com/compeng2e/page/appendixa).
- If the program loads a single byte from memory, there's a good chance that it's a character.
- On x86, an `lea` instruction might be used to compute an address, or it might be used for some funky arithmetic to compute a value.
- On Arm, if `adrp` is followed immediately by `add`, think of them as a single action to place an address in a register.


### Things that might trip you up

#### DOS line breaks versus UNIX line breaks

- <u>The problem</u> <br>
  Windows ends a line with `\r\n` but Linux ends a line with `\n`.
  - It'd been several years since this last caused us problems, but as we saw with KeyboardLab, it's causing us problems again
- <u>What to remember</u> <br>
  If a BombLab phase expects a string as an input, and you provided the correct input but the bomb still explodes:
  one possibility is that you have a typo.
  Another possibility (if your host computer runs Windows) is that mismatched line breaks caused `\r` to be treated as part of the input.
  - If you edit *inputs.txt* with Vim inside the container, you should be fine
  - If you edit *inputs.txt* with VS Code, make a habit of running `dos2unix data/inputs.txt` after you save the file, to convert DOS-style line breaks to UNIX-style line breaks

#### Comparisons

- <u>The problem</u> <br>
  `cmp` compares two values, but which is on which side of the comparison $a \circ b$?
  If you see `cmp opr1, opr2` and then subsequent `b.lt` (Arm) or `jl` (x86) instruction,
  will the program branch when $opr1 < opr2$ or when $opr2 < opr1$?
- <u>What to remember</u> <br>
  `cmp` subtracts one operand from the other (but doesn't save the difference) to set the status flags.
  The operands are the same order as the subtraction instruction.
  - x86: `sub src, dest` computes $dest - src$, so `cmp opr1, opr2` compares $opr2 \circ opr1$
  - Arm: `subs dest, src1, src2` computes $src1 - src2$, so `cmp opr1, opr2` compares $opr1 \circ opr2$ [^cmpFunFact]

[^cmpFunFact]: Fun fact: in the A64 instruction set, `cmp src1, src2` encodes as `subs xzr, src1, src2`. Since register xzr is read-only, the instruction performs the subtraction and sets the flags without saving the difference. 

#### Branching without a comparison

- <u>The problem</u> <br>
  You might see a conditional branch/jump that isn't preceded by a `cmp` or `tst` instruction.
- <u>What to remember</u> <br>
  Status flags are also set by arithmetic.
  If the compiler can save an instruction by using the flags that are already being set by arithmetic, it will do so.
  This is often found in loops, though you may see it elsewhere, too.
  - x86: all arithmetic instructions (except `lea`) set the status flags
  - Arm: instructions that end with `s` set the status flags (*e.g.*, `adds` sets the flags, but `add` doesn't)

#### `bl` versus `blt`

- <u>The problem</u> (Arm only) <br>
  When you see `bl`, is that "branch on less than"?
- <u>What to remember</u> <br>
  `bl` is a function call ("branch and link").
  `blt` is "branch on less than".
  - On Arm, all conditional suffixes are two letters ("less than" is `lt`)
  - In the disassembled code, the conditional suffix is separated from the core mnemonic by a dot -- so branch-on-less-than appears as `b.lt`
  - If the destination is a different function, it's a function call; if the destination is in the same function, it's not a function call

#### Printing an address versus printing the contents of memory

- <u>The problem</u> <br>
  You have a register that holds a pointer, and when you try to print it, you get what's in the register instead of what's at the address.
- <u>What to remember</u> <br>
  `print` (or `p`) prints a value.
  `x` ("examine") treats a value as an address and dereferences it, allowing you to examine memory.
  - `p $rbx` (x86) or `p $x4` (Arm) will print the content of x86 register `rbx` or Arm register `x4`
    - If it's an address, and you're intentionally printing the address, you probably want `p/a $rbx` or `p/a $x4`
  - `x $rbx` or `x $x4` will treat the register's content as a pointer and show you the memory it points to
    - You'll probably want to use format specifiers to indicate how much memory to examine and how to interpret what's found there

#### Don't confuse GDB variables with AT&T syntax

- <u>The problem</u> <br>
  You've gotten used to prefacing registers with `%` and immediate values with `$` (x86 only) but in GDB you preface registers with `$` literal values don't have a prefix, and a number with a `$` prefix isn't a number.
- <u>What to remember</u> <br>
  GDB needs to distinguish between program variables and debugger variables.
  Debugger variables start with `$` in case there's a program variable by the same name.
  - Registers are treated as debugger variables, so x86 register rax (%rax in AT&T syntax) is `$rax` and Arm register x0 is `$x0`
  - Whenever you print an expression, GDB creates a sequentially-numbered debugger variable for the result:
    `$1` is the result of the first expression you print, `$2` is the result of the second expression you print, and so on 

<!--

#### ...

- <u>The problem</u> <br>
  ...
- <u>What to remember</u> <br>
  ...

-->


---

|         [⬅️](03-bomb.c.md)          |      [⬆️](../README.md)      |         [➡️](05-grading.md)          |      
|:-----------------------------------:|:----------------------------:|:------------------------------------:|      
| [Partial Source Code](03-bomb.c.md) | [Front Matter](../README.md) | [Turn-In and Grading](05-grading.md) |      
