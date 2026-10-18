## Stage 0: Simple Buffer Overflow on the Stack

> 📇 **Scenario, continued**
>
> The first part of the plan to get the animals back into their enclosures is to turn on the PA system.
> You've located the helpfully-named `activate_pa_system` function;
> now you need to make it run.


In stage 0, you want to cause the program to run the `activate_pa_system` function.
This function does not take any arguments.
Your task is to overwrite a return address with the address of `activate_pa_system`,
so that when the vulnerable function returns, it will "return" to the start of `activate_pa_system` instead of to its caller.

> 📝 **Grading Note**
> 
> We will look for your attack string in `data/stage0.hex`.

[//]: # (TODO: Consider splitting this into ISA-specific pages)


### Determine the Size of your Attack String

- [ ] If you did not already do so, disassemble your target:
  ```shell
  objdump -d build/target > data/target.d
  ```
- [ ] Open `data/target.d` and locate the `get_input` function.
- [ ] Using the information from the discussion about stack frames ([A64](02-stack-frame-a64.md), [x86-64](02-stack-frame-x86-64.md)),
  study the function's prologue to determine how large `get_input`'s stack frame is.
  - Look for the space used to save registers and the space allocated for local variables.
- [ ] Your attack will overwrite the return address;
  determine where the return address is stored within the stack frame.
  > ⓘ **Note**
  > 
  > On AArch64, the return address you overwrite might be in the caller's frame.
  > (See the earlier [discussion about the AArch64 stack](02-stack-frame-a64.md#aarch64-stack-frame-with-a-small-buffer).)
- [ ] Within `get_input()`, locate the function call to `get_s`.
- [ ] Shortly before the function call will be a line of code that places the buffer's address into the first-argument register (`%rdi` for x86-64<!--, `x0` for AArch64, `r0` for AArch32-->).
  Locate that line of code and determine where the start of the buffer is relative to the address in the stack pointer (*i.e.*, relative to the low-address end of the stack frame).
- [ ] Knowing where the buffer begins and where the return address is stored, determine how large your attack string needs to be so that you overwrite the return address.


### Plan Your Attack

- [ ] In `data/target.d`, locate the `activate_pa_system` function and note its address.
- [ ] Open `data/stage0.hex` in a text editor of your choice.
- [ ] Fill `stage0.hex` with enough padding bytes to reach from the start of the buffer until just before the start of the return address.
  - These bytes are only used for padding, so it doesn't matter what the bytes are.
- [ ] After the padding bytes, place the bytes for `activate_pa_system`'s address.
  - Since this is a little-endian system, don't forget to reverse the bytes in the address when you type them.

For example, if there were 16 bytes between the start of the buffer and the start of the return address,
and if `activate_pa_system`'s address were 0x1234'5678 then you would put something like this in `stage0.hex`:

[//]: # (TODO distinguish between 64-bit example and 32-bit example)
```
00 00 00 00 00 00 00 00    // 00 is a common choice for padding
3E 3E 3E 3E 3E 3E 3E 3E    // something a visually-distinctive is also a good choice
78 56 34 12 00 00 00 00    /* activate_pa_system */ 
```

- [ ] Save `stage0.hex`


### Conduct Your Attack

- [ ] Use the `hex2raw` tool to convert your attack string into raw bytes,
  and use Unix input/output redirection or piping to send those bytes into the target's input stream.

For example:
```shell
build/hex2raw < data/stage0.hex | build/target 0
```

or
```shell
build/hex2raw < data/stage0.hex > data/stage0.raw
build/target 0 < data/stage0.raw
```


#### Unsuccessful Attack

If your attack doesn't successfully cause `activate_pa_system` to run, you'll be given some indication of why:
```
[ERROR] Oops! Segmentation Fault.

[SCENARIO]
...

[GRADING] Stage 0 not cleared: diagnostic 8b.
```

The error message tells you, broadly, what happened in your attack.
The diagnostic code in the grading note is a hexadecimal representation of the [exit code](../src/target/exit-codes.h) that would have been reported to the grader and generally conveys the same information.
You may need to have the system print your input and/or stack snapshots to better understand why the error occurred.


#### Successful Attack

A successful attack will result in one of two outputs:
```
[SUCCESS] Congratulations! You reached activate_pa_system, successfully clearing stage 0.

[SCENARIO]
...

[GRADING] Stage 0 cleared.
```

On an x86-64 system, you may see this:

```
[INFO] You reached activate_pa_system!
[WARNING] Your stack pointer is misaligned, but this is okay (even expected) in stage 0.
[WARNING] In later stages, you should think about how to preserve %rsp's alignment.
[SUCCESS] Congratulations! You reached activate_pa_system, successfully clearing stage 0.

[SCENARIO]
...

[GRADING] Stage 0 cleared.
```

On an x86-64 system, it is easy to enter a checkpoint function with a misaligned stack pointer,
and in stage 0 there's only one way to correct for that.
So we allow credit for stage 0 with a misaligned stack pointer on an x86-64 system.

In later stages you'll have many options to ensure the stack pointer is properly aligned when entering a checkpoint function.
If your attack would cause a misaligned stack pointer, we'll expect you to think of one of these options and incorporate it into your attack.
You will want to review [the discussion about x86-64 stack alignment](02-stack-frame-x86-64.md#x86-64-stack-alignment).
Reflect on why -- in *normal* operation, when the program arrives at the start function from a function call -- an x86-64 function's prologue must re-align the stack pointer to a 16-byte boundary.
Reflect also on why your stage 0 attack -- which caused the program to arrive at a function from a `ret` instruction -- resulted in the function's prologue causing the stack pointer's alignment to be off by 8.

Your planned attack in later stages may or may not result in a misaligned stack pointer.
You will find it to be less frustrating if you anticipate whether it will or won't, and make sure that it won't.

(On an AArch64 system, it is easy to avoid having a misaligned stack pointer by always using `ldp` when popping off of the stack.)


---

|                                     [⬅️ A64](02-stack-frame-a64.md) <br> [⬅️ x86-64](02-stack-frame-x86-64.md)                                     |      [⬆️](../README.md)      |            [➡️](04-student-id.md)            |
|:--------------------------------------------------------------------------------------------------------------------------------------------------:|:----------------------------:|:--------------------------------------------:|
| [What Does the Stack Frame Look Like? (A64)](02-stack-frame-a64.md) <br> [What Does the Stack Frame Look Like? (x86-64)](02-stack-frame-x86-64.md) | [Front Matter](../README.md) | [What is Your Student ID?](04-student-id.md) |
