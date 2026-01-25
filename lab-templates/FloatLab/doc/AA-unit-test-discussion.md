## Appendix: Unit Test Discussion

Floating point types require special care in unit tests.
Due to non-associativity and non-distributivity, floating-point computations that are mathematically equivalent may yield different results depending on evaluation order and rounding.
Because of this, the code under test may be correct even when the computed value does not exactly match the expected value.

For this reason, unit testing frameworks allow (and often require) comparisons of floating point values to have a *delta*, which specifies an acceptable tolerance for differences between actual and expected results.

The simple unit testing framework provided for your optional use allows you to compare floating point values with- or without a delta.
Unusually, but beneficial for this assignment, our unit testing framework allows you to include a delta when comparing integers.

Let us take a look at the commented-out tests in *test/unit-tests.c*.


### Float Converter

The *unit-tests.c* file includes a `union` that can be used to type-pun a `float` value into an `ieee754_t` bit vector, and vice-versa.

```c
union float_converter {
    ieee754_t bit_vector;
    float reference_value;
};
```

The assignment's constraints prohibit the use of a `union` in your gradable code,
but it's perfectly acceptable in your unit tests.

You can use it to authoritatively obtain the bit vector for a floating point value:
```c
float value_float = ...;
ieee754_t value_bit_vector = ((union float_converter) {.reference_value = value_float}).bit_vector;
```

and to obtain the floating point value for a bit vector:
```c
ieee754_t value_bit_vector = ...;
float value_float = ((union float_converter) {.bit_vector = value_bit_vector}).reference_value;
```


### Should You Use `ASSERT_EQUAL` or `ASSERT_ALMOST_EQUAL`?

That depends.

If you haven't yet implemented `round_to_nearest_even()` then `ASSERT_ALMOST_EQUAL()` is probably what you want.
We carefully selected example tests for *[05-normalization.md](05-normalization.md)*, *[06-multiply-divide.md](06-multiply-divide.md)*, and *[07-add-subtract.md](07-add-subtract.md)*
that would not have an observable rounding error.
However, if you do not take similar precautions when writing test cases, then your actual result may differ from the expected result due to a rounding error.

After you have implemented rounding, then you'll want to use `ASSERT_EQUAL()` so that you catch errors in `round_to_nearest_even()`.


### Should You Compare `float`s or `ieee754_t`s in the ASSERT Macros?

If your tests pass, it really doesn't matter, though comparing `ieee754_t`s is simpler in one regard.
If you haven't yet implemented `round_to_nearest_even()`, then the `delta` value for `ASSERT_ALMOST_EQUAL()` when comparing `ieee754_t`s will *always* be 1.
```c
ASSERT_ALMOST_EQUAL(expected_result_bit_vector, actual_result, 1);
```
The `delta` value when comparing `float`s will vary from test to test -- 
too small, and a rounding error will cause the test to fail;
too big, and the test may pass with an incorrect result.

On the other hand, if a test fails, then the error message from comparing `ieee754_t`s will provide you with the bit vector, because the `ASSERT` macros will interpret an `ieee754_t` value as an integer:
```
Expected 1093580881 (0x412EB851) ± 1 (0x00000001), got 1076803665 (0x402EB851) at ...
```
That is useful for diagnosing errors in specific bits.

The error message from comparing `float`s will provide you with the floating point value:
```
Expected 10.919999 (0x1.5d70a2p+3) ± 9.5367432e-07 (0x1p-20), got 2.7299998 (0x1.5d70a2p+1) at ...
```
That is useful for diagnosing arithmetic problems.
(You can see this particular exponent problem in both the bit vector and in the floating point value, but the problem may be more obvious to you in the floating point value.)


---

|         [⬅️](10-grading.md)          |      [⬆️](../README.md)      |                   |
|:------------------------------------:|:----------------------------:|:-----------------:|
| [Turn-In and Grading](10-grading.md) | [Front Matter](../README.md) |                   |
