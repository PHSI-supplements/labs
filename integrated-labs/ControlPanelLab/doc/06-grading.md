> 📇 **Epilogue**
>
> Herb looks over your work.
> "Hmm, yes.
> I think this is coming along nicely.
> Let's run a few more tests."
> 
> Archie storms into the room.
> "We have *got* to do something about security!
> How's that doodad coming along?
> Because there's now a half-man/half-fly in the labs 
> going on-and-on about Chaos Theory
> and how if we just give him a MacBook and a spaceship then
> he'll be able to get the Lord of Thunder
> to travel across the 8th Dimension.
> Is that thing just about ready?"
> 
> Herb shakes his head,
> "No, not quite yet.
> It should be ready in about a week."
> 
> *To be continued...*

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

After you have exhausted your late days, we will accept late turn-ins up to one hour late, assessing a 10% penalty on these late submissions.
After you have exhausted your late days, any work turned in more than one hour late will not be graded.

### Rubric

This assignment is worth 15 points.

- [ ] **+½** The `keys` nested array is correctly populated
- [ ] **+1** The correct addresses are assigned to `ioport` and `timer`
- [ ] **+1** The `key_is_pressed()` function is correctly implemented
- [ ] **+1** The `set_left_led()` function is correctly implemented
- [ ] **+¾** The `get_microseconds()` function is correctly implemented
- [ ] **+½** The `left_switch_is_in_right_position()` function is correctly implemented
- [ ] **+½** The `right_switch_is_in_right_position()` function is correctly implemented
- [ ] **+½** The `left_button_is_pressed()` function is correctly implemented
- [ ] **+½** The `right_button_is_pressed()` function is correctly implemented
- [ ] **+¾** The `set_right_led()` function is correctly implemented
- [ ] **+8** The `get_keypress()` function is correctly implemented (½ point for each key)
- Bonus:
  - [ ] **+1** Get the assigned [checked-off](AA-checkoff.md) by a TA or professor during office hours *before* it is due
- Penalties:
  - [ ] **no credit** for functions that violate one or more [constraints](../README.md#constraints)
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|             [⬅️](05-keypad.md)             |      [⬆️](../README.md)      |            [➡️](AA-checkoff.md)            |
|:------------------------------------------:|:----------------------------:|:------------------------------------------:|
| [Scanning the Matrix Keypad](05-keypad.md) | [Front Matter](../README.md) | [Appendix A: Lab Checkoff](AA-checkoff.md) |
