## 🧨 **Jumping the Guardrails**

> ⓘ **Note**
> 
> **After** you and your partner have both completed stages 0-4 under the normal collaboration rules,
> you may work together on the bonus credit up until the assignment is due.
> 
> You can also work on the bonus credit individually.

We expect you to conduct a certain type of buffer overflow attacks in each of the stages.
This assignment is written with guardrails in place to prevent other types of attack.
If you complete the expected attack successfully, then the program will terminate with an exit status of `0`
(on a Unix system, this is the conventional exit status for "success").

It's ~~possible~~ certain that it's possible to jump the guardrails.

There are two ways to earn bonus credit for this assignment.

> 📝 **Grading Note**
> 
> To receive any bonus credit, **you must complete the five stages using the intended attacks**.
> If you have not completed all five stages, you cannot receive bonus credit.
> If you find a way to jump the guardrails and use that to clear a stage without also conducting the intended attack,
> you will receive neither the bonus nor credit for clearing that stage.


### Attempt to Jump the Guardrails

Try to find *other* ways to make the program terminate with an exit status of `0`.
Can you make the program think it's in a different stage, allowing you to use a different attack than the intended one?
Can you make the program compare the expected student ID (integer or string version) to data that's already in the program instead of injecting the data?

Try to find any way to attack the program to circumvent the guardrails and make the program produce an exit code of `0`.

- [ ] Open the [BufferOverflowLab Bonus Credit](https://mynu.instructure.com/courses/13509/assignments/1028594) assignment in Canvas.
- [ ] In the Canvas assignment, describe each attempt to bypass the guardrails that you made, including:
  - Your "reconnaissance" that made you think that you might be able to achieve the bypass.
  - Broadly, how you were going to attempt to achieve that.
  - Your specific attack.
  - What happened when you made the attack.

You will receive up to 2 bonus points on the assignment for *attempting* to jump the guardrails.
How much of that bonus you get will depend on how persistent you were, 
how aggressive you were in your attempts,
and on how well you describe your attempts.


### Successfully Jump the Guardrails

In addition to the bonus for attempting to bypass the guardrails,
there is also a bonus for successfully doing so.

If you find an exploit that allows you to produce an exit code of `0` other than through the intended attack,
send Dr. Bohn an email or private Piazza message describing the exploit, including your attack string.

For each exploit discovered, we will award 1 additional bonus point to the first student or pair of students to discover the exploit.
This is in addition to the 2 bonus point they will almost certainly receive for attempting to jump the guardrails.

Dr. Bohn is the final adjudicator of whether two reported exploits are the same exploit or are distinct exploits.


### 🚧 Lab Still Under Construction

There is a guardrail not yet in place.
It is possible to use a system call to terminate the program with an exit code of 0.

For example, on x86-64, you would use the `syscall` instruction:
  ```asm
  mov $60, %rax     # set syscall callee to __NR_exit
  xor %rdi, %rdi    # __NR_exit's first arg is exit status -- set exit status to 0
  syscall
  ```

  or, on AArch64, you would use the `svc` (supervisor call) instruction:
  ```asm
  mov x8, #93       // set svc callee to __NR_exit
  mov w0, #0        // __NR_exit's first arg is exit status -- set exit status to 0
  svc #0
  ```

***<font color="red">
No bonus credit will be awarded for attacks that use a system call.
</font>***

---

|       [⬅️](10-fixing-code.md)        |      [⬆️](../README.md)      |         [➡️](12-grading.md)          |
|:------------------------------------:|:----------------------------:|:------------------------------------:|
| [Fixing the Code](10-fixing-code.md) | [Front Matter](../README.md) | [Turn-In and Grading](12-grading.md) |
