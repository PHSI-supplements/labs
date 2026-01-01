> 📇 **Epilogue**
>
> Herb finishes attaching the remotely-manipulated arm to a robot.
> You and he watch as an animal handler guides the robot into the pouch lion enclosure to examine a litter of cubs.
> 
> Nothing is going wrong. <br>
> Absolutely nothing.
> 
> *Roll credits*
>
> &nbsp;
>
> &nbsp;
>
> &nbsp;
>
> &nbsp;
>
> I wonder if there are extra scenes during the credits...

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

This assignment is worth 25 points.

- Memory-Mapped I/O:
  - [ ] **+¼** `ioport`'s address is set correctly
  - [ ] **+¾** `set_servo_pin()` is implemented correctly
  - [ ] **+1** `get_quadrature()` is implemented correctly
- Setting the Interrupt:
  - [ ] **+½** the timer interrupt is correctly configured and its ISR is correctly registered
- Servo:  <!-- points for no jitter? -->
  - [ ] **+2** The servo assumes its central position at the start of the program
  - [ ] **+2** The servo can rotate fully clockwise
  - [ ] **+2** The servo can rotate fully counter-clockwise
  - [ ] **+2** The servo rotates clockwise when commanded to rotate clockwise, and counterclockwise when commanded to rotate counterclockwise
  - [ ] **+2** There are 20 increments (21 "stop" positions) between the two rotational extremes
  - [ ] **+½** The servo does not "jitter" (when it reaches a "stop" position, it doesn't jiggle back & forth)
- Rotary Encoder:
  - [ ] **+2** The quadrature is sampled
  - [ ] **+2** The code looks for transitions from quadrature value `0 1` to `0 0` and from `1 0` to `0 0` 
  - [ ] **+2** The code uses those transitions to deduce the direction of rotation...
  - [ ] **+2** ...and makes the correct deduction
  - [ ] **+2** When the rotary encoder's shaft is stationary, the code reports that the shaft is stationary
  - [ ] **+2** When the shaft is turned from one detent to the next, the code reports only one turn
- Bonus:
  - [ ] **+1** Get the assigned [checked-off](AA-checkoff.md) by a TA or professor during office hours *before* it is due
- Penalties:
  - [ ] **no credit** for functions that violate one or more [constraints](../README.md#constraints)
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|            [⬅️](07-input-to-actuator.md)             |      [⬆️](../README.md)      |            [➡️](AA-checkoff.md)            |
|:----------------------------------------------------:|:----------------------------:|:------------------------------------------:|
| [Remotely Operating an Arm](07-input-to-actuator.md) | [Front Matter](../README.md) | [Appendix A: Lab Checkoff](AA-checkoff.md) |
