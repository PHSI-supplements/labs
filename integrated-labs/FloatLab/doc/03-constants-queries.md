## Constants and Queries

### Constants

There are seven named constants in *fpu.c*.

- [ ] Assign the appropriate bit vectors to `SIGN_BIT_MASK`, `EXPONENT_BITS_MASK`, and `FRACTION_BITS_MASK` so that you can use them to mask-off the sign bit, the exponent bits, and the fraction bits, respectively, in a `ieee754_t` floating point value.
- [ ] Assign the single-precision exponent bias to `EXPONENT_BIAS` and assign to `NUMBER_OF_FRACTION_BITS` the number of bits used for the fraction bit field in a single-precision floating point number.
- [ ] Assign to `NAN` and `INFINITY` suitable bit vectors for single-precision Infinity and Not-a-Number.

These constants will not be graded directly;
they exist solely to make your code more readable.
You may define additional named constants as needed.


### Query Functions

There are three functions to identify whether an `ieee754_t` floating point value is neither normal nor subnormal.
The remaining query function determines whether an `ieee754_t` floating point value is negative.

- [ ] Implement `is_nan()` to detect whether a value is Not-a-Number without regard to the value's sign.
  - Note that `is_nan()` must return `true` for *all* valid NaN bit vectors and not just those that match your `NAN` constant. 
- [ ] Implement `is_infinity()` to detect whether a value is infinity without regard to the value's sign.
- [ ] Implement `is_zero()` to detect whether a value is zero without regard to the value's sign.
- [ ] Implement `is_negative()` to detect whether a value is negative.

---

|               [⬅️](02-unnormal_t.md)               |      [⬆️](../README.md)      |                 [➡️](04-examining-numbers.md)                  |
|:--------------------------------------------------:|:----------------------------:|:--------------------------------------------------------------:|
| [`unnormal_t` and Its Functions](02-unnormal_t.md) | [Front Matter](../README.md) | [Examining IEEE 754-Compliant Values](04-examining-numbers.md) |
