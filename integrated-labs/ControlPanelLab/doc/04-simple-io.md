## Time, and Simple Memory-Mapped Input/Output

In this section, you will use the data structures provided by the CowPi library to access the RP2040's memory-mapped I/O registers.


### Reading a Timer

Because you have already [assigned an address to the `timer` pointer](03-labtime.md#determine-the-base-address-for-the-timer-registers),
you can use the `timer` pointer to access the `cowpi_timer_t` structure, which overlays the RP2040's general-purpose timer.
You will use the `raw_lower_word` field to access the lower 32&nbsp;bits of the timer's value.
No debouncing code is necessary because, while the timer's value can be thought of as an input, it is not a mechanical switch.

- [ ] Locate the `get_microseconds()` function.

In the starter code, the `get_microseconds()` function is implemented by calling the Arduino `micros()` function to report the time elapsed (in microseconds) since the microcontroller was powered-up.

The \processor's timer value increments every microsecond.

- [ ] Replace the call to `micros()` with code that uses the `timer` pointer to obtain the timer's value.
  - [ ] Read from the timer's `raw_lower_word` field and return that value.


### Test your get_microseconds function

- [ ] Place the **right switch** in the *right* position and upload your code.

The output will show the elapsed time, a small fraction of a second.
Whenever you press/release a key, press/release a button, or toggle a switch, the display will update the elapsed time.

- [ ] Open your smartphone's clock app, and go to the stopwatch feature.
- [ ] Press the Cow&nbsp;Pi's RESET button and the stopwatch's START button at the same time.
- [ ] Press a button on the Cow&nbsp;Pi a few times, comparing the elapsed time on the stopwatch and the elapsed time on the Cow&nbsp;Pi's display.


---


Because you have already completed [assigned an address to the `ioport` pointer](03-labtime.md#determine-the-base-address-for-the-io-port-registers),
you can use the `ioport` pointer to access the `cowpi_ioport_t` structure that overlays the data pins' registers.
You will use the `.input` field with bitmasks to read inputs, and
you will use the `.output` field with bitmasks and the **read-modify-write** pattern to write outputs.
During lab, the TAs covered reading from inputs and using the read-modify-write pattern to write outputs;
however, if you missed lab or have forgotten, you can find examples in the section of the Cow&nbsp;Pi datasheet that [discusses the `cowpi_ioport_t` structure](https://cow-pi.readthedocs.io/en/latest/CowPi_rp2040/io_registers.html#structure-for-memory-mapped-input-output).

### Simple Inputs

- [ ] Locate the `left_button_is_pressed()`, `right_button_is_pressed()`, `left_switch_in_right_position()`, and  `right_switch_in_right_position()` functions.

In the starter code, these functions are implemented by calling functions in the CowPi library.

- [ ] Replace the calls to CowPi library functions with code that uses the `ioport` pointer to ascertain the controls' positions.<br>
  <font color="red">Do *not* remove the calls to `debounce_byte()`!</font>


#### Test your simple input functions

- [ ] Place the **right switch** in the *left* position, and upload the program to your Cow&nbsp;Pi.

The output will include the positions of the left and right buttons ("U" for up and "D" for down) and of the left and right switches ("L" for left position and "R" for right position).


### Simple Outputs

- [ ] Locate the `set_right_led()` function.

In the starter code, this function is implemented by calling functions in the CowPi library.

- [ ] Modify `set_right_led()` to replace the calls to CowPi library functions with code that uses the `ioport` pointer to turn the LED on or off.
  - [ ] Use the read-modify-write pattern to do so, so that you do not change any pins that you do not intend to change.
  - No debouncing code is necessary because these functions do not read from mechanical switches.

    
### Test your simple output function

- [ ] Upload the program to your Cow&nbsp;Pi.

If the **right button** is *pressed* while the **right switch** is in the *right* position then the right LED will illuminate.
Otherwise, the right LED will not illuminate.


---

|             [⬅️](03-labtime.md)              |      [⬆️](../README.md)      |             [➡️](05-keypad.md)             |
|:--------------------------------------------:|:----------------------------:|:------------------------------------------:|
| [Initial Changes to the Code](03-labtime.md) | [Front Matter](../README.md) | [Scanning the Matrix Keypad](05-keypad.md) |
