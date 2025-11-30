## Appendix A: Lab Checkoff

You are not required to have your assignment checked-off by a TA or the professor.
If you do not do so, then we will perform a functional check ourselves.
We are, however, offering a small bonus if you complete your assignment early and get it checked-off by a TA or the professor during office hours.

> 📝 **Grading Note**
>
> You are not eligible for the early check-off bonus if you use a late day on this assignment.

<!--
<font color="red">***You can also use this checklist yourself to make sure you've implemented everything correctly.***</font>
-->

1. [ ] [Attach the Servo and the Rotary Encoder Module to the Cow&nbsp;Pi](BB-peripherals.md).
2. [ ] Leaving the Cow&nbspPi disconnected from your computer, use your fingers to turn the servo arm to a rotational extreme.

3. [ ] Show the TA your *io_functions.c* to demonstrate that you implemented the functions using memory-mapped I/O.
    - **+¼** `ioport`'s address is set correctly
    - **+¾** `set_servo_pin()` is implemented correctly
    - **+1** `get_quadrature()` is implemented correctly
4. [ ] Show the TA your *timer.c* to demonstrate that the timer interrupt and its ISR are set up correctly.
    - **+½** the timer interrupt is correctly configured and its ISR is correctly registered

5. [ ] Show the TA your *servomotor.c*.
6. [ ] Place both of the Cow&nbsp;Pi's switches in the *left* position.
7. [ ] Compile the program and upload it to the Cow&nbsp;Pi.
    The servo will center itself.
    - **+2** The servo assumes its central position at the start of the program
8. [ ] Observe as the servo starts to rotate through its positions.
    The servo will initially rotate counterclockwise.
    - **+2** The servo rotates clockwise when commanded to rotate clockwise, and counterclockwise when commanded to rotate counterclockwise
9. [ ] Observe that when the servo arm reaches 90º counterclockwise from center, it reverses direction. 
   Similarly, when the servo arm reaches 90º clockwise from center, it reverses direction.
   - **+2** The servo can rotate fully clockwise
   - **+2** The servo can rotate fully counter-clockwise
10. [ ] Count the discrete steps from one rotational extreme to the other.
    Including fully-clockwise and fully-counterclockwise, there are 21 "stop" positions.
    That is, the servo advances 20 times before reversing.
    - **+2** There are 20 increments (21 "stop" positions) between the two rotational extremes

11. [ ] Show the TA your *rotary-encoder.c*.
    - **+2** The quadrature is sampled
    - **+2** The code looks for transitions from quadrature value `0 1` to `0 0` and from `1 0` to `0 0`
    - **+2** The code uses those transitions to deduce the direction of rotation
12. [ ] Place the Cow&nbsp;Pi's **left** switch in the *right* position, and press the RESET button.
13. [ ] Turn the knob once clockwise.
    The "CW" value on the display changes from 0 to 1.
14. [ ] Turn the knob once counterclockwise.
    The "CCW" value on the display changes from 0 to 1.
    - **+2** The code correctly deduces the direction of rotation
15. [ ] Turn the knob five places counterclockwise and then five places clockwise.
    The "CCW" value increases by 1 with each counterclockwise step, and the "CW" value increases by 1 with each clockwise step.
    - A very rare report of two turns with each step can be confirmed to be losing the switch bounce race by repeating this test.
    - If misreporting the number of turns occurs regularly, there is probably a problem with the code.
    - If in doubt, try a different rotary encoder module.
    - **+2** When the rotary encoder's shaft is stationary, the code reports that the shaft is stationary
    - **+2** When the shaft is turned from one detent to the next, the code reports only one turn


This concludes the demonstration of your system's functionality.
The TAs will later examine your code for violations of the assignment's constraints.
If your code looks like it is tailored for this checklist, the TAs may re-grade using a different checklist.


---

|         [⬅️](08-grading.md)          |      [⬆️](../README.md)      |                           [➡️](BB-peripherals.md)                           |
|:------------------------------------:|:----------------------------:|:---------------------------------------------------------------------------:|
| [Turn-In and Grading](08-grading.md) | [Front Matter](../README.md) | [Appendix B: Attaching and Detaching Peripheral Devices](BB-peripherals.md) |
