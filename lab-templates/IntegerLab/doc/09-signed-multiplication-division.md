## Signed Multiplication and Division (Bonus Credit)

> ⓘ **Note**
> 
> Implementing signed multiplication and division is an optional, extra-credit part of this assignment
> 
> *You are **not** required to implement signed multiplication and division.* 

Addition uses the same assembly code instruction for both signed and unsigned integers, as does subtraction.
Indeed, these instructions perform exact same actions regardless of whether the integers will be interpreted as signed or unsigned, which is why the overflow conditions for both are flagged.

Multiplication and division, however, have separate instructions for signed and unsigned integers.
This is because the logic for unsigned multiplication and division only produce correct results for non-negative numbers, and so the unsigned implementations cannot be used for negative integers.
The signed implementations cannot be used for unsigned integers because they treat half of the possible unsigned integers as though they were negative, yielding incorrect results.

A simple patch would be to keep track of which operands are negative, negate those operands so that they are positive, apply the unsigned implementation, and then negate the result as necessary.
*Using that patch technique will not earn you bonus credit.*
<font color="red">To earn bonus credit, you must address the underlying reason that the signed implementations need to be different.</font>


### Signed Multiplication

If we only cared about the 16-bit product, the lower 16 bits of the full 32-bit product, then the unsigned implementation works for both signed and unsigned integers.
The upper 16 bits, however, differ when `is_negative()` is true.
For example:
```text
Expression to evaluate: -3 * 8
MULTIPY_BY_POWER_OF_TWO
	expected: 0xFFFD * 0x0008 = 0x0007'FFE8
	actual:   0xFFFD * 0x0008 = 0x0007'FFE8
UNSIGNED MULTIPLICATION
	expected result (hexadecimal): 0xFFFD * 0x0008 = 0x0007'FFE8
	expected result (unsigned):    65533 * 8 = 65512 (524264)
	actual result (hexadecimal):   0xFFFD * 0x0008 = 0x0007'FFE8
	actual result (unsigned):      65533 * 8 = 65512 (524264)
SIGNED MULTIPLICATION (bonus credit)
	expected result (hexadecimal): 0xFFFD * 0x0008 = 0xFFFF'FFE8
	expected result (signed):      -3 * 8 = -24 (-24)
	actual result (hexadecimal):   0xFFFD * 0x0008 = 0xFFFF'FFE8
	actual result (signed):        -3 * 8 = -24 (-24)
		Number of calls to ripple_carry_addition:    48
		Number of calls to multiply_by_power_of_two: 17
```

Notice that in the example, the upper 13 bits are all 0s after unsigned multiplication but are all 1s after signed multiplication.
That should not be possible if the operands have only 0s above their lower 16 bits!
Think about what you can do to the operands to make it possible.

> ❗️ **Important**
>
> To receive bonus credit, you cannot simply make the operands positive and then possibly negate the product.
> 
> You *may* check whether the operands are negative and introduce a change to the operands, but you *may not* change the product after it has been computed.

If you chose to implement signed multiplication then step through your unsigned multiplication to see if you can find where it breaks down for negative operands.

- [ ] For bonus credit, implement `signed_multiply()` to correctly handle negative numbers when the arguments are interpreted as signed integers.
  - *Reminder: you may not change the signatures of any functions declared in *alu.h*; however, you may implement other helper functions if you wish.*
- [ ] Check your work with several values, both great and small.


### Signed Division

Recall that the semantics of integer division are that the fractional portion of the quotient be truncated;
that is, the quotient is rounded toward zero.
The fast division technique for powers of two used for unsigned integers, however, has the effect of rounding toward negative infinity.
This is fine for positive quotients, but it rounds negative quotients in the wrong direction.

For example, if we used unsigned fast division for signed division then we would see this:
```text
Expression to evaluate: -14 / 4
UNSIGNED DIVISION
	expected result (hexadecimal): 0xFFF2 / 0x0004 = 0x3FFC    0xFFF2 % 0x0004 = 0x0002
	expected result (unsigned):    65522 / 4 = 16380    65522 % 4 = 2
	actual result (hexadecimal):   0xFFF2 / 0x0004 = 0x3FFC    0xFFF2 % 0x0004 = 0x0002
	actual result (unsigned):      65522 / 4 = 16380    65522 % 4 = 2
		Number of calls to ripple_carry_addition:    1
		Number of calls to multiply_by_power_of_two: 1
SIGNED DIVISION (bonus credit)
	expected result (hexadecimal): 0xFFF2 / 0x0004 = 0xFFFD    0xFFF2 % 0x0004 = 0xFFFE
	expected result (signed):      -14 / 4 = -3    -14 % 4 = -2
	actual result (hexadecimal):   0xFFF2 / 0x0004 = 0xFFFD    0xFFF2 % 0x0004 = 0xFFFE
	actual result (signed):        -14 / 4 = -3    -14 % 4 = -2
		Number of calls to ripple_carry_addition:    3
		Number of calls to multiply_by_power_of_two: 1
```

If you chose to implement signed division then in your implementation of `signed_divide()`, 
whenever the dividend is negative you need to introduce a bias toward positive infinity to correct the rounding direction.

> ❗️ **Important**
>
> To receive bonus credit, you cannot simply make the operands positive and then possibly negate the quotient.
>
> You *may* check whether the dividend is negative, but you *may not* change the operands, and you *may not* change the quotient after it has been computed.

- [ ] For bonus credit, implement `signed_division()` to correctly handle negative dividends.
- [ ] Check your work with several values, both great and small.

---

|                  [⬅️](08-unsigned-multiplication-division.md)                  |      [⬆️](../README.md)      |         [➡️](10-grading.md)          |
|:------------------------------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Unsigned Multiplication and Division](08-unsigned-multiplication-division.md) | [Front Matter](../README.md) | [Turn-In and Grading](10-grading.md) |
