> 📇 **Epilogue**
>
> You and Herb look for Archie in the Pleistocene Petting Zoo’s labs to give him the good news,
> and you find a blond woman wearing cargo shorts, butchering a Gilbert and Sullivan song...
> 
> ♪ I am the very model of a modern vice admiral ♪            <br>
> ♪ I’ve information about all things paleobotanical ♪        <br>
> ♪ And I’ve been up to my armpits in problems scatological ♪ <br>
> ♪ During the regency I had experience matriarchical ♪       <br>
> ♪ I plot space travel, normal and superluminal ♪            <br>
> ♪ (Even if I challenge the Pauli exclusion principle) ♪     <br>
> 
> "I don’t know how these people keep getting into our labs.
> Please tell me that you have good news," pleads Archie.
> 
> "Yes, we have the calculator that you asked for.
> Moreover, the Cow Pi is ready for whatever you need: 
> security systems, parking meters – you name it," Herb cheerfully responds.
> 
> "Excellent.
> Let's have H.Awk... no, not H.Awk Aye."
> Archie turns to you.
> "I've got something that I'd like you to get started right away. 
> Here’s what I'd like to have built next."
> 
> *To be continued...*

## Turn-In and Grading

Be sure that you have pushed your code to git.unl.edu.

### No Credit for Uncompilable Code

If the TA cannot create an executable from your code, then your code will be assumed to have no functionality.
Be sure to compile and test your code with the original driver code, the original header file(s), and the original PlatformIO configuration files.

> ✍️ **One Edit Rule**
>
> At the TA's discretion, if they can make your code compile with one edit (such as introducing a missing semicolon) then they may do so and then assess a 10% penalty on the resulting score.
> The TA is under no obligation to do so, and you should not rely on the TA’s willingness to edit your code for grading.
> If there are multiple options for a single edit that would make your code compile, there is no guarantee that the TA will select the option that would maximize your score.

### Late Submissions

This assignment is due before the start of your lab section.
If you have late days available, you may use one or more to extend your deadline.
You can exercise a late day (or days) by editing the [submission_metadata.json](../submission_metadata.json) file and including the update with your code.

> 📝 **Grading Note**
>
> You are not eligible for the early check-off bonus if you use a late day on this assignment.

After you have exhausted your late days, we will accept late turn-ins up to one hour late, assessing a 10% penalty on these late submissions.
After you have exhausted your late days, any work turned in more than one hour late will not be graded.

### Rubric

This assignment is worth 25 points.

- Digital Logic Design:
  - [ ] **+1** The B segment functions correctly
  - [ ] **+9** The remaining six segments function correctly (1½ point for each segment)
- Polling:
  - [ ] **+2** The first digit is correctly detected
  - [ ] **+2** Subsequent digits correctly update a number (1 point each: positive numbers, negative numbers)
  - [ ] **+2** The left pushbutton correctly negates a number (1 point each: positive numbers, negative numbers)
  - [ ] **+2** The overflow flag is correctly set (½ each: negating `INT16_MIN` overflows, negating other numbers does not overflow, building numbers that require more than 16 bits in two's complement overflows, building other numbers do not overflow)
  - [ ] **+1** The right pushbutton sets the number to 0 and clears the overflow flag
  - [ ] **+1** The LEDs illuminate in response to a keypress or buttonpress, as appropriate
  - [ ] **+2** The LEDs deluminate a half-second after illuminating later
  - [ ] **+1½** A keypress or buttonpress is treated as a single press
  - [ ] **+1½** The system is responsive and never blocks
- Bonus:
  - [ ] **+1** Get the assigned [checked-off](AA-checkoff.md) by a TA or professor during office hours *before* it is due
- Penalties:
  - [ ] **no credit** for segment functions whose return value is not computed by a sum-of-products expression
  - [ ] **no credit** for segment functions whose sum-of-product expression uses more than three variables per product term, or more than three product terms
  - [ ] **no credit** for functions that violate one or more [constraints](../README.md#constraints)
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|             [⬅️](06-calculator.md)             |      [⬆️](../README.md)      |            [➡️](AA-checkoff.md)            |
|:----------------------------------------------:|:----------------------------:|:------------------------------------------:|
| [A Four-Function Calculator](06-calculator.md) | [Front Matter](../README.md) | [Appendix A: Lab Checkoff](AA-checkoff.md) |
