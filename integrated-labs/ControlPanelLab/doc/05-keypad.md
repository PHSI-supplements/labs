## Scanning the Matrix Keypad

Now that you have some practice with using memory-mapped I/O to read from and write to external pins, you can demonstrate your understanding by combining reads and writes to deduce which key (if any) on the keypad is being pressed.

- [ ] Locate the `get_keypress()` function.

The implementation in the starter code calls the CowPi library's `cowpi_get_keypress()` function.
The `cowpi_get_keypress()` function returns a `char` corresponding to the character on the pressed key,
but the `get_keypress()` function is supposed to return a `uint8_t` that has the hexadecimal value of the pressed key (considering `#` as 0xE and `*` as 0xF).
Because of this, the rest of the implementation is a pair of `switch` statements to obtain the correct value from the `keys` nested array.

- [ ] Read the section of the Cow Pi datasheet that [discusses the matrix keypad](https://cow-pi.readthedocs.io/en/latest/hardware/inputs.html#matrix-keypad), including the pseudocode.

After you have done so:

- [ ] Preserve the debouncing code in `get_keypress()`, and
- [ ] Replace the starter code's call to `cowpi_get_keypress()` and its `switch` statements with code that scans the keyboard.
  - [ ] Use the ioport` pointer to read from and write to the appropriate pins,
  - [ ] Use a 1&nbsp;µs busy-wait (see below) for the delay shown on line 4 of the pseudocode in the datasheet, and
  - [ ] Use the `keys` nested array to obtain the correct integer value for the key at a given row and column.


### What is a busy-wait?
A busy-wait is a loop that does nothing until some criterion is satisfied.
```c
    while (!condition_is_satisfied) {}
```

In this case, the condition to be satisfied as that at least one microsecond has elapsed since the busy-wait started.

- [ ] Use `get_microseconds()` to obtain the time immediately before the busy-wait.
- [ ] In the busy-wait, compare that with the "current" value obtained by `get_micrseconds()` to see if at least one microsecond has elapsed.


### Suggestions

Examine the pseudocode in the datasheet and relate it to the "theory of operation."

> ⓘ **Note**
> 
> The pseudocode uses the "walrus operator" (`:=`) for assignments and the "equal sign" (`=`) for equality comparisons, as is common in ALGOL-inspired languages.
> This is in contrast to C-inspired languages that use the "equal sign" for assignment and the "double equal sign" for equality comparisons.

> 💡 **Tip**
> 
> Even though the pseudocode is expressed as nested loops, you do not need to implement it that way.
> We have seen implementations that have an outer loop for the rows and an inner loop for the columns,
> and we have seen implementations that have a loop for the rows but use a `switch` statement or chained `if` statements to enumerate the possibilities for the columns.
> With four rows and four columns, both are viable solutions.

The key insights are:
- Each of the row vectors you output will have exactly one "0" bit;
  the placement of that "0" corresponds to exactly one of the rows in the `keys` nested array, and
- Each of the column vectors you read as input, if it is not 0xF, will have exactly one "0" bit;
  the placement of that "0" corresponds to exactly one of the columns in the `keys` nested array

Even though possible set the loop conditions to terminate the loop as soon as the pressed key has been determined,
it would be better to keep your loop conditions simple and allow the code to examine all sixteen keys.
With only sixteen keys, there isn't much time savings to be had by ending the loop as soon as the key has been found,
and in a "real" embedded system, our time budget would have to allow enough time to examine all sixteen keys and so any "savings" gained by ending the loop early would be lost to sitting idle later.


#### Test your get_keypress function

- [ ] Place the **right switch** in the *left* position, and upload the program to your Cow&nbsp;Pi.

The output will include the key that was pressed (if any), a hyphen if no key is being pressed, or a question mark if `get_keypress()` returns an invalid value.


---

|                     [⬅️](04-simple-io.md)                      |      [⬆️](../README.md)      |         [➡️](06-grading.md)          |
|:--------------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Time, and Simple Memory-Mapped Input/Output](04-simple-io.md) | [Front Matter](../README.md) | [Turn-In and Grading](06-grading.md) |
