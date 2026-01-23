## Logical Operations

Implementing logical NOT, logical AND, and logical OR is not quite as simple as applying the corresponding bitwise operations, but it is very nearly so.

### TL;DR

- [ ] Implement `logical_not()` to return `true` if and only if its argument is considered to be `false`.
- [ ] Implement `logical_and()` to return `true` if and only if its two arguments are considered to be `true`.
- [ ] Implement `logical_or()` to return `true` if and only if at least one of its two arguments is considered to be `true`.
- [ ] Compile and run *integerlab*, trying several values, comparing your actual results with the expected results.
  - Note that you will receive a warning for an unused variable in `ripple_carry_addition()`;
    this is okay for now
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`


### logical_not()

When is a value considered to be `false`?
From among the tests that you have available, one of these will return `true` when that condition is satisfied, and `false` when it is not.

- [ ] Implement `logical_not()` to return `true` if and only if its argument is considered to be `false`.


### logical_and() and logical_or()

When is a value considered to be `true`?
From among the tests that you have available, one of these will return `true` when that condition is satisfied, and `false` when it is not.
Specifically, it will return a 1 or a 0, as appropriate.

You cannot simply apply bitwise AND and bitwise OR to the original values because their bits might not line up -- for example, `0x5 & 0xA == 0x0`.
After you reduce these values to a 1 or a 0, then their bits will line up, and then you can apply a bitwise operation to the results of the aforementioned test.

- [ ] Implement `logical_and()` to return `true` if and only if its two arguments are considered to be `true`.
- [ ] Implement `logical_or()` to return `true` if and only if at least one of its two arguments is considered to be `true`.

> ⓘ **Note**
> 
> You are not required to preserve C's "shortcut evaluation" of the logical AND and logical OR operations.
> Indeed, you cannot because the semantics of C's functions requires that both arguments to `logical_and()` and `logical_or()` be evaluated before your code has the opportunity to determine their truth values.

### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

For example:
```
Enter a one- or two-operand logical expression or "quit": !0
expected: !0 = 1
actual:   !0 = 1

Enter a one- or two-operand logical expression or "quit": !1
expected: !1 = 0
actual:   !1 = 0

Enter a one- or two-operand logical expression or "quit": 0 && 42
expected: 0 && 42 = 0
actual:   0 && 42 = 0

Enter a one- or two-operand logical expression or "quit": 0 || 73
expected: 0 || 73 = 1
actual:   0 || 73 = 1
```

- [ ] Check your code with other values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

---

|                     [⬅️](03-negative-and-equality.md)                      |      [⬆️](../README.md)      |            [➡️](05-zero-sign-extend.md)            |
|:--------------------------------------------------------------------------:|:----------------------------:|:--------------------------------------------------:|
| [Checking the Sign, and Testing for Equality](03-negative-and-equality.md) | [Front Matter](../README.md) | [Zero- and Sign-Extension](05-zero-sign-extend.md) |
