## Scanning the Matrix Keypad

Now that you have some practice with using memory-mapped I/O to read from and write to external pins, you can demonstrate your understanding by combining reads and writes to deduce which key (if any) on the keypad is being pressed.

- [ ] Locate the `get_keypress()` function.
- 
The implementation in the starter code calls the CowPi library's `cowpi_get_keypress()` function.
The `cowpi_get_keypress()` function returns a `char` corresponding to the character on the pressed key,
but the `get_keypress()` function is supposed to return a `uint8_t` that has the hexadecimal value of the pressed key (considering `#` as 0xE and `*` as 0xF).
Because of this, the rest of the implementation is a pair of `switch` statements to obtain the correct value from the `keys` nested array.

- [ ] Read the section of the Cow Pi datasheet that [discusses the matrix keypad](https://cow-pi.readthedocs.io/en/latest/hardware/inputs.html#matrix-keypad).

After you have done so:

- [ ] Preserve the debouncing code in `get_keypress()`, and
- [ ] Replace the starter code's call to `cowpi_get_keypress()` and its `switch` statements with code that scans the keyboard.
  - [ ] Use the ioport` pointer to read from and write to the appropriate pins,
  - [ ] Use a 1&nbsp;µs busy-wait (see below) for the delay shown on line 4 of the pseudocode in the datasheet, and
  - [ ] Use the `keys` nested array to obtain the correct integer value for the key at a given row and column.


\paragraph{What is a busy-wait?}
A busy-wait is a loop that does nothing until some criterion is satisfied.
```c
    while (!condition_is_satisfied) {}
```

In this case, the condition to be satisfied as that at least one microsecond has elapsed since the busy-wait started.

- [ ] Use `get_microseconds()` to obtain the time immediately before the busy-wait.
- [ ] In the busy-wait, compare that with the "current" value obtained by `get_micrseconds()` to see if at least one microsecond has elapsed.


\subsubsection*{Suggestions}

Look at the pseudocode\footnote{
Note that the pseudocode uses the "walrus operator" (`:=`) for assignments and the "equal sign" (`=`) for equality comparisons, as is common in ALGOL-inspired languages.
This is in contrast to C-inspired languages that use the "equal sign" for assignment and the "double equal sign" for equality comparisons.
} in the datasheet and relate it to the "theory of operation."
Even though the pseudocode is expressed as nested loops, you do not need to implement it that way.
We have seen implementations that have an outer loop for the rows and an inner loop for the columns,
and we have seen implementations that have a loop for the rows but use a `switch` statement or chained `if` statements to enumerate the possibilities for the columns.
With four rows and four columns, both are viable solutions.

The key insights are:
- Each of the row vectors you output will have exactly one "0" bit;
  the placement of that "0" corresponds to exactly one of the rows in the `keys` nested array, and
- Each of the column vectors you read as input, if it is not 0xF, will have exactly one "0" bit;
  the placement of that "0" corresponds to exactly one of the columns in the `keys` nested array

Even though you *can* set the loop conditions to terminate the loop as soon as the pressed key has been determined,\footnote{
I am *not* saying you can `return` from inside the loop or `break` out of the loop;
I am saying you can write a `while` condition that includes testing whether `key_pressed` is still 0xFF.
} it would be better to keep your loop conditions simple and allow the code to examine all sixteen keys.
With only sixteen keys, there isn't much time savings to be had by ending the loop as soon as the key has been found,
and in a "real" embedded system, our time budget would have to allow enough time to examine all sixteen keys and so any "savings" gained by ending the loop early would be lost to sitting idle later.


#### Test your get_keypress function

- [ ] Place the **right switch** in the *left* position, and upload the program to your Cow&nbsp;Pi.

The output will include the key that was pressed (if any), a hyphen if no key is being pressed, or a question mark if `get_keypress()` returns an invalid value.

\vspace{1cm}

This would be a good time to make a backup copy of your program.


%\subsection{Display Module} \label{subsec:DisplayModule}
%
%You will use a pointer to a `cowpi_i2c_t` structure to access the memory-mapped I/O registers for the \processor's I$^2$C (aka "TWI") hardware,
%and you will use those registers to send data to the display module.
%
%Read the datasheet's sections that discuss
%the [I$^2$C registers](https://cow-pi.readthedocs.io/en/latest/microcontroller.html#atmega328ptwistruct),
%the [I$^2$C Controller Transmitter Sequence](https://cow-pi.readthedocs.io/en/latest/microcontroller.html#controller-transmitter-sequence),
%the [data format for bytes sent to the display module](https://cow-pi.readthedocs.io/en/latest/hardware/outputs.html#data-byte-for-lcd1602-display-module),
%and the [steps required by the display module itself](https://cow-pi.readthedocs.io/en/latest/hardware/outputs.html#hd44780-driven-lcd-character-display).
%After you have done so, review the starter code for
%
%```c[numberstyle=\color{gray}, numbers=left, firstnumber=285, basicstyle=\ttfamily\small, escapechar=`]
%    void send_halfbyte(const cowpi_display_module_protocol_t *configuration, uint8_t halfbyte, bool is_command) {
%        // contact the peripheral by transmitting a start bit followed by the desired peripheral's address
%        cowpi_i2c_initialize(configuration);    `\label{code:i2cInitialize}`
%        // (you do not need to make further use of the `configuration` argument)
%
%        // transmit one or more data bytes
%        // (your code goes here)                `\label{code:i2cData}`
%
%        // transmit a stop bit
%        cowpi_i2c_finalize();                   `\label{code:i2cFinalize}`
%    }
%```
%
%Of the [three steps](https://cow-pi.readthedocs.io/en/latest/microcontroller.html#controller-transmitter-sequence) in the I$^2$C Controller Transmitter Sequence, the first step of contacting the display module is handled in line&nbsp;\ref{code:i2cInitialize},
%and the third step of transmitting a STOP bit is handled in line&nbsp;\ref{code:i2cFinalize}.
%Your task is to implement the second step of transmitting one or more data bytes, starting at line line&nbsp;\ref{code:i2cData}.
%These are [the bytes and the requisite delay](https://cow-pi.readthedocs.io/en/latest/hardware/outputs.html#hd44780-driven-lcd-character-display) required by the display module.
%
%If you have not already done so:
%
%<!-- itemize -->
%    - Uncomment the second line of the starter code's `initialize_io()` function, and
%    - Assign the appropriate address to the `i2c` pointer on that line.
%
%
%Then, starting at line line&nbsp;\ref{code:i2cData}:
%
%<!-- itemize -->
%    - Implement the pseudocode from the I$^2$C Controller Transmitter Sequence's "transmit one or more data bytes" step, to
%    - Send the three bytes of data required by the display module.
%        <!-- itemize -->
%            % - You may handle the error conditions show in the pseudocode in whatever manner you see fit; it would be best to do so in a manner that allows you to determine *which* error is occurring.
%            - Use `delayMicroseconds(1)` to implement the pulse described in the [data byte sequence](https://cow-pi.readthedocs.io/en/latest/hardware/outputs.html#data-byte-sequence).
%        
%
%
%After you are satisfied that you have implemented the `send_halfbyte()` function correctly:
%
%<!-- itemize -->
%    - Uncomment the last line of the starter code's `initialize_io()` function to register `send_halfbyte()` with the CowPi_stdio library.
%
%
%All of the functions in the CowPi library that send characters or commands to the display module will now make use of your `send_halfbyte()` function.
%
%\subsubsection*{Suggestions}
%Altogether, your code will make three transmissions in the `send_halfbyte()` function.
%After each transmission, you need to wait until the transmission is complete before initiating the next transmission;
%you can achieve this with a *busy wait*.
%As discussed in lecture, a busy wait is simply a do-nothing loop that blocks the program while some condition holds.
%
%The bit vector created in line&nbsp;6 of the the Controller Transmitter Sequence's pseudocode consists of bits that must be set to 1 in the control register for all of these transmissions.
%
%Even though the pseudocode might appear to characterize those transmissions as a loop over the data meant for the display module, the `for each` statement should be understood to mean $\forall$ -- indeed, it will be easier to implement the byte sequence sequentially.
%Two of the three bytes meant for the display module are identical, and the remaining byte differs only only in one bit.
%The first ensures the halfbyte, backlight, read/write, and command bits are at their correct values before a latching pulse starts.
%The second maintains those values and creates the latching pulse; a `delayMicroseconds()` call holds the pulse.
%Finally, the third byte ensures those values are still present as the latching pulse ends.
%
%\vspace{0.5cm}
%
%There are two aspects to this task that some students found frustrating in the past:
%<!-- itemize -->
%    - Some of the required bitshifts may seem like make-work -- for example, line&nbsp;16 of the pseudocode shifts the serial adapter's address to the left by one bit, but after that the least significant bit is always 0
%        <!-- itemize -->
%            - These bits that are seemingly constant appear so only because this assignment uses one specific part of a very flexible protocol
%            - In other uses of the I$^2$C protocol, the bits that are constant *in this assignment* serve other purposes
%        
%    - If some part of your implementation has a bug, you aren't provided with much data you can use to form hypotheses during debugging
%        <!-- itemize -->
%            - "Not much data" is not the same as "no data"
%                <!-- itemize -->
%                    - If a busy-wait doesn't terminate, the problem is probably with your implementation of the I$^2$C protocol -- double-check the bit vectors placed in the control register%, and possibly the bit vector placed in the data register when you transmit the serial adapter's address
%                    - If the function terminates but the display module doesn't update, the problem is probably with the bit vectors placed in the data register that the serial adapter will pass along to the display module, or with the "latch" pulse
%                
%            - You can always get help from the professor or a TA with any aspect of this assignment, and you can discuss *concepts and syntax* with other students.
%                *Without showing other students your code*, asking other students questions like these, and answering them, is acceptable:
%                <!-- itemize -->
%                    - '`The datasheet says we want a `1' in bit 7, a '1' in bit 2, and '0's in the other bits; that looks like this, right?'' and then write a binary or hexadecimal bit vector on paper or a whiteboard
%                    - '`The datasheet says to shift a `1' seven places to the left, and then shift a '1' two places to the left, and then take those two results and bitwise-OR them together; would you help me remember how to do a left-shift?''
%                
%        
%
%
%\subsubsection*{Test your code}
%
%Place the left switch in the right position and upload the program to your Cow&nbsp;Pi.
%If the test code displays its outputs on the display module, then you implemented `send_halfbyte()` correctly.
%If the test code does not display its output one the display module, or if the test code does not run at all, then there is an error in your code.
%
%\vspace{1cm}
%
%If you decide to work on other parts of the assignment before finishing `send_halfbyte()` then comment-out the assignment to `cowpi_hd44780_send_halfbyte` in `initialize_io()`.


---

|                     [⬅️](04-simple-io.md)                      |      [⬆️](../README.md)      |         [➡️](06-grading.md)          |
|:--------------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Time, and Simple Memory-Mapped Input/Output](04-simple-io.md) | [Front Matter](../README.md) | [Turn-In and Grading](06-grading.md) |
