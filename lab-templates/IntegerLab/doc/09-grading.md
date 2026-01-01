> 📇 **Epilogue**
>
> Herb smiles as he hands you the the test results from the latest integrated circuit fab batch.
> "C-licon successfully turned your code into an ALU.
> Nicely done!"
> I think maybe it's time to use C-licon to see if we can improve the Floating Point Unit (FPU) on our experimental microprocessor.
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

This assignment is worth 36 points.

- [ ] **+1** The `exponentiate()` function produces the correct powers of two.
- [ ] **+1** The `lg()` function produces the correct base-2 logarithms.
- [ ] **+1** The `is_negative()` function correctly determines whether its argument has a negative value when interpreted as a signed integer.
- [ ] **+1** The `equal()` function correctly determines whether its arguments are equal to each other.
- [ ] **+1** The `not_equal()` function correctly determines whether its arguments are not equal to each other.
- [ ] **+1** The `logical_not()` function correctly produces the logical inverse of its argument.
- [ ] **+1** The `logical_and()` function correctly produces the logical conjunction of its arguments.
- [ ] **+1** The `logical_or()` function correctly produces the logical disjunction of its arguments.
- [ ] **+1** The `one_bit_full_addition()` function correctly determines the `sum` and `c_out` bits for a 1-bit full adder.
- [ ] **+5** The `ripple_carry_addition()` function correctly implements a 32-bit ripple-carry adder.
- [ ] **+2** The `add()` function correctly performs 16-bit integer addition.
- [ ] **+2** The `add()` function correctly detects unsigned integer overflow and signed integer overflow.
- [ ] **+3** The `subtract()` function correctly performs 16-bit integer subtraction.
- [ ] **+2** The `subtract()` function correctly detects unsigned integer overflow and signed integer overflow.
- [ ] **+3** The `multiply_by_power_of_two()` function correctly multiplies its first argument by its second argument when the second argument is 0 or is a power of two.
- [ ] **+3** The `unsigned_multiply()` function correctly provides the 16-bit product when it multiplies its first argument by its second argument when they are interpreted as unsigned integers.
- [ ] **+2** The `unsigned_multiply()` function correctly provides the 32-bit full product spread across the `supplemental_result` and `result` fields.
- [ ] **+3** The `unsigned_divide()` function correctly provides the 16-bit quotient when it divides its first argument by its second argument (or correctly reports division by zero) when they are interpreted as unsigned integers and the second argument is 0 or is a power of two.
- [ ] **+2** The `unsigned_divide()` function correctly provides the 16-bit remainder.


- Bonuses:
  - [ ] **+1** The `signed_multiply()` function correctly performs signed integer multiplication by addressing the underlying reason that signed and unsigned multiplication need to be different.
  - [ ] **+1** The `signed_divide()` function correctly performs signed integer division by addressing the underlying reason that signed and unsigned division need to be different.
- Penalties:
  - [ ] **no credit** for any of these functions that violates an assignment constraint:
    - `exponentiate()`, `lg()`,
      `is_negative()`, `equal()`, `not_equal()`,
      `logical_not()`, `logical_and()`, `logical_or()`,
      `one_bit_full_addition()`, `multiply_by_power_of_two()`, `unsigned_divide()`
  - [ ] **no credit** for `ripple_carry_addition()` if `ripple_carry_addition()` or `one_bit_full_addition()` violate a constraint.
  - [ ] **no credit** for `add()` if `add()`, `ripple_carry_addition()`, or `one_bit_full_addition()` violate a constraint.
  - [ ] **no credit** for `subtract()` if `subtract()`, `ripple_carry_addition()`, or `one_bit_full_addition()` violate a constraint.
  - [ ] **no credit** for `unsigned_multiply()` if `unsigned_multiply()` or `multiply_by_power_of_two()` violate a constraint.
  - [ ] **no bonus** If `signed_multiply()` or `signed_divide()` violate an assignment constraint or fail to address the underlying reason that the signed and unsigned implementations need to be different.
  - *Assignment constraint violations by helper functions will be assessed against the required function(s) that they help.*
  - [ ] **-1** for each `goto` statement, `break` statement used to exit from a loop, or `return` statement that occurs within a loop

---

|                 [⬅️](08-signed-multiplication-division.md)                 |      [⬆️](../README.md)      |           [➡️](AA-example-tests.md)            |
|:--------------------------------------------------------------------------:|:----------------------------:|:----------------------------------------------:|
| [Signed Multiplication and Division](08-signed-multiplication-division.md) | [Front Matter](../README.md) | [Appendix: Example Tests](AA-example-tests.md) |
