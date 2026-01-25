> 📇 **Epilogue**
>
> Lil enters the room.
> Herb challenges her: "*Gulliver's Travels*, `endian'," and Lil answers, "ends."
>
> Lil walks up to you and says, "We have the insurance situation taken care of, and it's time to get the Zoo ready for guests.
> We're reassembling the tech team, and there's plenty of work to do."
>
> You smile.
> "That's good news!"
>
> Lil's face is hard to read.
> "Well, yes and no.
> It's good that you'll be able to resume work on the Zoo's systems.
> But while Archie was waiting for us to fix the insurance situation, he got bored and -- cutting a long story short -- he ended up creating some new 'opportunities' that we need you 'to succeed' at."
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
You can exercise a late day (or days) by editing the [submission_metadata.json](../submission_metadata.json) file and including the update with your code.

After you have exhausted your late days, we will accept late turn-ins up to one hour late, assessing a 10% penalty on these late submissions.
After you have exhausted your late days, any work turned in more than one hour late will not be graded.

### Rubric

This assignment is worth 35 points.

- [ ] **+1** `is_nan()` correctly reports whether or not its argument is a number
- [ ] **+1** `is_zero()` correctly reports whether or not its argument is zero
- [ ] **+1** `is_infinity()` correctly reports whether or not its argument is infinite
- [ ] **+1** `is_negative()` correctly reports whether or not its argument is negative
- [ ] **+1** `get_754_integer()` correctly extracts the significand's implicit integer
- [ ] **+1** `get_754_fraction()` correctly extracts the significand's fraction bits
- [ ] **+1** `get_754_exponent()` correctly extracts the exponent
- [ ] **+1** `decode()` correctly converts an `ieee754_t` value into a `unnormal_t` structure
- [ ] **+1** `negate()` correctly changes its argument's sign
- [ ] **+5** `add()` can add integers \& fractions, positive \& negative values, and "large" \& "small" numbers
- [ ] **+1** The identity and commutative properties hold for `add()`
- [ ] **+1** `add()` provides correct answers for its special cases
- [ ] **+5** `multiply()` can multiply integers \& fractions, positive \& negative values, and "large" \& "small" numbers
- [ ] **+2** The identity, zero, and commutative properties hold for `multiply()`
- [ ] **+1** `multiply()` provides correct answers for its special cases
- [ ] **+1** `divide()` provides correct answers for its special cases
- [ ] **+1** `divide()` can divide when the divisor is of the form $\pm 2^n, -126 \le n \le 127$
- [ ] **+1** `divide()` can divide when the dividend's significand is a multiple of the divisor's significand
- [ ] **+1** `round_to_nearest_even()` rounds down when the truncated part of the significand is less than halfway between representable values
- [ ] **+1** `round_to_nearest_even()` rounds up when the truncated part of the significand is more than halfway between representable values
- [ ] **+2** `round_to_nearest_even()` rounds to the nearest-even when the truncated part of the significand is exactly halfway between representable values
- [ ] **+1** Rounding can carry into the exponent
- [ ] **+1** `encode()` overflows to infinity
- [ ] **+1** `encode()` gracefully underflows through subnormal numbers
- [ ] **+1** `encode() underflows to zero`


- Bonus:
    - [ ] **+2** `divide()` can divide arbitrary values


- Penalties:
  - [ ] **no credit** for functions that use `float` or `double` variables or constants, use `union` variables, use C's floating point operations, and/or a function you did not write
  - [ ] **no credit** for arithmetic functions, if `decode()` and/or `encode()`  use `float` or `double` variables or constants, use `union` variables, use C's floating point operations, and/or a function you did not write
  - *Assignment constraint violations by helper functions will be assessed against the required function(s) that they help.*
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|                [⬅️](09-arbitrary-division.md)                |      [⬆️](../README.md)      |               [➡️](AA-unit-test-discussion.md)               |
|:------------------------------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [Bonus Credit: Arbitrary Division](09-arbitrary-division.md) | [Front Matter](../README.md) | [Appendix: Unit Test Discussion](AA-unit-test-discussion.md) |
