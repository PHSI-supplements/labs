## Multiplication and Division

Recall that for any number base, $b$, multiplying two floating point values $(m_1 \times b^{e_1}) \cdot (m_2 \times b^{e_2})$ produces $m_1 \cdot m_2 \times b^{e_1 + e_2}$.
Similarly, dividing the two floating point values yields $\frac{m_1}{m_2} \times b^{e_1 - e_2}$.

### TL;DR

- [ ] Produce the appropriate return values for `multiply()`'s guard clauses.
- [ ] Multiply the two operands together using integer arithmetic.
- [ ] Compile and run *floatlab*, multiplying a few values.


- [ ] Produce the appropriate return values for `divide()`'s guard clauses.
- [ ] Divide $dividend \div divisor$ using integer arithmetic.
  - You only need to handle the cases in which the dividend's significand is a multiple of the divisor's significand.
- [ ] Compile and run *floatlab*, dividing a few values.


### Multiplication

The `multiply()` stub identifies a handful of special cases that you can easily handle.

- [ ] Produce the appropriate return values for `multiply()`'s guard clauses.
  - If it is easier for you, you *may* change the compound conditionals in the guard clauses into separate guard clauses.
    For example, instead of handling \
    `if (is_infinity(multiplier) || is_zero(multiplier))` as a single guard clause,
    you may handle `if (is_infinity(multiplier)` as its own guard clause and then handle `if (is_zero(multiplier))` as its own guard clause.

After the guard clauses, the operands are guaranteed to both be finite, non-zero numbers.
These lines
```c
[[maybe_unused]] unnormal_t decoded_multiplicand = prepare_for_arithmetic(decode(multiplicand));
[[maybe_unused]] unnormal_t decoded_multiplier = prepare_for_arithmetic(decode(multiplier));
```
create `unnormal_t` representations of the operands that have their significands fully in the integer portion.
Because you do not need to give the two operands the same exponent, you do not need to worry about further adjustment.

> ⓘ **Note**
> 
> These two variables are annotated as `[[maybe_unused]]` because they *are* unused until you implement `multiply()`.
> Annotating them as `[[maybe_unused]]` instructs the compiler not to issue a warning about them being unused.

- [ ] Multiply the two operands together using integer arithmetic.

> ⓘ **Note**
>
> Do *not* implement re-normalization and rounding in the `multiply()` function.
> Notice this code at the end of `multiply()`:
> ```c
>     unnormal_t product = unnormal(...);
>     return encode(product);
> ```
> That code will take care of re-normalization and, eventually, rounding.

> 📝 **Grading Note**
>
> For the `multiply()` function, we will not deduct points if you have the wrong sign for Not-a-Number.
> *We will, however, deduct points if you have the wrong sign for Zero.*


#### Check Your Work

- [ ] Compile and run *floatlab*, multiplying a few values.

Be sure to check:

- The identity, zero, and commutative properties
  - <u>`5 * 1`</u>
  - <u>`5 * 0`</u>
  - <u>`2 * 3`</u>
  - <u>`3 * 2`</u>
- Integer operands
  - <u>`75 * 7`</u>
  - <u>`5 * 25`</u>
- Fractional operands
  - <u>`.75 * 7`</u>
  - <u>`5 * .25`</u>
- Negative operands
  - <u>`-5 * 2`</u>
  - <u>`5 * -2`</u>
  - <u>`-5 * -2`</u>
  - <u>`5 * -0`</u>
- Numbers both great and small
  - <u>`1.35e25 * 2.39e11`</u>
  - <u>`1.35e-25 * 2.39e-11`</u>
  - <u>`1e-30 * 1e-8`</u>
  - <u>`2e30 * 2e-30`</u>
- A sufficiently-large product overflows to infinity
  - <u>`0x7E000000 * 0x41000000`</u>
- A sufficiently-small product underflows to zero
  - <u>`0x3C800000 * 0x00000020`</u>
- NaN and Infinity are "sticky" (except for $\infty \times 0$)
  - <u>`nan * 1`</u>
  - <u>`inf * 2`</u>
  - <u>`inf * 0`</u>
    
<!--
The first of these requires rounding up
  - <u>`1.65e25 * 2.39e11`</u>
  - <u>`1.65e-25 * 2.39e-11`</u>
-->

> ⓘ Note
> 
> When you try your own values for testing,
> if the *expected* value can become the *actual* value by adding 1 to the LSB,
> then this is a rounding error.
> You will implement rounding [later](08-rounding.md).


### Division

Implementing the `divide()` function is very similar to implementing `multiply()` with three exceptions:

- There are different special cases
- You subtract the exponents and divide the significands
- In general, integer division is insufficient

We will limit our implementation of `divide()` to the special cases and to cases in which the dividend's significand is a multiple of the divisor's significand.
This limitation guarantees that if the `unnormal_t` operands' significands are fully in the `.integer` field then the `unnormal_t` quotient's significand will fully be in the `.integer` field and will not spill over into the `.fraction` field.
**In this limited implementation, integer division is sufficient.**

- [ ] Produce the appropriate return values for the guard clauses.
- [ ] Divide $dividend \div divisor$ using integer arithmetic.

> ⓘ **Note**
>
> Do *not* implement re-normalization and rounding in the `divide()` function.
> Notice this code at the end of `divide()`:
> ```c
>     unnormal_t quotient = unnormal(...);
>     return encode(quotient);
> ```
> That code will take care of re-normalization and, eventually, rounding.

> 📝 **Grading Note**
>
> For the `divide()` function, we will not deduct points if you have the wrong sign for Not-a-Number.
> *We will, however, deduct points if you have the wrong sign for Zero.*


#### Check Your Work

- [ ] Compile and run *floatlab*, dividing a few values.

Be sure to check:

- The identity property
  - <u>`5 / 1`</u>
- Integer operands
  - <u>`75 / 4`</u>
- Fractional operands
  - <u>`.75 / 4`</u>
  - <u>`5 / .25`</u>
  - <u>`.75 / .25`</u>
- Negative operands
  - <u>`-4 / 2`</u>
  - <u>`4 / -2`</u>
  - <u>`-4 / -2`</u>
- Divisors that require more than one 1 in the significand (but the dividend's significand is still a multiple of the divisor's significand)
  - <u>`30 / 5`</u>
  - <u>`25 / 0x3F200000`</u>
  - <u>`0x3F480000 / 5`</u>
- The special cases
  - <u>`nan / 2`</u>
  - <u>`2 / nan`</u>
  - <u>`inf / 2`</u>
  - <u>`0 / 2`</u>
  - <u>`2 / inf`</u>
  - <u>`2 / 0`</u>
  - <u>`inf / inf`</u>
  - <u>`0 / 0`</u>

> ⓘ Note
>
> When you try your own values for testing,
> if the *expected* value can become the *actual* value by adding 1 to the LSB,
> then this is a rounding error.
> You will implement rounding [later](08-rounding.md).

---

|                    [⬅️](05-normalization.md)                     |      [⬆️](../README.md)      |            [➡️](07-add-subtract.md)            |
|:----------------------------------------------------------------:|:----------------------------:|:----------------------------------------------:|
| [Encoding Numbers into the IEEE 754 Format](05-normalization.md) | [Front Matter](../README.md) | [Addition and Subtraction](07-add-subtract.md) |
