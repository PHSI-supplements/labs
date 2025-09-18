## Utility Functions

> ⚠️ **Warning**
> 
> The signed/unsigned inequality comparison functions `…less_than()`, `…at_most()`, `…at_least()`, and `…greater_than()` will *not* work until you have implemented `subtract()`!
> <small>(However, you shouldn't need these functions, so this should not be a limitation.)</small>

- [ ] Open *basetwo.c* in your editor.
  You will see the stubs of two functions there.


### TL;DR

- [ ] Implement the `exponentiate()` function using a bit shift operation.
- [ ] Implement the `lg()` function using a `switch` statement.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
  - Note that you will receive a warning for an unused variable in `ripple_carry_addition()`;
    this is okay for now
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

### exponentiate()

This function produces a power of two.
Treating its argument as an exponent, it returns the value $2^{exponent}$ when $0 \le exponent < 32$.
If $exponent < 0$ or $exponent \ge 32$, the function must return *something*, but we do not require that it returns any specific value.

A characteristic of powers of two is that when represented in binary, exactly one bit is 1 and all others are 0.

- [ ] Implement the `exponentiate()` function using a bit shift operation.

You should be able to implement this function with a single line of code,
but you may use more than one line.


### lg()

This function is the inverse of `exponentiate()`:
it produces the base-2 logarithm of its argument.
Assuming its argument is a power of two, then if $power\_of\_two = 2^{exponent}$, the function will return $exponent$.
If the argument is not a power of two, the function must return *something*, but we do not require that it returns any specific value.

There are some very short solutions that will work if you have already implemented arithmetic.
Since you haven't, the function stub begins an alternative:
use a `switch` statement, enumerating the 32 possible cases and returning the appropriate value in each case.

- [ ] Implement the `lg()` function using a `switch` statement.

### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

For example:
```
Enter a one- or two-operand logical expression,
    a two-operand comparison expression, a two-operand arithmetic expression,
    "lg <value>" or "exponentiate <value>" to test your powers-of-two code,
    "is_negative <value>" to determine if 2's complement value is negative,
    "add1 <binary_value1> <binary_value2> <carry_in>" for 1-bit full adder,
    "add32 <hex_value1> <hex_value2> <carry_in>" for 32-bit ripple-carry adder,
    or "quit": exponentiate 10
expected: 2**10 == 0x00000400 == 1024
actual:   2**10 == 0x00000400 == 1024

Enter ... "lg <value>" or "exponentiate <value>" ... or "quit": lg 1024
expected: log2 1024 == log2 0x00000400 == 10
actual:   log2 1024 == log2 0x00000400 == 10

Enter ... "lg <value>" or "exponentiate <value>" ... or "quit": lg 0x0400
expected: log2 1024 == log2 0x00000400 == 10
actual:   log2 1024 == log2 0x00000400 == 10
```

The expected results come from the *math* library's `exp2()` and `log2()` functions.
The actual results come, of course, from the code you wrote.

- [ ] Check your code with other values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |                     [➡️](03-negative-and-equality.md)                      |
|:----------------------------------------:|:----------------------------:|:--------------------------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Checking the Sign, and Testing for Equality](03-negative-and-equality.md) |
