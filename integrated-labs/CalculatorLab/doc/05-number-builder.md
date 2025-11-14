> 📇 **Scenario continued**
>
> "Excellent!"
> Herb is clearly pleased with your BCD-to-seven-segment-decoder.
> "The next thing we need is the ability to enter numbers into the calculator."
> Herb calls up the project's issue tracker.
> "You work on building numbers, and I'll write up the code to connect that to an ALU and to track the calculator's state."

## Implementing the Number Builder

In this part of the assignment, you will implement a system to "build numbers" one digit at a time, like you would with a calculator.
For this part of the assignment, you do not need the seven-segment display;
the driver code will place the number being built on row 0 of the Cow&nbsp;Pi's display.

- [ ] Place the Cow&nbsp;Pi's **right** switch in the *left* position, and the **left** switch in the *right* position.
- [ ] Compile the program and upload it to the Cow&nbsp;Pi.

The top row of the Cow&nbsp;Pi's display will simply show `0`.


### TL;DR

In `build_number()`:
- [ ] Prepare [state machines](04-polling.md#the-input-solution-that-keeps-the-system-responsive) for the keypad, the left pushbutton, and the right pushbutton.
- [ ] Add code to the keypad state machine to detect a keypress and set `number` to the key's face-value, while keeping the system responsive to other inputs.
- [ ] Add code to the **left** button's state machine to detect a button press and negate `number`, while keeping the system responsive to other inputs.
- [ ] Add code to the **right** button's state machine to detect a button press and set `number` to 0, while keeping the system responsive to other inputs.
- [ ] Add code to illuminate the **left** LED whenever a key is pressed and deluminate the LED a half-second later, while keeping the system responsive to further inputs.
- [ ] Add code to illuminate the **right** LED whenever either pushbutton is pressed and deluminate the LED a half-second later, while keeping the system responsive to further inputs.

Then:
- [ ] Implement `process_digit()` to compute a new number, given the previous number and the new digit.
- [ ] Update `build_number()` to update `number` with the value returned by `process_digit()`.
- [ ] Implement `overflow_occurred()` to report whether overflow occurred for the cases of
  - Negating -32768
  - Negating any other number
  - Building positive numbers
  - Building negative numbers
- [ ] Update `build_number()` to set `overflow` to `true` when overflow occurs, and to update `number` only when overflow doesn't occur.
- [ ] Update `build_number()` to set `overflow` to `false` when the right button is pressed.


### Examine the Starter Code

- [ ] Open *number_builder.c*

- There are three functions that you will implement, `build_number()`, `process_digit()`, and `overflow_occurred()`.
- There is a defined type, `input_states_t`, that you will use when implementing the [inputs' state machines](04-polling.md#the-input-solution-that-keeps-the-system-responsive). 
- There are three variables defined for you:
  - `buffer`, which you may use with `sprintf()` and `display_string()` if you wish to place debugging messages on the display.
  - `number`, which your code will update.
  - `overflow`, which your code will update.
- There are three accessor/mutator functions that the driver code will use to read and reset `number` and `overflow`.


### Reading a Digit from the Keypad

In the `build_number()` function:
- [ ] Add code to [determine which (if any) key is being pressed](04-polling.md#functions-to-read-the-buttons-keypad-and-timer-and-functions-to-write-to-the-leds).
- [ ] Add either chained `if`/`else if` blocks, or a `switch` statement that will transition `keypad_state` between states according to the input state machine [described earlier](04-polling.md#the-input-solution-that-keeps-the-system-responsive).

Keep things simple for now, to catch errors when they're easier to troubleshoot.
- [ ] In the keypad state machine's `RESPOND_TO_PRESS` state, determine whether the character returned by `cowpi_get_keypress()` is a decimal digit.
- If it is a digit:
  - [ ] Convert the digit character into the digit's value ($0 ≤ value ≤ 9$).
  - [ ] Assign that value to `number`.

#### Check your work

- [ ] Compile the program and upload it to the Cow&nbsp;Pi.
- [ ] Confirm that pressing a key with a decimal digit causes the display to show that digit.
- [ ] Confirm that releasing that key does not cause the number shown to change.
- [ ] Check each of the ten decimal digits.
- [ ] Confirm that pressing a key that does not have a decimal digit (`A`, `B`, `C`, `D`, `*`, `#`) does not cause the number shown to change.


### Negating a Number

Our calculator will use the **left** button to negate a value being entered.

In the `build_number()` function:
- [ ] Add code to determine whether the **left** pushbutton is being pressed.
- [ ] Add either chained `if`/`else if` blocks, or a `switch` statement that will transition `left_button_state` between states according to the input state machine [described earlier](04-polling.md#the-input-solution-that-keeps-the-system-responsive).
- [ ] In the left button state machine's `RESPOND_TO_PRESS` state, negate `number`.

#### Check your work

- [ ] Compile the program and upload it to the Cow&nbsp;Pi.
- [ ] Press a non-zero digit key (for example, `4`); the number should appear on the display.
- [ ] Press the **left** button; confirm that the negated value is now on the display (for example, `-4`).
- [ ] Press the **left** button again; confirm that the original value is now on the display (for example, `4`).


### Clearing a Number

In the `build_number()` function:
- [ ] Add code to determine whether the **right** pushbutton is being pressed.
- [ ] Add either chained `if`/`else if` blocks, or a `switch` statement that will transition `right_button_state` between states according to the input state machine [described earlier](04-polling.md#the-input-solution-that-keeps-the-system-responsive).
- [ ] In the right button state machine's `RESPOND_TO_PRESS` state, set `number` to 0.

#### Check your work

- [ ] Compile the program and upload it to the Cow&nbsp;Pi.
- [ ] Press a non-zero digit key (for example, `4`); the number should appear on the display.
- [ ] Press the **right** button; confirm that the display now shows `0`.
- [ ] Press the **right** button again; confirm that the display still shows `0`.


### Managing the LEDs

The LEDs should indicate that a button has been pressed.
We want the left LED to light up in response to the user pressing a key on the keypad,
and we want the right LED to light up in response to the user pressing one of the pushbuttons.
In both cases, we want the LED to remain lit for a half-second and then go dark.

- [ ] Add variables to `build_number()` to track the times of the last key press and the last button press.
  *These variables need to ``remember'' their values between calls to `build_number()`.*
- [ ] In each of the aforementioned state machines, add code to note the time that a press occurred.
- [ ] Add code to `build_number()` to illuminate the **left** LED when a key on the keypad has been pressed and then deluminate it a half-second later.
- [ ] Add code to `build_number()` to illuminate the **right** LED when either pushbutton has been pressed and then deluminate it a half-second later.
  
  > 📝 **Grading Note**
  >
  > Be sure the to [keep the system responsive](04-polling.md#the-timer-solution-that-keeps-the-system-responsive) during the half-second illumination.

#### Check your work

- [ ] Compile the program and upload it to the Cow&nbsp;Pi.
- [ ] Press a key on the keypad.
  - The **left** LED should illuminate and then deluminate a half-second later.
- [ ] Press the **left** pushbutton.
  - The **right** LED should illuminate and then deluminate a half-second later.
- [ ] Press the **right** pushbutton.
  - The **right** LED should illuminate and then deluminate a half-second later.
- [ ] Push several keys on the keypad rapidly in succession.
  - The number should continue to update even while the LED is illuminated.
- [ ] Rapidly alternate between pressing a key on the keypad and pressing one of the pushbuttons.
  - The number should continue to update even while the LEDs are illuminated.
  

### Building a Number

Viewed as a weighted sum, an $n$-digit decimal number $d_{n-1}d_{n-2}{\dots}d_2d_1d_0$ has the value

$$number = \sum_{i=0}^{n-1}d_i \times 10^i$$

When building a number digit-by-digit, whenever you introduce a new digit, $d_{new}$ where $0 \leq d_{new} < 10$, it will be the least-significant digit (that is, its weight will be "times 1"),
and all pre-existing digits will increase in significance by one order of magnitude.
So the new value is

$$
new\_number = \left(\sum_{i=0}^{n-1}d_i \times 10^{i+1}\right) + \left(d_{new} \times 1\right)
$$ $$
\phantom{new\_number} = \left(\sum_{i=0}^{n-1}d_i \times 10^i \times 10\right) + d_{new}
$$ $$
\phantom{new\_number} = \left(10 \times \sum_{i=0}^{n-1}d_i \times 10^i\right) + d_{new}
$$ $$
\phantom{new\_number} =  10 \times number + d_{new}
$$

Thus, if you're building a positive decimal number, you update the number by multiplying the old value by 10 and adding the new digit.
If you're building a negative number, the idea is similar except that you'll subtract the new digit.

Locate the `process_digit()` function.
- [ ] Add code to compute the new number, considering:
  - Whether the digit is a valid digit
  - Whether the old number is negative or non-negative
- [ ] Return the new number.

In `build_number()`:
- [ ] Modify the keypad state machine's `RESPOND_TO_PRESS` state to update `number` with the value returned by `process_digit()`.

#### Check your work

- [ ] Compile the program and upload it to the Cow&nbsp;Pi.
- [ ] Confirm that pressing a key does not cause the number to update a few hundred thousand times for a single keypress
- [ ] Confirm that you can "build" a number by pressing number keys.
  - Build both positive and negative numbers.
  - You do not yet detect overflow, so values greater than 32,767 and less than -32,768 will wrap-around the number wheel.


### Detecting Overflow

In Chapter 3, you learned two ways to detect signed integer overflow: 
compare the most significant bit's carry-in and carry-out bits,
and compare the operands' signs and the result's sign.

You do not have access to the carry bits, so you will need to rely on comparing signs.
Notice in the [earlier discussion](#building-a-number) that when `number` is positive, you're adding the new digit and should get a new positive number,
and when `number` is negative, you're subtracting the new digit and should get a new negative number.
So, a straight-forward overflow check can simply compare the sign of the new and old numbers.

There is an exception: if you negate a number, the new and old numbers will have opposite signs, 
and you typically wouldn't expect this to cause overflow.
You might be tempted to not check for overflow when the user negates the number, but there is a special case that must be considered:
*What value do you get if you negate -32,768 and place it in an `int16_t` variable?*

[//]: # (TODO: re-introduce the two-step overflow detection for microcontrollers with 16-bit `int`s)

Locate the `overflow_occurred()` function.
- [ ] Add code for the case of `old_number` being `INT16_MIN`.
- [ ] Add code for the case of all other negations.
- [ ] Add code for the case of building a positive number.
- [ ] Add code for the case of building a negative number.

In `build_number()`:
- [ ] Modify the keypad state machine's `RESPOND_TO_PRESS` state to determine whether the value returned by `process_digit()` overflowed.
- [ ] If the value overflowed, then set `overflow` to `true`, and do *not* update `number`.
- [ ] Modify the left button state machine's `RESPOND_TO_PRESS` state to determine whether negating `number` would overflow.
- [ ] If negation causes overflow, then set `overflow` to `true`, and do *not* update `number`.
- [ ] Modify the left button state machine's `RESPOND_TO_PRESS` state to set `overflow` to `false` 

#### Check your work

- [ ] Compile the program and upload it to the Cow&nbsp;Pi.
- [ ] Confirm that attempting to build a number greater than 32,767 fails and sets the `overflow` flag.
- [ ] Confirm that building positive numbers less than 32,768 succeeds.
- [ ] Confirm that attempting to build a negative number less than -32,768 fails and sets the `overflow` flag.
- [ ] Confirm that building negative numbers greater than -32,769 succeeds.
- [ ] Confirm that clearing a number also clears the `overflow` flag.
- [ ] Confirm that negating any number other than -32,768 succeeds.
- [ ] Confirm that attempting to negate -32,768 fails and sets the `overflow` flag


---

|         [⬅️](04-polling.md)         |      [⬆️](../README.md)      |             [➡️](06-calculator.md)             |
|:-----------------------------------:|:----------------------------:|:----------------------------------------------:|
| [Polling Discussion](04-polling.md) | [Front Matter](../README.md) | [A Four-Function Calculator](06-calculator.md) |
