## Encoding Numbers into the IEEE 754 Format

### TL;DR

In the `encode()` function:
- [ ] Determine whether the value is too great to be represented as a normal number.
- [ ] Determine whether the value is too small to be represented as a normal number.
- [ ] If the number can be represented as a normal number, then encode `number` in the IEEE&nbsp;754 normal form.
- [ ] If the number is too small to be represented as a normal number, then:
  - [ ] Use `unnormal_t`'s `set_exponent()` function to set `number`'s exponent to that which all 32-bit subnormal numbers have, and
  - [ ] Encode `number` in the IEEE&nbsp;754 subnormal form.
- [ ] Appropriately encode numbers too great to be represented as normal numbers.
- [ ] Apply rounding, following the IEEE&nbsp;754 default of "round-to-nearest, ties-to-even."
- [ ] Compile and run *floatlab*, recoding a few values (example usages: <u>`recode 12.375`</u> and <u>`recode 0x00055000`</u>).

[//]: # (TODO: Migrate rounding to its own function, its own section)

### Encoding Numbers

The `encode()` function converts an `unnormal_t` value into an IEEE&nbsp;754-compliant format.
The function stub already handles zero and the flagged cases of Not-a-Number and Infinity.
The stub also handles the sign bit.

Observe that when your program reaches
```c
/* GENERATE THE APPROPRIATE BIT VECTOR AND PLACE IT IN RESULT */
```
then you know that `number`'s "true value" is a non-zero, finite number.
Moreover, the integer portion has been set to $1$, which will make it easy to determine if `number` can be encoded as a normal number,
and will make it easy to perform that encoding.

[//]: # (TODO: Make the hints **💡 Hint**s)

In the `encode()` function:
- [ ] Determine whether the value is too great to be represented as a normal number.
  - Suppose that the number *can* be represented as a normal number -- what is the greatest exponent possible?
    Is `number`'s exponent greater than that?
- [ ] Determine whether the value is too small to be represented as a normal number.
  - Suppose that the number *can* be represented as a normal number -- what is the least exponent possible?
    Is `number`'s exponent less than that?
- [ ] If the number can be represented as a normal number, then encode `number` in the IEEE&nbsp;754 normal form.
- [ ] If the number is too small to be represented as a normal number, then:
    - [ ] Use `unnormal_t`'s `set_exponent()` function to set `number`'s exponent to that which all 32-bit subnormal numbers have, and
    - [ ] Encode `number` in the IEEE&nbsp;754 subnormal form.

For both normal and subnormal numbers, you will need to use `unnormal_t`'s functions that access the structure's fields.
Don't forget that the bit vector returned by `get_unnormal_fraction()` is the numerator of $\frac{get\_unnormal\_fraction()}{2^{64}}$ and that `get_unnormal_exponent()` returns the two's complement representation of the exponent.

There are additional tasks for `encode()` that we recommend you attempt to implement now, though you will not be able to test them with the assignment's driver code until later:\footnote{See Appendix&nbsp;\ref{sec:testRounding} for a way to test them now.}

- [ ] Appropriately encode numbers too great to be represented as normal numbers.
- [ ] Apply rounding, following the IEEE&nbsp;754 default of "round-to-nearest, ties-to-even."

[//]: # (TODO: Migrate rounding to its own function, its own section)

The final special circumstance, numbers that are too small to be represented as subnormal numbers,
should be handled as a natural consequence of adjusting the `number` to be able to properly encode it as a subnormal number.
Regardless, you will not be able to test underflow to zero using the assignment's driver code until later.


#### Check Your Work

[//]: # (TODO: Double-check that "recode 12.375 6" is still an option)

When you run *floatlab*, you can specify that you want to recode a value, such as <u>`recode 12.375`</u> and <u>`recode 12.375 6`</u>.
The program will first decode the value.
It will then adjust the exponent by the specified amount (if an amount is specified).
Then it will send the result to `encode()`.
Finally, it will print the original value and the `ieee754_t` value returned by `encode`.

- [ ] Compile and run *floatlab*, recoding a few values.

For example:
```
Enter ... "recode <value>",
    or "quit": recode 12.375
expected: 12.3750000000_{10}	0x41460000	+1.1000,1100,0000,0000,0000,000_{2} x 2^{3}
actual:   12.3750000000_{10}	0x41460000	+1.1000,1100,0000,0000,0000,000_{2} x 2^{3}

Enter ... "recode <value>",
    or "quit": recode 0x00055000
expected: 0.0000000000_{10}	0x00055000	+0.0000,1010,1010,0000,0000,000_{2} x 2^{-126}
actual:   0.0000000000_{10}	0x00055000	+0.0000,1010,1010,0000,0000,000_{2} x 2^{-126}
```

Try some other numbers to check that your `encode()` function correctly encodes the value that's in an `unnormal_t` data structure.

[//]: # (TODO: Exam bonus answer)

---

|                 [⬅️](04-examining-numbers.md)                  |      [⬆️](../README.md)      |             [➡️](06-multiply-divide.md)              | 
|:--------------------------------------------------------------:|:----------------------------:|:----------------------------------------------------:| 
| [Examining IEEE 754-Compliant Values](04-examining-numbers.md) | [Front Matter](../README.md) | [Multiplication and Division](06-multiply-divide.md) | 
