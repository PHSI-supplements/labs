## Checking the Sign, and Checking for Equality

> ⚠️ **Warning**
>
> The signed/unsigned inequality comparison functions `…less_than()`, `…at_most()`, `…at_least()`, and `…greater_than()` will *not* work until you have implemented `subtract()`!
> <small>(However, you shouldn't need these functions, so this should not be a limitation.)</small>

- [ ] Open *basetwo.c* in your editor.
  You will see the stubs of two functions there.


### TL;DR

- [ ] Implement `is_negative()` to determine whether its argument, when interpreted as a signed value, is negative.
- [ ] Consider what the output of each of those three bitwise operations would be if the two operands were the same, and what the output would be if the two operands were different.
- [ ] Implement `equal()` to return `true` if and only if its two arguments are the same value.
- [ ] Implement `not_equal()` to return `true` if and only its two arguments are not the same value.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
    - Note that you will receive a warning for an unused variable in `ripple_carry_addition()`;
      this is okay for now
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### is_negative()

Real ALUs typically have hardware dedicated to quickly determining whether a value is 0 or not, and *alu.h* includes the macros `is_zero()` and `is_not_zero()` to serve this purpose.
Real ALUs also typically have hardware dedicated to quickly determine whether an integer, when treated as a signed value, is negative.

- [ ] Implement `is_negative()` to determine whether its argument, when interpreted as a signed value, is negative.

The function shall return 1 when the value is negative, and 0 when it is non-negative.
You should be able to implement this function in a single line of code (but you may use more, provided you comply with the assignment's constraints).


### equal() and not_equal()

The general approach to comparing two values requires arithmetic, as will be covered in [the textbook's Chapter 6](https://unl.grlcontent.com/compeng2e/page/chapter6).
If you do not anticipate testing the equality of two values in your arithmetic, then you can postpone implementing `equal()` and `not_equal()` until later.
On the other hand, if you think that you might need to test for equality as part of your arithmetic functions, there is a simple test for equality that does not require arithmetic.

To implement each of the `equal()` and `not_equal()` functions, you will need one of the 2-operand bitwise operations, either bitwise AND, bitwise OR, or bitwise XOR.
- What is $(a\text{ AND }a)$?
- What is $(a\text{ OR }a)$?
- What is $(a\text{ XOR }a)$?

Notice that only one of these operations produces something "interesting" when the two operands are the same.

So far, you have three tests to characterize a value: `is_zero()`, `is_not_zero()`, and `is_negative()`.
If you apply the right test to the output of the right bitwise operation, you'll have your implementation of `equal()`.
The opposite test to the same bitwise operation naturally gives you `not_equal()`.

- [ ] Consider what the output of each of those three bitwise operations would be if the two operands were the same, and what the output would be if the two operands were different.

One of those six possibilities will have a predictable output that can be evaluated with one or more of the three existing tests.

- [ ] Implement `equal()` to return `true` if and only if its two arguments are the same value.
- [ ] Implement `not_equal()` to return `true` if and only its two arguments are not the same value.


### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

For example:
```
Enter ... "is_negative <value>" ... or "quit": is_negative 1
expected: 1 (0x0001) is not negative
actual:   1 (0x0001) is not negative

Enter ... "is_negative <value>" ... or "quit": is_negative -1
expected: -1 (0xFFFF) is negative
actual:   -1 (0xFFFF) is negative

Enter ... a two-operand comparison expression ... or "quit": 1 == 1
expected: (1 == 1) = 1
actual:   (1 == 1) = 1

Enter ... a two-operand comparison expression ... or "quit": 1 != 1
expected: (1 != 1) = 0
actual:   (1 != 1) = 0

Enter ... a two-operand comparison expression ... or "quit": 1 == -1
expected: (1 == -1) = 0
actual:   (1 == -1) = 0

Enter ... a two-operand comparison expression ... 1 != -1
expected: (1 != -1) = 1
actual:   (1 != -1) = 1
```

- [ ] Check your code with other values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

---

|        [⬅️](02-utility-functions.md)         |      [⬆️](../README.md)      |         [➡️](04-logical-operations.md)         |
|:--------------------------------------------:|:----------------------------:|:----------------------------------------------:|
| [Utility Functions](02-utility-functions.md) | [Front Matter](../README.md) | [Logical Operations](04-logical-operations.md) |
