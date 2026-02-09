## Unsigned Multiplication and Division

### TL;DR

- [ ] Add code to `multiply_by_power_of_two()` so that if the `power_of_two` argument is 0, then the function returns 0.
- [ ] Add code to `multiply_by_power_of_two()` that assumes any other `power_of_two` is in fact a power of two,
  and apply the fast multiplication technique for powers of two discussed in Chapter~3 and in lecture.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.

In the `unsigned_multiply()` function:
- [ ] Use each of the `multiplier`'s bits, in turn, as the `power_of_two` argument to `multiply_by_power_of_two()` to multiply `multiplicand`.
  - You must implement long multiplication by calling `multiply_by_power_of_two()`.
- [ ] Add each of these intermediate products to arrive at the 32-bit product of $multiplicand \times multiplier$.
- [ ] Place the 16-bit product, the lower 16 bits of the full product, in `product`'s `result` field.
- [ ] Place the upper 16 bits of the full product in `product`'s `supplemental_result` field.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
  - Unless and until you implement signed multiplication, your "SIGNED MULTIPLICATION" actual results will differ from the expected results.
    *You are **not** required to implement signed multiplication.*
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

In the `unsigned_divide()` function:
- [ ] If the divisor is 0 then set the `divide_by_zero` flag.
- [ ] Otherwise, assume that `divisor` is a power of two, and implement fast division accordingly.
  <font color="red">*Do not implement general division.*</font>
- [ ] Place the quotient in `quotient`'s `result` field.
- [ ] Place the remainder in `quotient`'s `supplemental_result` field.
- [ ] Compile and run `***./integerlab***`, trying a few values.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### Multiplication by a Power of Two

Before you can perform long multiplication of arbitrary values, you must be able to multiply by a power of two.



Strictly speaking, the specification `multiply_by_power_of_two()` function requires it to do a little bit more than multiplying by a power of two;
it also needs to be able to multiply by zero.

- [ ] Add code to `multiply_by_power_of_two()` so that if the `power_of_two` argument is 0, then the function returns 0.
- [ ] Add code to `multiply_by_power_of_two()` that assumes any other value of `power_of_two` is in fact a power of two,
  and apply the fast multiplication technique for powers of two discussed in Chapter~3 and in lecture.

> ⓘ **Note**
>
> The second argument is the power of two value, such as 0x0040 ($2^6 = 64_{10}$) or 0x2000 ($2^{13} =  8192_{10}$).
> It is *not* the exponent of two, such as 6 or 13.

Be sure to remember that `multiply_by_power_of_two()` returns a 32-bit value.

<font color="red">Your solution for `multiply_by_power_of_two()` must be a constant-time solution.</font>
If your solution includes a loop or recursion, please review the Chapter~3 material.

#### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

When you enter the inputs for your power-of-two multiplier, the operands will be interpreted as hexadecimal values even if you omit the leading "0x".
For example:
```
Enter ... "mul2 <hex_value> <hex_power_of_two>" ...:  mul2 5 4
expected: 0x0005 * 0x0004 = 0x00000014
actual:   0x0005 * 0x0004 = 0x00000014

Enter ... "mul2 <hex_value> <hex_power_of_two>" ...:  mul2 5 0
expected: 0x0005 * 0x0000 = 0x00000000
actual:   0x0005 * 0x0000 = 0x00000000

Enter ... "mul2 <hex_value> <hex_power_of_two>" ...:  mul2 0xFFFF 0x8000
expected: 0xFFFF * 0x8000 = 0x7FFF8000
actual:   0xFFFF * 0x8000 = 0x7FFF8000
```

- [ ] Check your code with other values, comparing your actual results with the expected results.


### General Unsigned Multiplication

The distributive property of multiplication tells us that if $multiplier = \sum_{i=0}^{31}multiplier_i \times 2^i$ then

$$
multiplicand \times multiplier = multiplicand \times \sum_{i=0}^{31}multiplier_i \times 2^i
$$ $$
\phantom{multiplicand \times multiplier} = \sum_{i=0}^{31} multiplicand \times multiplier_i \times 2^i
$$

In the `unsigned_multiply()` function:

- [ ] Use each of the `multiplier`'s bits, in turn, as the `power_of_two` argument to `multiply_by_power_of_two()` to multiply `multiplicand`.
  - You must implement long multiplication by calling `multiply_by_power_of_two()`.
    Alternate algorithms, such as peasant multiplication, are prohibited.
    You should not even consider superpolynomial algorithms, such as repeatedly adding the multiplicand to itself $multiplier$ times.
- [ ] Add each of these intermediate products to arrive at the 32-bit product of $multiplicand \times multiplier$.

When multiplying two 16-bit operands, some real ALUs will spread the 32-bit full product across two 16-bit registers.
High-level languages will only access the register containing the 16-bit product when assigning the result to the destination variable.
Assembly language, however, lets programmers access both registers.

- [ ] Place the 16-bit product, the lower 16 bits of the full product, in `product`'s `result` field.
- [ ] Place the upper 16 bits of the full product in `product`'s `supplemental_result` field.

#### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

> ⓘ **Note**
>
> Unless and until you implement signed multiplication, your "SIGNED MULTIPLICATION" actual results will differ from the expected results.
> *You are **not** required to implement signed multiplication.*

For example:
```
Enter ... a two-operand arithmetic expression... or "quit": 3 * 5
UNSIGNED MULTIPLICATION
    expected result (hexadecimal): 0x0003 * 0x0005 = 0x0000'000F
    expected result (unsigned):    3 * 5 = 15 (15)
    actual result (hexadecimal):   0x0003 * 0x0005 = 0x0000'000F
    actual result (unsigned):      3 * 5 = 15 (15)
SIGNED MULTIPLICATION
    expected result (hexadecimal): 0x0003 * 0x0005 = 0x0000'000F
    expected result (signed):      3 * 5 = 15 (15)
    actual result (hexadecimal):   0x0003 * 0x0005 = 0x0000'0000
    actual result (signed):        3 * 5 = 0 (0)

Enter ... a two-operand arithmetic expression... or "quit": 0x234 * 0x345
UNSIGNED MULTIPLICATION
    expected result (hexadecimal): 0x0234 * 0x0345 = 0x0007'3404
    expected result (unsigned):    564 * 837 = 13316 (472068)
    actual result (hexadecimal):   0x0234 * 0x0345 = 0x0007'3404
    actual result (unsigned):      564 * 837 = 13316 (472068)
SIGNED MULTIPLICATION
    expected result (hexadecimal): 0x0234 * 0x0345 = 0x0007'3404
    expected result (signed):      564 * 837 = 13316 (472068)
    actual result (hexadecimal):   0x0234 * 0x0345 = 0x0000'0000
    actual result (signed):        564 * 837 = 0 (0)
```

The expected results (including the upper 16 bits) come directly from the registers used by processor's ALU and are authoritative.

- [ ] Check your code with other values, comparing your actual results with the expected results. 
  - Generate products that fit within the lower 16 bits and products that require more.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### Unsigned Division by a Power of Two

As discussed in Chapter~3 and in lecture, there is a fast division technique when the divisor is a power of two.
In the `unsigned_divide()` function:

- [ ] If the divisor is 0 then set the `divide_by_zero` flag.
- [ ] Otherwise, use that fast technique to implement division by a power of two.

<font color="red">*Do not implement general division.*</font>

When dividing integers, some real ALUs will place the quotient in one register and the remainder in another.
When assigning the result to the destination variable, a high-level language will only access the register containing the quotient or the register containing the remainder, depending on whether the program called for division or the modulo operator.
Assembly language, however, lets programmers access both registers.

- [ ] Place the quotient in `quotient`'s `result` field.
- [ ] Place the remainder in `quotient`'s `supplemental_result` field.

<font color="red">Your solution to determine the quotient should be a constant-time solution.</font>
If your solution includes a loop or recursion, please review the Chapter~3 material.

#### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

> ⓘ **Note**
>
> Unless and until you implement signed division, your "SIGNED DIVISION" actual results will differ from the expected results.
> *You are **not** required to implement signed division.*

For example:
```
Enter ... a two-operand arithmetic expression... or "quit": 70 / 8
UNSIGNED DIVISION
    expected result (hexadecimal): 0x0046 / 0x0008 = 0x0008    0x0046 % 0x0008 = 0x0006
    expected result (unsigned):    70 / 8 = 8    70 % 8 = 6
    actual result (hexadecimal):   0x0046 / 0x0008 = 0x0008    0x0046 % 0x0008 = 0x0006
    actual result (unsigned):      70 / 8 = 8    70 % 8 = 6
SIGNED DIVISION
    expected result (hexadecimal): 0x0046 / 0x0008 = 0x0008    0x0046 % 0x0008 = 0x0006
    expected result (signed):      70 / 8 = 8    70 % 8 = 6
    actual result (hexadecimal):   0x0046 / 0x0008 = 0x0000    0x0046 % 0x0008 = 0x0000
    actual result (signed):        70 / 8 = 0    70 % 8 = 0

Enter ... a two-operand arithmetic expression... or "quit": 0x29B / 0x40
UNSIGNED DIVISION
    expected result (hexadecimal): 0x029B / 0x0040 = 0x000A    0x029B % 0x0040 = 0x001B
    expected result (unsigned):    667 / 64 = 10    667 % 64 = 27
    actual result (hexadecimal):   0x029B / 0x0040 = 0x000A    0x029B % 0x0040 = 0x001B
    actual result (unsigned):      667 / 64 = 10    667 % 64 = 27
SIGNED DIVISION
    expected result (hexadecimal): 0x029B / 0x0040 = 0x000A    0x029B % 0x0040 = 0x001B
    expected result (signed):      667 / 64 = 10    667 % 64 = 27
    actual result (hexadecimal):   0x029B / 0x0040 = 0x0000    0x029B % 0x0040 = 0x0000
    actual result (signed):        667 / 64 = 0     667 % 64 = 0

Enter ... a two-operand arithmetic expression... or "quit": 53 / 0
UNSIGNED DIVISION
    expected result: divide-by-zero
    actual result:   divide-by-zero
SIGNED DIVISION
    expected result: divide-by-zero
    actual result (hexadecimal):   0x0035 / 0x0000 = 0x0000    0x0035 % 0x0000 = 0x0000
    actual result (signed):        53 / 0 = 0    53 % 0 = 0
```

The expected results (including the remainder) come directly from the registers used by processor's ALU and are authoritative.

- [ ] Check your code with other values, comparing your actual results with the expected results.
  - Remember that the divisor must be either 0 or a power of two.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

---

|            [⬅️](07-addition-subtraction.md)            |      [⬆️](../README.md)      |                 [➡️](09-signed-multiplication-division.md)                 |
|:------------------------------------------------------:|:----------------------------:|:--------------------------------------------------------------------------:|
| [Addition and Subtraction](07-addition-subtraction.md) | [Front Matter](../README.md) | [Signed Multiplication and Division](09-signed-multiplication-division.md) |
