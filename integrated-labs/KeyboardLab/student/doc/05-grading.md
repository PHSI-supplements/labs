> 📇 **Epilogue**
> 
> Great news!
> Archie brings you your new keyboard.
> He also brings you a problem of his own.
> Because you were held up with the broken keyboard, Archie decided to try some programming on his own, and his code is behaving strangely.
> 
> *To be continued...*

## Turn-In and Grading

Be sure that you have pushed your code to git.unl.edu.

### No Credit for Uncompilable Code

If the TA cannot create an executable from your code, then your code will be assumed to have no functionality.
Be sure to compile and test your code on the nuros.unl.edu Linux server with the original driver code, the original header file(s), and the original CMakeLists.txt.

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

This assignment is worth 20 points.

- [ ] **+4** `generate_email()` produces the specified output
- [ ] **+4** `iz_digit()` determines whether a character is a digit
- [ ] **+4** `decapitalize()` converts uppercase letters to lowercase letters and leaves other characters unchanged
- [ ] **+4** `is_even()` determines whether a number is even or odd
- `produce_multiple_of_ten()` has the following:
  - [ ] **+1** Code to assign the value 5 to the variable `five`
  - [ ] **+1** Code to divide an even number by 2
  - [ ] **+1** Code to subtract 1 from an odd number
  - [ ] **+1** Correct functionality
- Penalties:
  - [ ] **no credit** for each solution that depends on a prohibited character
  - [ ] **no credit** for each solution that hard-codes a return value instead of attempting to solve the specified problem
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|             [⬅️](06-characterize-hands.md)              |      [⬆️](../README.md)      |                         |
|:-------------------------------------------------------:|:----------------------------:|:-----------------------:|
| [Characterizing a Poker Hand](06-characterize-hands.md) | [Front Matter](../README.md) |                         |
