## Polling Discussion

Polling, which you encountered in DuplicatorLab, is simply repeatedly checking whether some condition holds, and performing some action if it does.

<figure>
  <img src="images/polling/AreWeThereYet.png" width="50%" alt="The central family from 'The Simpsons' in a car. The children are repeatedly asking, 'Are we there yet? Are we there yet?'">
  <figcaption>Polling. <small> Image © 20th Century Fox Television.</small></figcaption>
</figure>

In this assignment, you will poll the pushbuttons, numeric keypad, and timer.


### Functions to Read the Buttons, Keypad, and Timer; and Functions to Write to the LEDs

The input functions in the CowPi library are [described in the datasheet](https://cow-pi.readthedocs.io/en/latest/CowPi/inputs.html).

- `cowpi_debounce_byte(cowpi_get_keypress(), KEYPAD)` returns a `char` with the ASCII representation of the character depicted on whichever key is pressed.
  - If no key is pressed, `cowpi_get_keypress()` returns `'\0'`
  - Because you will only be interested in decimal numerals, you can convert the character to a value by subtracting `'0'`,
    similar to how you converted uppercase letters to lowercase letters in KeyboardLab.
- `cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN)` returns `true` if the left button is pressed, and `false` otherwise.
- `cowpi_debounce_byte(cowpi_right_button_is_pressed(), RIGHT_BUTTON_DOWN)` returns `true` if the right button is pressed, and `false` otherwise.
- `get_microseconds()` returns a `uint32_t` with the value in the timer's lower word (this isn't a CowPi function but is provided specifically for this assignment).

The output functions in the CowPi library are [described in the datasheet](https://cow-pi.readthedocs.io/en/latest/CowPi/outputs.html).

- `cowpi_illuminate_left_led()` causes the left LED to light up.
- `cowpi_illuminate_right_led()` causes the right LED to light up.
- `cowpi_deluminate_left_led()` causes the left LED to go dark.
- `cowpi_deluminate_right_led()` causes the right LED to go dark.


### Detecting Key and Button Actions

Recall that the application code, including the `build_number()` function is called in each iteration of a `while(true)` loop.
This means that you can repeatedly call the I/O functions -- you can poll the inputs -- simply by calling the functions once in your `build_number()` function's body.

For inputs that you expect to "stick", such as the position of a slide switch, you generally expect your code to return the same value each time you read its input.
For "momentary" inputs like the pushbuttons and the keypad's keys, we expect a single press to be treated as exactly one press.
Since the `while(true)` loop runs hundreds of thousands of iterations per second, even the fastest-possible tap of a button will cause `cowpi_left_button_is_pressed()` to return `true` for several thousand iterations.
Code that doesn't take this into account will not treat that single press as exactly one press.

#### The input solution that you will *not* use

One option is to write your code to block until the button is released:
```c
if (cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN)) {
    ... do something ...
    while (cowpi_debounce_byte(cowpi_left_button_is_pressed(), LEFT_BUTTON_DOWN)) {}
}
```
The problem with this approach is that the system will be non-responsive until the user releases the button.

#### The input solution that keeps the system responsive

You can have a single press be treated as exactly one press while also keeping the system responsive by implementing three state machines: one for each pushbutton and one for the keypad.
The idea is that each of these inputs is in one of four possible states:
- If the input's state machine is in the *Not Pressed* state, it stays in that state until the input is pressed.
  When the input is pressed, the input's state machine transitions to the *Respond to Press* state.
- If the input's state machine is in the *Respond to Press* state, then the system takes whatever one-time action needs to be taken in response to the input being pressed.
  After this action is complete, the input's state machine transitions to the *Pressed* state.
- If the input's state machine is in the *Pressed* state, it stays in that state until the input is released.
  When the input is released, the input's state machine transitions to the *Respond to Release* state.
-  If the input's state machine is in the *Respond to Release* state, then the system takes whatever one-time action (if any) needs to be taken in response to the input being released.
  After this action is complete, the input's state machine transitions to the *Not Pressed* state.

![foo](images/polling/polling-states.svg)

You could implement a state machine using a `switch` statement, or you could implement a state machine using chained `if/else if/.../else` statements.


### Measuring the Passage of Time

If you want some duration of time to occur between two actions by the program, you again have two options: blocking and non-blocking.

#### The timer solution that you will *not* use

For very short periods, and for situations in which you do specifically want nothing else to happen, a busy-wait is an excellent choice.
When you scanned the keypad in ControlPanelLab, you used a busy-wait to introduce a 1µs delay between setting the rows' logic values and reading from the columns.
Similarly, if responsiveness during the wait is unimportant, a busy-wait is a simple, easy choice -- the driver code for the digital logic design portion of this assignment uses a 1,000,000µs busy-wait.
```c
    start = get_microseconds();
    while (get_microseconds() - start < 1000000) {}
    i = (i + 1) % 10;
```

#### The timer solution that keeps the system responsive

When you implement the number builder, there will be a requirement that LEDs be illuminated for a half-second (500,000µs) after button or key presses.
Illuminating the LED can be part of the input device's *Respond to Press* state.
Outside of the state machine, you can poll the timer to determine when to deluminate the LED.
```c
    // in the state machine
    cowpi_illuminate_whichever_led();
    start = get_microseconds();     // you'll want to use a different variable for each LED
    ...
    // outside the state machine
    if (get_microseconds() - start > 500000) {
        cowpi_deluminate_whichever_led();
    }
```


---

|          [⬅️](03-digital-logic-design.md)          |      [⬆️](../README.md)      |               [➡️](05-number-builder.md)                |
|:--------------------------------------------------:|:----------------------------:|:-------------------------------------------------------:|
| [Digital Logic Design](03-digital-logic-design.md) | [Front Matter](../README.md) | [Implementing the Number Builder](05-number-builder.md) |
