## Appendix A: Lab Checkoff

You are not required to have your assignment checked-off by a TA or the professor.
If you do not do so, then we will perform a functional check ourselves.
We are, however, offering a small bonus if you complete your assignment early and get it checked-off by a TA or the professor during office hours.

<!--
<font color="red">***You can also use this checklist yourself to make sure you've implemented everything correctly.***</font>
-->

1. [ ] Show the TA your `keys` nested array and your `initialize_io()` function.
    - **+1** The `key` nested array is correctly populated
    - **+½** The correct address is assigned to `ioport`
    - **+½** The correct address is assigned to `timer`
2. [ ] Show the TA your implementations of the Input/Output functions to establish that they are implemented using memory-mapped I/O.
3. [ ] Place the **right switch** in the *right* position and RESET the Cow&nbsp;Pi.
4. [ ] Demonstrate that the display shows that a key is pressed whenever any key is pressed, and that the display shows that no key is pressed whenever no keys are pressed.
    - **+2** The `key_is_pressed()` function is correctly implemented
5. [ ] Demonstrate that, as you press those keys, the display shows time advancing at the rate of one second per second.
    - **+2** The `get_microseconds()` function is correctly implemented
6. [ ] Place the **right switch** in the *left* position and RESET the Cow&nbsp;Pi.
7. [ ] Demonstrate that both pushbuttons' positions are correctly detected.
    - **+½** The `left_button_is_pressed()` function is correctly implemented
    - **+½** The `right_button_is_pressed()` function is correctly implemented
8. [ ] Demonstrate that both switches' positions are correctly detected.
    - **+½** The `left_switch_is_in_right_position()` function is correctly implemented
    - **+½** The `right_switch_is_in_right_position()` function is correctly implemented
9. [ ] Demonstrate that when and only when the **left switch** is in the *right* position and the **left button** is *pressed*, the left LED illuminates.
    - **+2** The `set_left_led()` function is correctly implemented
10. [ ] Demonstrate that when and only when the **right switch** is in the *right* position and the **right button** is *pressed*, the left LED illuminates.
    - **+1** The `set_right_led()` function is correctly implemented
11. [ ] Demonstrate that each of the keys on the keypad is correctly detected and that the absence of a keypress is also reported correctly (as `-`, *not* `?`).
    - **+8** The `get_keypress()` function is correctly implemented

This concludes the demonstration of your system's functionality.
The TAs will later examine your code for violations of the assignment's constraints.
If your code looks like it is tailored for this checklist, the TAs may re-grade using a different checklist.

---

|         [⬅️](06-grading.md)          |      [⬆️](../README.md)      |              [➡️](BB-datasheet-links.md)               |
|:------------------------------------:|:----------------------------:|:------------------------------------------------------:|
| [Turn-In and Grading](06-grading.md) | [Front Matter](../README.md) | [Links to the Cow Pi Datasheet](BB-datasheet-links.md) |
