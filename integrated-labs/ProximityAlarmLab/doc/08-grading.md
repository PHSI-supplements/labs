> 📇 **Epilogue**
>
> A technician installing a proximity alaram outside the lab door briefly sets off the alarm, but then the proximity alarm falls quiet and faithfully reports that nothing is approaching.
> As reports come in of facilities getting secured with Cow&nbsp;Pi-based locks, and of accurate specimen counts accomplished with Cow&nbsp;Pi-based calculators, Archie smiles and tells you that this was a job well done.
> With all of the excitement neatly wrapped-up and arriving at a satisfactory conclusion, you look forward to a boring career in which there’s absolutely no screaming and running for your life.
> 
> *The end...?*
> 
> &nbsp;
> 
> &nbsp;
> 
> &nbsp;
> 
> &nbsp;
> 
> For reasons you don't quite understand, you find yourself staring nervously at the calendar.
> Archie pops his head in your office.
> "There's something else that needs your attention."

## Turn-In and Grading

Be sure that you have pushed your code to git.unl.edu.

### No Credit for Uncompilable Code

If the TA cannot create an executable from your code, then your code will be assumed to have no functionality.
Be sure to compile and test your code on the nuros.unl.edu Linux server with the original driver code, the original header file(s), and the original CMake configuration files.

> ✍️ **One Edit Rule**
>
> At the TA's discretion, if they can make your code compile with one edit (such as introducing a missing semicolon) then they may do so and then assess a 10% penalty on the resulting score.
> The TA is under no obligation to do so, and you should not rely on the TA’s willingness to edit your code for grading.
> If there are multiple options for a single edit that would make your code compile, there is no guarantee that the TA will select the option that would maximize your score.

### Late Submissions

This assignment is due before the start of your lab section.
If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt](../LATE-DAYS-USED-ON-THIS-ASSIGNMENT.txt) file and including the update with your code.

> 📝 **Grading Note**
>
> You are not eligible for the early check-off bonus if you use a late day on this assignment.

After you have exhausted your late days, we will accept late turn-ins up to one hour late, assessing a 10% penalty on these late submissions.
After you have exhausted your late days, any work turned in more than one hour late will not be graded.

### Rubric

This assignment is worth 20 points.

- Piezobuzzer:
  - [ ] **+2** The system continuously generates the tone and illuminates both LEDs when the **right** button is pressed
  - [ ] **+2** The system chirps the tone and strobes the LEDs exactly once when the **left** button is pressed
  - [ ] **+2** The piezobuzzer is silent, and the LEDs are dark except in response to a button press
  - [ ] **+2** The audible tone has a frequency of 1kHz
  - [ ] **+2** A chirp is an audible tone lasting 100ms
- Rangefinder:
  - [ ] **+1** Exactly one pulse is initiated per button press
  - [ ] **+2** When there is no in-range object, the system displays a message to that effect
  - [ ] **+1** When an object is detected, the system displays a message to that effect (either a simple report, or the distance to the object)
  - [ ] **+2** When an object is detected, the system displays the distance to the object (not just a simple detection report)
  - [ ] **+2** The distance is correctly calculated
  - [ ] **+1** The distance is calculated without using floating point arithmetic and without using integer division
- No Interference / Separation of Concerns:
  - [ ] **+1** The alarm code does not trigger an ultrasonic pulse, and the sensor code does not generate an alarm
- Bonus:
  - [ ] **+1** Get the assigned [checked-off](AA-checkoff.md) by a TA or professor during office hours *before* it is due
- Penalties:
  - [ ] **no credit** for an alarm solution that does not use a timer interrupt
  - [ ] **no credit** for a rangefinder solution that does not use a timer interrupt and a pin interrupt
  - [ ] **no credit** for functions that violate one or more [constraints](../README.md#constraints)
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop


---

|                 [⬅️](06-sensor-state-machine.md)                  |      [⬆️](../README.md)      |            [➡️](AA-checkoff.md)            |
|:-----------------------------------------------------------------:|:----------------------------:|:------------------------------------------:|
| [Building the Sensor's State Machine](06-sensor-state-machine.md) | [Front Matter](../README.md) | [Appendix A: Lab Checkoff](AA-checkoff.md) |
