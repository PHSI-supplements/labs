## A Four-Function Calculator

- [ ] [Attach the Seven-Segment Display Module to the Cow Pi](BB-peripherals.md).
- [ ] Place the Cow&nbsp;Pi's **right** switch in the *right* position.
- [ ] Compile the program and upload it to the Cow&nbsp;Pi.

You now have a Cow&nbsp;Pi-based four-function calculator that can perform arithmetic on 16-bit signed integers.

- Use the decimal digit keys on the keypad to enter numbers.
- Use the letter keys on the keypad to specify the arithmetic operation (notice that these keys have supplementary labels for `+`, `-`, `×`, and `÷`).
  - When you specify an arithmetic operation, both LEDs will illuminate until you start building the next operand.
  - When you start building the next operand, a crude approximation of the arithmetic symbol will appear on the leftmost position of the seven-segment display.
- Use the left pushbutton to negate the number being built.
- Use the right pushbutton to clear the number being built.
  Use it a second time to clear the accumulator. 
- Use the `#` key on the keypad to indicate that the specified arithmetic operation should be performed (notice that this key has a supplementary label for `=`).
  - An arithmetic key will also cause a previously-specified arithmetic operation to be performed and then specify the next arithmetic operation.

Unfortunately, I doubt that the DLC will allow you to use the Cow&nbsp;Pi-based four-function calculator when taking an exam.


---

|               [⬅️](05-number-builder.md)                |      [⬆️](../README.md)      |         [➡️](07-grading.md)          |
|:-------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Implementing the Number Builder](05-number-builder.md) | [Front Matter](../README.md) | [Turn-In and Grading](07-grading.md) |
