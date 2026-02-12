## Addition and Subtraction

> ⚠️ **Warning**
>
> The signed/unsigned inequality comparison functions `…less_than()`, `…at_most()`, `…at_least()`, and `…greater_than()` will *not* work until you have implemented `subtract()`!
> <small>(However, you shouldn't need these functions, so this should not be a limitation.)</small>


### TL;DR

- [ ] Use the 32-bit adder to add `addend` to `augend` (*i.e.*, calculate $augend + addend$).
- [ ] Place the 16-bit sum in the `alu_result_t` variable's `result` field.
- [ ] Assume that the operands are unsigned 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `unsigned_overflow` flag accordingly.
- [ ] Assume that the operands are signed 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `signed_overflow` flag accordingly.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


- [ ] Use the 32-bit adder to subtract `subtrahend` from `minuend` (*i.e.*, calculate $minuend - subtrahend$).
  - <font color="red">Apply a `0xFFFF` bitmask to your arguments when you call `ripple_carry_addition()` to make sure that only the 16-bit values are passed to `ripple_carry_addition()`!</font>
- [ ] Place the 16-bit difference in the `alu_result_t` variable's `result` field.
- [ ] Assume that the operands are unsigned 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `unsigned_overflow` flag accordingly.
- [ ] Assume that the operands are signed 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `signed_overflow` flag accordingly.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### 16-Bit Addition

The `add()` function, along with the other arithmetic functions, returns an `alu_result_t` structure.

Having implemented a 32-bit adder, you can use it for your 16-bit addition function.
Following the convention that the most significant bit is $bit_{31}$ and the least significant bit is $bit_0$ then:
- The 16-bit sum will be in $bits_{15..0}$, the lower 16 bits of the 32-bit adder's sum.
- Viewed from the perspective of 16-bit addition:
  - The 32-bit sum's $bit_{15}$ is the 16-bit value's most significant bit, and $bit_0$ is the 16-bit value's least significant bit.
  - The 32-bit sum's $bit_{16}$ is the final carry-out of 16-bit addition.


- [ ] Use the 32-bit adder to add `addend` to `augend` (*i.e.*, calculate $augend + addend$).
- [ ] Place the 16-bit sum in the `alu_result_t` variable's `result` field.
- [ ] Assume that the operands are unsigned 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `unsigned_overflow` flag accordingly.
- [ ] Assume that the operands are signed 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `signed_overflow` flag accordingly.

#### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

For example:
```
Enter ... a two-operand arithmetic expression... or "quit": 3 + 15
UNSIGNED ADDITION
    expected result (hexadecimal): 0x0003 + 0x000F = 0x0012
    expected result (unsigned):    3 + 15 = 18	overflow: false
    actual result (hexadecimal):   0x0003 + 0x000F = 0x0012
    actual result (unsigned):      3 + 15 = 18	overflow: false
SIGNED ADDITION
    expected result (hexadecimal): 0x0003 + 0x000F = 0x0012
    expected result (signed):      3 + 15 = 18	overflow: false
    actual result (hexadecimal):   0x0003 + 0x000F = 0x0012
    actual result (signed):        3 + 15 = 18	overflow: false

Enter ... a two-operand arithmetic expression... or "quit": 0x6000 + 0x3000
UNSIGNED ADDITION
    expected result (hexadecimal): 0x6000 + 0x3000 = 0x9000
    expected result (unsigned):    24576 + 12288 = 36864	overflow: false
    actual result (hexadecimal):   0x6000 + 0x3000 = 0x9000
    actual result (unsigned):      24576 + 12288 = 36864	overflow: false
SIGNED ADDITION
    expected result (hexadecimal): 0x6000 + 0x3000 = 0x9000
    expected result (signed):      24576 + 12288 = -28672	overflow: true
    actual result (hexadecimal):   0x6000 + 0x3000 = 0x9000
    actual result (signed):        24576 + 12288 = -28672	overflow: true
```

The expected overflow flags are obtained directly from flags set in the processor's ALU and are authoritative.

- [ ] Check your code with other values, comparing your actual results with the expected results.
  - Use positive and negative operands.
  - Generate sums that produce signed overflow, sums that produce unsigned overflow, and sums that produce neither.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### 16-Bit Subtraction

Having implemented a 32-bit adder, you can use it for your 16-bit subtraction function.

- [ ] Use the 32-bit adder to subtract `subtrahend` from `minuend` (*i.e.*, calculate $minuend - subtrahend$).
  - Use the adder using the technique discussed in Chapter~3 and in lecture
  - <font color="red">Apply a `0xFFFF` bitmask to your arguments when you call `ripple_carry_addition()` to make sure that only the 16-bit values are passed to `ripple_carry_addition()`!</font>
    - A subtle, normally-desirable, rule in the bitwise complement's semantics will cause 1s to be placed in $bits_{31..16}$.
      For our specific use, this is undesirable and so you need to force $bits_{31..16}$ to have 0s.
- [ ] Place the 16-bit difference in the `alu_result_t` variable's `result` field.
- [ ] Assume that the operands are unsigned 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `unsigned_overflow` flag accordingly.
- [ ] Assume that the operands are signed 16-bit integers and determine whether overflow occurred;
  set the `alu_result_t` variable's `signed_overflow` flag accordingly.

#### Check your work

- [ ] Compile and run *integerlab*`, trying a few values.

For example:
```
Enter ... a two-operand arithmetic expression... or "quit": 15 - 25
UNSIGNED SUBTRACTION
    expected result (hexadecimal): 0x000F - 0x0019 = 0xFFF6
    expected result (unsigned):    15 - 25 = 65526	overflow: true
    actual result (hexadecimal):   0x000F - 0x0019 = 0xFFF6
    actual result (unsigned):      15 - 25 = 65526	overflow: true
SIGNED SUBTRACTION
    expected result (hexadecimal): 0x000F - 0x0019 = 0xFFF6
    expected result (signed):      15 - 25 = -10	overflow: false
    actual result (hexadecimal):   0x000F - 0x0019 = 0xFFF6
    actual result (signed):        15 - 25 = -10	overflow: false

Enter ... a two-operand arithmetic expression... or "quit": 0x100 - 0x7F
UNSIGNED SUBTRACTION
    expected result (hexadecimal): 0x0100 - 0x007F = 0x0081
    expected result (unsigned):    256 - 127 = 129	overflow: false
    actual result (hexadecimal):   0x0100 - 0x007F = 0x0081
    actual result (unsigned):      256 - 127 = 129	overflow: false
SIGNED SUBTRACTION
    expected result (hexadecimal): 0x0100 - 0x007F = 0x0081
    expected result (signed):      256 - 127 = 129	overflow: false
    actual result (hexadecimal):   0x0100 - 0x007F = 0x0081
    actual result (signed):        256 - 127 = 129	overflow: false
```

As with addition, the expected overflow flags are obtained directly from flags set in the processor's ALU.

- [ ] Check your code with other values, comparing your actual results with the expected results.
  - Use positive and negative operands.
  - Generate differences that produce signed overflow, differences that produce unsigned overflow, and differences that produce neither.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

---

|        [⬅️](06-adders.md)        |      [⬆️](../README.md)      |                  [➡️](08-unsigned-multiplication-division.md)                  |
|:--------------------------------:|:----------------------------:|:------------------------------------------------------------------------------:|
| [Adder "Hardware"](06-adders.md) | [Front Matter](../README.md) | [Unsigned Multiplication and Division](08-unsigned-multiplication-division.md) |
