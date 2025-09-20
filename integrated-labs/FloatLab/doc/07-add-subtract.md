## Addition and Subtraction

As is the case for integer arithmetic, the heavy-lifting for addition and subtraction is handled solely by the `add()` function.
The `subtract()` function is already implemented in terms of `add` and the `negate()` function.

### TL;DR

- [ ] Implement `negate()`.



- [ ] Produce the appropriate return values for `add()`'s guard clauses.
- [ ] Repeatedly use the `shift_left_once()` function (or, synonymously, use `decrement_exponent()` or `move_binary_point_to_the_right()`) on whichever operand has the ***greater*** exponent to shift its significant to the left (decreasing the exponent, moving the binary point to the right) until either:
  - the exponents match, or
  - one more shift would make addition unreliable, as reported by  `left_shift_will_make_addition_unreliable()`.
- [ ] If the exponents still do not match, then repeatedly use the `shift_right_once()` function (or `increment_exponent()` or `move_binary_point_to_the_left()`) to shift the other operand's significand to the right (increasing the exponent, moving the binary point to the left) until the exponents match.
- [ ] Add the two values using integer arithmetic.
- [ ] Compile and run *floatlab*, adding and subtracting a few values.


### Negation

The `negate()` function is simple: it only needs to change the number's sign bit.

- [ ] Implement `negate()`.

You will test `negate()` with the `subtract()` function.


### Addition

The `add()` stub identifies a handful of special cases that you can easily handle.

- [ ] Produce the appropriate return values for the guard clauses.

After the guard clauses, the operands are guaranteed to both be finite, non-zero numbers.
These lines
```c
[[maybe_unused]] unnormal_t decoded_augend = prepare_for_arithmetic(decode(augend));
[[maybe_unused]] unnormal_t decoded_addend = prepare_for_arithmetic(decode(addend));
```
create `unnormal_t` representations of the operands that have their significands fully in the integer portion.

Recall that for any number base, $b$, adding two floating point values $m_1 \times b^{e_1} + m_2 \times b^{e_2}$ is simplified when $e_1 = e_2$.

Start by adjusting one of the decoded operands so that the two decoded operands have the same exponent.
It is acceptable for the least significant bit (or even several less significant bits) to be truncated;
however, *you must take care that the most significant bit does not get truncated*!

- [ ] Repeatedly use the `shift_left_once()` function (or, synonymously, use `decrement_exponent()` or `move_binary_point_to_the_right()`) on whichever operand has the ***greater*** exponent to shift its significant to the left (decreasing the exponent, moving the binary point to the right) until either:
  - the exponents match, or
  - one more shift would make addition unreliable, as reported by  `left_shift_will_make_addition_unreliable()`.
- [ ] If the exponents still do not match, then repeatedly use the `shift_right_once()` function (or `increment_exponent()` or `move_binary_point_to_the_left()`) to shift the other operand's significand to the right (increasing the exponent, moving the binary point to the left) until the exponents match.
- [ ] Add the two values using integer arithmetic.
    > ⓘ **Note**
    > 
    > You need only to add the integer portions, setting the fraction portion to 0.
      If you shifted an operand's significand to the right only after the other operand is shifted as far to the left as is safe to do so, then any bits that were shifted into the fraction would be lost to rounding anyway.

> 💡 **Tip**
> 
> If the two operands have the same sign, add the significands;
> if the two operands have different signs, subtract the significands' magnitudes.

> 📝 **Grading Note**
> 
> For the `add()* function, we will not deduct points if you have the wrong sign for Zero or for Not-a-Number` because the appropriate sign is usually indeterminate.
> (There are two cases where the sign can be determined; can you discover which cases those are?)


#### Check Your Work

When you run *floatlab*, you can enter a two-operand expression, such as addition and subtraction.
As before, if an operand is prepended with `0x` then the parser will treat it as a bit vector;
otherwise, the parser will treat it as a floating point value.

```
Enter a value, a two-operand arithmetic expression,
    "decode <value>", "recode <value>",
    or "quit": 1 + 2
0x3f800000	+1.0000,0000,0000,0000,0000,000_{2} x 2^{0}
+
0x40000000	+1.0000,0000,0000,0000,0000,000_{2} x 2^{1}
expected: 3.0000000000_{10}	0x40400000	+1.1000,0000,0000,0000,0000,000_{2} x 2^{1}
actual:   3.0000000000_{10}	0x40400000	+1.1000,0000,0000,0000,0000,000_{2} x 2^{1}
```

- [ ] Compile and run *floatlab*, adding and subtracting a few values.

Be sure to check:
- The identity and commutative properties
  - <u>`5 + 0`</u>
  - <u>`2 + 3`</u>
  - <u>`3 + 2`</u>
- Cases in which the exponent will be greater than that of either operand
  - <u>`3 + 3`</u>
- Fractional operands
  - <u>`.4 + .04`</u>
- Not only the use of negative operands, but also subtraction
  - <u>`-5 + 2`</u>
  - <u>`2 - 5`</u>
  - <u>`3 - -3`</u>
- Numbers both great and small
  - <u>`1.65e35 + 2.39e29`</u>
  - <u>`1.65e-39 + 2.39e-33`</u>
- A sufficiently-large sum overflows to infinity
  - <u>`0x7F7FFFFF + 0x73800000`</u>
- A sufficiently-small difference between normal numbers underflows to subnormal numbers
  - <u>`0x01000000 - 0x00C00000`</u>
- A number subtracted from itself produces zero:
  - <u>`0x00000001 - 0x00000001`</u>
- NaN and Infinity are "sticky" (except for $\infty - \infty$)
  - <u>`nan + 1`</u>
  - <u>`inf - 0x7F7FFFFF`</u>
  - <u>`inf - inf`</u>

> ⓘ Note
>
> When you try your own values for testing, if the *expected* value's LSB is 1 and the *actual* value's LSB is 0,
> but the two values are otherwise identical, then this is a rounding error.
> You will implement rounding [on the next page](08-rounding.md).

---

|             [⬅️](06-multiply-divide.md)              |      [⬆️](../README.md)      |    [➡️](08-rounding.md)    |
|:----------------------------------------------------:|:----------------------------:|:--------------------------:|
| [Multiplication and Division](06-multiply-divide.md) | [Front Matter](../README.md) | [Rounding](08-rounding.md) |
