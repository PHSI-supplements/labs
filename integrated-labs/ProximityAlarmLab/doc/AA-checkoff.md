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

1. [ ] [Attach the Devices to the Cow Pi](BB-peripherals.md).
2. [ ] Show the TA your *alarm.c* to demonstrate that a timer interrupt is used to generate the tone.

3. [ ] Place both of the Cow&nbsp;Pi's switches in the *left* position.
4. [ ] Compile the program and upload it to the Cow&nbsp;Pi.
5. [ ] Press the **right** button.
    A 1kHz tone is generated, and both LEDs illuminate.
    - **+2** The audible tone has a frequency of 1kHz
6. [ ] Release the button.
    The LEDs deluminate, and the buzzer goes quiet.
    - **+2** The system continuously generates the tone and illuminates both LEDs when the **right** button is pressed
7. [ ] Press the **left** button.
    The LEDs illuminate for 0.1s while simultaneously the buzzer emits the 1kHz tone for 0.1s.
    - **+2** A chirp is an audible tone lasting 100ms
8. [ ] Press the **left** button again.
    The LEDs illuminate for 0.1s while simultaneously the buzzer emits the 1kHz tone for 0.1s.
    - **+2** The system chirps the tone and strobes the LEDs exactly once when the **left** button is pressed
    - **+2** The piezobuzzer is silent, and the LEDs are dark except in response to a button press

9. [ ] Show the TA your *sensor.c* to demonstrate that the sensor's state transitions happen only due to timer interrupts and pin interrupts.
    (Pulse initiation and distance calculation happens in the main control loop.)
10. [ ] Place the Cow&nbsp;Pi's **left** switch in the *right* position, and press the RESET button.
11. [ ] Point the sensor toward a nearby object.
    Press the **left** button.
    - **+1** if the display shows only that an object was detected, *or*
    - **+3** if the display shows the distance to the object.
12. [ ] Change the distance between the Cow&nbsp;Pi and the object.
    The display does not change.
    - **+1** Exactly one pulse is initiated per button press.
13. [ ] Point the sensor toward a vacant space and press the **left** button.
    The display shows that no object is detected.
    - **+2** When there is no in-range object, the system displays a message to that effect.
14. [ ] Point the sensor toward an object and press the **left** button.
    The display shows that object is detected (possibly by showing the distance).
15. [ ] Show the TA the `compute_distance()` function in *sensor.c* to demonstrate that the distance is calculated as specified.
    - **+2** The distance is correctly calculated
    - **+1** The distance is calculated without using floating point arithmetic and without using integer division



This concludes the demonstration of your system's functionality.
The TAs will later examine your code for violations of the assignment's constraints.
If your code looks like it is tailored for this checklist, the TAs may re-grade using a different checklist.


---

|         [⬅️](08-grading.md)          |      [⬆️](../README.md)      |                           [➡️](BB-peripherals.md)                           |
|:------------------------------------:|:----------------------------:|:---------------------------------------------------------------------------:|
| [Turn-In and Grading](08-grading.md) | [Front Matter](../README.md) | [Appendix B: Attaching and Detaching Peripheral Devices](BB-peripherals.md) |
