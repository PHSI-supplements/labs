> 📇 **Scenario, continued**
>
> Archie replies to your email, assuring you that a new keyboard has been ordered.
> Meanwhile, he needs you to write some code that will convert uppercase letters to lowercase letters and to indicate whether a character is a decimal digit.
> 
> At first, this seems to be easy work since those actual functions are part of the standard C library with their prototypes in `ctype.h`.
> As you get ready to impress everyone with how fast you can "write" this code by calling those standard functions, you remember that your keyboard is missing the *3* key (which is also used for *#*), preventing you from typing `#include <ctype.h>`.
> As you're pondering this, the *s* key falls off.
> Several number keys fall off soon thereafter: only *0*, *7*, and *9* remain.
> The *f* key is looking fragile, so you decide that you had better not type too many `if` statements
> (and without the *s* key, you can't use a `switch` statement at all).

## Treating Characters as Numbers

As you look at the loose keys littering your desk, you remember that `char` is just another integer type,
and all the arithmetic and comparisons that can use `int`s as operands can also use `char`s as operands.
For example, `('a' + 1 == 'b')` and `('c' < 'd')` are both perfectly valid, true expressions.

> ⓘ **Note**
>
> Your solution should not need the number `7`;
> the *7* key is retained so that you can use a logical AND (`&&`) if you need to.

### The Task

- [ ] Edit *problem2.c* so that:
  - `iz_digit()` returns 1 if the character is a decimal digit ('0', '1', '2', ...) and 0 otherwise
    > 💡 **Tip**
    >
    > $9 \div 9 = 1$
  - `decapitalize()` will return the lowercase version of an uppercase letter ('A', 'B', 'C', ...) but will return the original character if it is not an uppercase letter

You may not `#include` any headers, you may not use any number keys other than the *0*, *9*, and *7* (which is used for *&*) keys, you may not use *S* or *W*, and you may use at most two *F*s.}

> 📖 **Readability Tip**
> 
> Your code will be more readable if it does not depend on any characters' ASCII values, nor in the relative positions of upper- and lowercase letters in the ASCII table, only that:
> - digits are in a contiguous sequence in the ASCII table (sorted from the least to the greatest value)
> - the lowercase letters are in a contiguous sequence (sorted alphabetically)
> - the uppercase letters are in a contiguous sequence (sorted alphabetically)

- [ ] Build the executable in your IDE or with the command `cmake --build build`.
    Be sure to fix both errors and warnings.
- [ ] Run the executable in your IDE or with the command `build/keyboardlab` and select option 2 ("check problem 2"). \\
  You will be prompted to enter a character, and the program will use that character to compare the outputs of your functions to the reference functions from `ctype.h`.
  - When testing `decapitalize()`, be sure to test it using uppercase letters, lowercase letters, and characters other than letters.

<font color="red">
You can double-check that you aren't using disallowed keys by running the constraint-checking Python script:

```
ctest --test-dir build --output-on-failure -R keyboardlab2
```
</font>

The `iz_digit()` function is worth four points, two for correctly determining that a character is a digit and two for correctly determining that a character is not a digit.
Partial credit is available for determining that a character is a digit but returning a non-zero value other than 1, and partial credit is available if you fail to determine that a non-printable character is not a digit.
You will receive no credit if you simply hard-code a return value, such as `return 0`.

The `decapitalize()` function is worth four points, two for converting uppercase letters to lowercase, one for returning unmodified lowercase letters, and one for returning unmodified non-letter characters.
You will receive no credit if you always return the original character, such as `return character` or otherwise do not attempt the task.

[//]: # (You will receive one bonus point if your correct solutions to `iz_digit&#40;&#41;` and `decapitalize&#40;&#41;` do not depend on specific ASCII values, nor in the relative positions of upper- and lowercase letters in the ASCII table.)

---

|               [⬅️](02-numbers-as-characters.md)               |      [⬆️](../README.md)      |                [➡️](04-bit-operations.md)                |
|:-------------------------------------------------------------:|:----------------------------:|:--------------------------------------------------------:|
| [Treating Numbers as Characters](02-numbers-as-characters.md) | [Front Matter](../README.md) | [Using Bitmasks and Shifting Bits](04-bit-operations.md) |
