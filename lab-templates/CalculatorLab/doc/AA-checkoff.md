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

1. [ ] [Attach the Seven-Segment Display Module to the Cow Pi](BB-peripherals.md).
2. [ ] Show the TA your *seven_segment_pla.c* to demonstrate that the `return` statements use product-of-terms expressions with no more than three variables per product term.<!-- and no more than three product terms per expression.-->
3. [ ] Show the TA your *build_number.c* to demonstrate that there are no constraint violations.
4. [ ] "Clean" the build directory
    - Command line: `pio run -t clean`
    - VS Code: click on the trash can icon in the PlatformIO toolbar
    - CLion: click on the broom icon labeled "Clean" in the PlatformIO tool window
5. [ ] Build the project.
    After the build is complete, show the TA that the end of the build output says
    ```
    constraint-check.py found no violations specified by test/calculatorlab.json in src/seven_segment_pla.c.
    constraint-check.py found no violations specified by test/calculatorlab.json in src/number_builder.c.
    ```
   does ***not*** show any issues with *seven_segment_pla.c*'s return statements,
   and does ***not*** say
   ```
   *** Constraint violations found ***
   ```

6. [ ] Place both of the Cow&nbsp;Pi's switches in the *left* position.
7. [ ] Upload the program to the Cow&nbsp;Pi.
8. [ ] As the program cycles through the decimal numerals, compare the segments on the pla-driven digit to the segments on the rom-driven digit; the glyphs of the two digits should be identical.
    - **+1** The B segment functions correctly
    - **+1½** for each of the remaining six segments that function correctly

9. [ ] Place the Cow&nbsp;Pi's **left** switch in the *right* position, and press the RESET button.
10. [ ] Press 2, then 3.
    The left LED illuminates for ½ second with each keypress.
    The display shows `2`, then `23`.
    - **+2** The first digit is correctly detected
    - **+1** Subsequent digits correctly update a positive number
    - **+1½** A keypress or buttonpress is treated as a single press
    - **+½** The left LED illuminates in response to a keypress
    - **+1** The left LED deluminates a half-second after illuminating later
11. [ ] Press the left pushbutton.
    The right LED illuminates for ½ second.
    The display shows `-23`.
    - **+1** The left pushbutton correctly negates a positive number
    - **+¼** The right LED illuminates in response to a press of the left button
    - **+1** The right LED deluminates a half-second after illuminating later
12. [ ] Press 4.
    The display shows `-234`.
    - **+1** Subsequent digits correctly update a negative number
    - **+½** Negating numbers other than `INT16_MIN` do not set the overflow flag.
13. [ ] Press the left pushbutton.
    The display shows `234`.
    - **+1** The left pushbutton correctly negates a negative number
14. [ ] Press 5, then 6.
    The display shows `23456`.
     - **+½** Building numbers that fit in 16 bit two's complement do not set the overflow flag.
15. [ ] Press 7.
    The display shows `23456 overflow`.
16. [ ] Press the right pushbutton.
    The right LED illuminates for ½ second.
    The display shows `0`.
    - **+1** The right pushbutton sets the number to 0 and clears the overflow flag
    - **+¼** The right LED illuminates in response to a press of the right button
17. [ ] Press 3, 2, 7, 6, 8.
    The display shows `3276 overflow`.
18. [ ] Press the right pushbutton to clear the number, then press 3, left pushbutton, 2, 7, 6, 9.
    The display shows `-3276 overflow`.
    - **+½** Building numbers that do not fit in 16 bit two's complement sets the overflow flag.
19. [ ] Press the right pushbutton to clear the number, then press 3, left pushbutton, 2, 7, 6, 8.
    The display shows `-32768`.
20. [ ] Press the left pushbutton to negate the number.
    The display shows `-32768 overflow`.
    - **+½** Negating numbers `INT16_MIN` sets the overflow flag.
21. [ ] Press the right pushbutton to clear the number, then rapidly press 1, 2, 3, left pushbutton, 4, 7, left pushbutton, right pushbutton.
    All presses are detected.
    The display updates appropriately with each press, and the LEDs illuminate appropriately.
22. **+1½** The system is responsive and never blocks


This concludes the demonstration of your system's functionality.
The TAs will later examine your code for violations of the assignment's constraints.
If your code looks like it is tailored for this checklist, the TAs may re-grade using a different checklist.


---

|         [⬅️](07-grading.md)          |      [⬆️](../README.md)      |                                  [➡️](BB-peripherals.md)                                  |
|:------------------------------------:|:----------------------------:|:-----------------------------------------------------------------------------------------:|
| [Turn-In and Grading](07-grading.md) | [Front Matter](../README.md) | [Appendix B: Attaching and Detaching the Seven-Segment Display Module](BB-peripherals.md) |
