## Initial Changes to the Code

During your lab period, the TAs will guide the class through the first modifications to the starter code that you must make, described in this section.
If you do not attend your lab period, then you must complete this section on your own.
***Except during lab time, you may *not* discuss the solutions for this section with other students.***


### Populate the Keypad's Lookup Table

Locate the `keys` $4 \times 4$ nested array on lines 34-39 of *io_functions.c*.
This nested array serves as a lookup table to obtain the appropriate value when a key is pressed.
*Even the starter code depends on this nested array being populated correctly.*
The element `keys[0][0]` will correspond to the `1` key;
`keys[0][3]` will correspond to the `A` key;
`keys[3][0]` will correspond to the `*` key;
and `keys[3][3]` will correspond to the `D` key.

We want the numerals `0`-`9` to produce their respective decimal (and hexadecimal) values.
We want `A`-`D` to produce their respective hexadecimal values.
We want `\#` to produce the hexadecimal value 0xE, and we want `*` to produce the hexadecimal value 0xF.

- [ ] Populate `keys`' nested array initializer so that the lookup table will produce the correct value for each row/column combination.


#### Test your lookup table

You can confirm that you correctly populated the array's initializer by running the program on the Cow Pi.

- [ ] Place the **right switch** in the *left* position, and upload your code.
  (Or, if you have already uploaded your code, position the switch and press the RESET button.)

The display will show the key that was pressed (if any), a hyphen if no key is being pressed, or a question mark if `get_keypress()` returns an invalid value.

```c
     ...
344  if (key_pressed <= 0x0F) {
345      sprintf(output, "%2X%5c%2c%4c%2c",
346              key_pressed,
347              left_button_position ? 'D' : 'U', right_button_position ? 'D' : 'U',
348              left_switch_position ? 'L' : 'R', right_switch_position ? 'L' : 'R');
349  }  else {
350      sprintf(output, "%2c%5c%2c%4c%2c",
351              key_pressed == 0xFF ? '-' : '?',
352              left_button_position ? 'D' : 'U', right_button_position ? 'D' : 'U',
353              left_switch_position ? 'L' : 'R', right_switch_position ? 'L' : 'R');
354  }
     ...
```

Familiarize yourself with the test code's other outputs.
The output will include the positions of the left and right buttons ("U" for up and "D" for down) and of the left and right switches ("L" for left position and "R" for right position).

Finally, if the left switch is in the right position and the left button is pressed, then the left LED will illuminate.
Similarly, having the right switch in the right position while pressing the right button will cause the right LED to illuminate.

```c
     ...
324  set_left_led(left_switch_is_in_right_position() && left_button_is_pressed());
325  set_right_led(right_switch_is_in_right_position() && right_button_is_pressed());
     ...
```


### Determine the Base Addresses of Certain I/O Register Banks

In most of this assignment, you will use a `cowpi_ioport_t` structure to access the memory-mapped I/O registers for the RP2040's data pins.

You will also use a pointer to a `cowpi_timer_t` structure to determine how much time has elapsed since the system was powered-up.


#### Determine the Base Address for the I/O Port Registers

Read the section of the Cow&nbsp;Pi datasheet that [discusses the `cowpi_ioport_t` structure](https://cow-pi.readthedocs.io/en/latest/CowPi_rp2040/io_registers.html#structure-for-memory-mapped-input-output).
(During the guided discussion in your lab period, the TAs may direct you to particular parts of that section of the datasheet,
but be sure to go back and read the full section covering [input/output pins](https://cow-pi.readthedocs.io/en/latest/CowPi_rp2040/io_registers.html#external-pins-input-output) later.)
After you have done so,

- [ ] Uncomment the `ioport = ...` line of the starter code's `initialize_io()` function, and
- [ ] Assign the appropriate address to the `ioport = ...` pointer on that line.

```c
48  void initialize_io(bool key_mode) {
49      show_key_press = key_mode;
50      // Uncomment these lines and set the correct addresses during lab time
51      // ioport = (cowpi_ioport_t *) (0x00000000);
52      // timer = (cowpi_timer_t *) (0x00000000);
53  }
```

> ⚠️ **Warning**
> 
> If you skipped lab time and need to look up the base address for the I/O port registers on your own,
> ***consult the section of the Cow&nbsp;Pi datasheet that [discusses the `cowpi_ioport_t` structure](https://cow-pi.readthedocs.io/en/latest/CowPi_rp2040/io_registers.html#structure-for-memory-mapped-input-output).***
> If you consult a different source, you may find a plausible-sounding but incorrect address.

You can now use the `ioport` pointer to access the microcontroller pins' inputs and outputs.


#### Determine the Base Address for the Timer Registers

Read the section of the Cow&nbsp;Pi datasheet that [discusses the timer registers](https://cow-pi.readthedocs.io/en/latest/CowPi_rp2040/io_registers.html#timers).
After you have done so,

- [ ] Uncomment the `timer = ...` line of the starter code's `initialize_io()` function, and
- [ ] Assign the appropriate address to the `timer` pointer on that line.

Later in this assignment, you will use the `timer` pointer to access the timer's memory-mapped registers to read its counter.


### Detect Whether a Key on the Numeric Keypad Has Been Pressed

The next part of the group activity is detecting when someone is pressing a key on the numeric keypad.
The `key_is_pressed()` function in the starter code is:

```c
66  static bool key_is_pressed(void) {
67      // this is four distinct reads to figure out if any of the column pins has a 0 on it -- can you do it in one read?
68      bool key_is_pressed = !(digitalRead(10) && digitalRead(11) && digitalRead(12) && digitalRead(13));
69      return cowpi_debounce_long(key_is_pressed, INPUT_X);
70  }
```

Line&nbsp;68 uses the Arduino function `digitalRead()` to read the values on the four pins attached to the keypad's columns.
If any of those pins has a 0 on it, then a key has been pressed (see section of the Cow Pi datasheet that [discusses the matrix keypad](https://cow-pi.readthedocs.io/en/latest/hardware/inputs.html#matrix-keypad)).
The next line [debounces](02-debouncing-debugging.md#debouncing) that reading.

One problem is that the `digitalRead()` function is part of the Arduino core and, as noted in the [constraints](../README.md#constraints), you may not use functions from the Arduino core.
The other problem is that the `digitalRead()` function can read only one pin at a time, and so there are four distinct reads.
Now that you have the base address for the `ioport` structure,
you can use memory-mapped I/O to replace the calls to `digitalRead()`,
and you can do so in a manner that obtains the values on all four pins at the same time.

If you are currently in your lab period, then work with the other students in your lab section to determine the answers to these questions.
If you are not attending your lab period, then work individually to determine the answers to these questions.

- [ ] Using the datasheet's [Table&nbsp;22](https://cow-pi.readthedocs.io/en/latest/CowPi_rp2040/io_registers.html#id16):
  - What bitmask should you use?
  - What should line&nbsp;68 look like? 
- [ ] Replace line&nbsp;68 with code that reads from a memory-mapped input register to determine whether a key is being pressed.


#### Test your keypress detection

You can confirm that you correctly detected a change on the keypad by running the program on the Cow Pi.

- [ ] Place the **right switch** in the *right* position and upload your code.
  (Or, if you have already uploaded your code, position the switch and press the RESET button.)

The display will indicate whether a key is being pressed, and also the elapsed time since the system was powered up.


### Controlling an LED

The final part of the group activity is illuminating and deluminating the left LED.
Locate the `set_left_led()` function.
In the starter code, this function is implemented by calling functions in the CowPi library.

- [ ] Modify this function to replace the calls to CowPi library functions with code that uses the `ioport` pointer, to turn the LEDs on or off.
  - [ ] Use the read-modify-write pattern to do so, so that you do not change any pins that you do not intend to change.
    - Which field in the `cowpi_ioport_t` structure should you use?
    - When turning the LED on, what bitmask should you use?
      What operation should you use?
    - When turning the LED off, what bitmask should you use?
      What operation should you use?
  - No debouncing code is necessary because these functions do not read from mechanical switches.


#### Test your illumination code

- [ ] Upload the program to your Cow&nbsp;Pi.
- [ ] Confirm that whenever the left switch is in the right position, and the left button is pressed, the left LED will illuminate.
- [ ] Confirm that whenever the left switch is in the left position, and/or the left button is not pressed, the left LED does not illuminate.


---

You are now ready to complete the remainder of this assignment on your own.


---

|            [⬅️](02-debouncing-debugging.md)            |      [⬆️](../README.md)      |                     [➡️](04-simple-io.md)                      |
|:------------------------------------------------------:|:----------------------------:|:--------------------------------------------------------------:|
| [Debouncing and Debugging](02-debouncing-debugging.md) | [Front Matter](../README.md) | [Time, and Simple Memory-Mapped Input/Output](04-simple-io.md) |
