## Adder "Hardware"

> ⚠️ **Warning**
>
> The signed/unsigned inequality comparison functions `…less_than()`, `…at_most()`, `…at_least()`, and `…greater_than()` will *not* work until you have implemented `subtract()`!
> <small>(However, you shouldn't need these functions, so this should not be a limitation.)</small>


Now that you've warmed up to bitwise operations and implementing operations without using C's built-in operations, let us turn your attention to arithmetic.
Before you can add two $n$-bit values, you must be able to add two 1-bit values.


### TL;DR

- [ ] Implement a 1-bit full adder using bitwise operations.
- [ ] Compile and run *integerlab*, trying all possible values.


- [ ] Use your 1-bit full adder to implement a 32-bit ripple-carry adder.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### One Bit Full Adder

In the `one_bit_full_addition()` function, you will implement a 1-bit full adder;
that is, an adder that takes two operand bits and a carry-in bit, and it produces a sum bit and a carry-out bit.

The function takes one argument, a structure containing five fields.
As described in [the description of *alu.h*](01-getting-started.md#aluh), these five fields are the operand bits `a` and `b`, the carry-in bit `c_in`, the sum bit `sum`, and the carry-out bit `c_out`.
When the structure is passed in to the function, only `a`, `b`, and `c_in` are populated.
Your task is to populate the `sum` and `c_out` fields, and return the structure.

- [ ] Implement a 1-bit full adder using bitwise operations.

Because the fields are guaranteed to be strictly 1 or 0, you do not need to apply any of the test functions to reduce them to 1 or 0.

#### Check your work

- [ ] Compile and run *integerlab*, trying all possible values.

When you enter the inputs for your 1-bit full adder, only the least significant bit of each operand will be used.
For example:
```
Enter ... "add1 <binary_value1> <binary_value2> <carry_in>" ...: add1 0 0 0
expected: 0 + 0 + 0 = 0 carry 0
actual:   0 + 0 + 0 = 0 carry 0

Enter ... "add1 <binary_value1> <binary_value2> <carry_in>" ...: add1 0 0 1
expected: 0 + 0 + 1 = 1 carry 0
actual:   0 + 0 + 1 = 1 carry 0
```

Check your code with all eight possible inputs, comparing your actual results with the expected results.


### Ripple-Carry Adder

> 🪢 **Reminder**
>
> In a ripple-carry adder, the carry-out bit from bit position $n$ becomes the carry-in bit for bit position $n+1$.

Use whatever code that you need, that does not violate any of this assignment's constraints, to:

- [ ] Use your 1-bit full adder to implement a 32-bit ripple-carry adder.
  - [ ] Populate the input fields of a `one_bit_adder_t` variable and pass that variable to `one_bit_full_addition()`.
  - [ ] Use the `sum` bit to contribute to the 32-bit sum and the `c_out` bit as the `c_in` bit of the next bit position.
  - Repeat until you have added all 32-bit positions, resulting in the 32-bit sum.
    (Discard the final carry-out.)

#### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

When you enter the inputs for your 32-bit adder, the operands will be interpreted as hexadecimal values even if you omit the leading "0x", and only the least-significant bit of the carry-in will be used.
For example:
```
Enter ... "add32 <hex_value1> <hex_value2> <carry_in>" ...: add32 0x1a 0x22 0
expected: 0x0000001A + 0x00000022 + 0 = 0x0000003C
actual:   0x0000001A + 0x00000022 + 0 = 0x0000003C

Enter ... "add32 <hex_value1> <hex_value2> <carry_in>" ...: add32 1a 22 1
expected: 0x0000001A + 0x00000022 + 1 = 0x0000003D
actual:   0x0000001A + 0x00000022 + 1 = 0x0000003D
```

- [ ] Check your code with other values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

<font color="red">When you test your 32-bit adder, don't forget to test larger values, too</font>, such as:
```
Enter ... "add32 <hex_value1> <hex_value2> <carry_in>" ...: add32 0x76543210 0x89ABCDEF 0
expected: 0x76543210 + 0x89ABCDEF + 0 = 0xFFFFFFFF
actual:   0x76543210 + 0x89ABCDEF + 0 = 0xFFFFFFFF

Enter ... "add32 <hex_value1> <hex_value2> <carry_in>" ...: add32 0x76543210 0x89ABCDEF 1
expected: 0x76543210 + 0x89ABCDEF + 1 = 0x00000000
actual:   0x76543210 + 0x89ABCDEF + 1 = 0x00000000
```

---

|         [⬅️](04-logical-operations.md)         |      [⬆️](../README.md)      |            [➡️](06-addition-subtraction.md)            |
|:----------------------------------------------:|:----------------------------:|:------------------------------------------------------:|
| [Logical Operations](04-logical-operations.md) | [Front Matter](../README.md) | [Addition and Subtraction](06-addition-subtraction.md) |
