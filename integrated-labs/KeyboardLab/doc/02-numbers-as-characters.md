> 📇 **Scenario**
>
> You've recently been hired to help the Pleistocene Petting Zoo get started.
> Your new employer, Archie, is surprisingly honest: he admits to you that some expenses were spared.
> Archie helpfully points out that any challenge is also an opportunity to succeed.
> You suspect your job will offer plenty of "opportunities to succeed."
>
> <!--![Meme from the original 'Jurassic Park' movie. Top: Hammond, with the caption 'Spares No Expense'. Bottom: Nedry, with the caption 'Hires One IT Guy'. Original images © Universal Studios and Amblin Entertainment, Inc. Meme creator unknown.](some-expenses-spared.png)-->
> <figure>
>   <img src="some-expenses-spared.png" width="50%" alt="Meme from the original 'Jurassic Park' movie. Top: Hammond, with the caption 'Spares No Expense'. Bottom: Nedry, with the caption 'Hires One IT Guy'.">
>   <figcaption>Some expenses were spared. <small>Original images © Universal Studios and Amblin Entertainment, Inc. Meme creator unknown.</small></figcaption>
> </figure>
---
> 📇 **Scenario, continued**
> 
> You soon discover your first ~~challenge~~...
> 
> You soon discover your first opportunity.
> Archie purchased your workstation from an electronics recycling warehouse, and the keyboard is missing the letter W!
> You decide to write an email requesting a new keyboard.

## Treating Numbers as Characters

The email needs to read:

```
To⇥Archie↵
RE⇥I Need a Working Keyboard↵
↵
Please order a new keyboard for me.  This one is broken.↵
```

(*Note*: here, the ⇥ symbol represents the TAB character, which is needed by the email program,
and the ↵ symbol represents the NEWLINE character.)

### TL;DR

- [ ] Edit `problem1.c` so that it produces the specified output without using the *W* key or the backslash key, and without `#include`ing or `#embed`ing any other files.
- [ ] Build the executable in your IDE or with the command: `cmake --build build`.
  Be sure to fix both errors and warnings.
- [ ] Run the executable in your IDE or with the command `build/keyboardlab` and select option 1 ("check problem 1").
  This will print your email message.
  - If it matches the intended email message, then you will be informed that it does.
  - If it does not match the intended email message, then the program will inform you where the first difference is between your message and the desired message and will print a small portion of each to show the difference.

### The Challenge

You quickly realize that you can't type this directly into your mail program because of the missing `W` key.
So you decide to write a short program that will output the text that you want to send.
The code you would like to write is:

```c
#include <stdio.h>
#include <string.h>

char *generate_email(char *destination, int destination_size) {
    snprintf(destination, destination_size, "%s",
             "TO\tArchie\n"
             "RE\tI Need a Working Keyboard\n"
             "\n"
             "Please order a new keyboard for me. This one is broken.\n");
    return destination;
}
```

(*Note*: `\t` and `\n` are the escape sequences that generate the TAB and NEWLINE characters.
They are *not* a literal backslash followed by a literal 't' or 'n'.)

### Discussion

Of course, the `W` and `w` are still a problem, but you realize you can insert those characters by using their ASCII values.

> 💡**Tip**
> 
> Use the ASCII table in Chapter 2 of the textbook.

For example, if the space bar were missing then you could replace
```c
printf("Hello World!\n");
```
with
```c
printf("%s%c%s\n", "Hello", 0x20, "World!");
```
or
```c
printf("%s%c%s\n", "Hello", 32, "World!");
```
because 0x20 (which is decimal 32) is the ASCII value for the space character (`' '`).
Recall that the first argument for `printf()` is a *format string*:
`%s` specifies that a string should be palced at that position in the output,
and `%c` specifies that a character should be placed at that position in the output.

(*Note*: the `snprintf()` function is very much like the `printf()` function, except that it "prints" into a string.
See Appendix C of the textbook.)

As you open your editor, the *\\* key falls off the keyboard, preventing you from typing `\t` and `\n`.
You carefully start typing, but as soon as you've finished with the two `#include` directives, the *3* key (which is also used for *#*) falls off of your keyboard.

### The Task

- [ ] Edit `problem1.c` so that it produces the specified output without using the *W* key or the backslash key, and without `#include`ing or `#embed`ing any other files.
- [ ] Build the executable in your IDE or with the command: `cmake --build build`.
  Be sure to fix both errors and warnings.
- [ ] Run the executable in your IDE or with the command `build/keyboardlab` and select option 1 ("check problem 1").
  This will print your email message.
  - If it matches the intended email message, then you will be informed that it does.
  - If it does not match the intended email message, then the program will inform you where the first difference is between your message and the desired message and will print a small portion of each to show the difference.

<font color="red">
You can double-check that you aren't using disallowed keys by running the constraint-checking Python script:

```
ctest --test-dir build --output-on-failure -R keyboardlab1
```
</font>

You will earn 3 points for replacing all occurrences of `W`, `w`, `\t` and `\n` with their ASCII values.
You will earn 1 point for also producing a string that perfectly matches the desired string.

---

|         [⬅️](01-lab-time.md)          |      [⬆️](../README.md)      |               [➡️](03-characters-as-numbers.md)               |
|:-------------------------------------:|:----------------------------:|:-------------------------------------------------------------:|
| [Lab Time Discussion](01-lab-time.md) | [Front Matter](../README.md) | [Treating Characters as Numbers](03-characters-as-numbers.md) |
