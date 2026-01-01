## `unnormal_t` and Its Functions

The `unnormal_t` data type is a structure with fields for the sign bit, the integer portion, the fractional portion, and the exponent.
It also has flags for Not-a-Number and for Infinity.
Unlike the IEEE&nbsp;754 format, an `unnormal_t` value can have more than one bit in its integer portion.

<span style="background-color: pink">The `unnormal_t` type does not correspond to any floating point type described in the IEEE&nbsp;754 standard!</span>

> ❗️ **Important**
> 
> You should *not* access the `unnormal_t` fields directly.
> Instead, use the `unnormal()` macro to create an `unnormal_t` value, the accessor functions that we provide to retrieve the fields, and the modifier functions that we provide to make adjustments in a **value-preserving** manner.
> These functions are pass-by-value "pure" functions; there is no observable effect if you do not use the value returned.

> ⓘ **Note**
> 
> While you typically will see non-primitive variables passed by reference to C functions, the `unnormal_t` functions use pass-by-value.
> This is considerably less efficient in both time and memory (and there are other downsides beyond the scope of what you've learned so far);
> however, passing the `unnormal_t` variables by value ensures that there will be no aliased variables and also that memory management will be handled by the program stack.
> <font color="red">This means that the variables passed as arguments to functions will be unchanged, and if an `unnormal_t` variable is returned then it will be a modified copy of the original.</font>
> A consequence of this is that *you must make sure that you always use the value returned by a function if you expect to use the effect of the function.*

You can, and should, look at the functions' signatures in *unnormal.h*.
<font color="red">The shift functions and the alignment functions are *value-preserving*: changes to the significand create corresponding changes to the exponent, and vice-versa.</font>
We summarize the functions that you are likely to use here (there are more functions than we list here, and you may use *any* function that is declared in *unnormal.h*):

- Creating and printing an `unnormal_t` value (all necessary calls to these functions are in the starter code)
  - **unnormal()** returns an `unnormal_t` value (*not* a pointer) based on the arguments provided.
    The argument list is a series of dot-prefixed named fields (such as `.sign=0, .infinity=1`) whose meanings are the obvious ones from the class discussion about floating point numbers.
    <span style="background-color: lime;">The `.exponent` argument, if included, is expected to be a two's complement value.</span>
    <span style="background-color: yellow;">The `.fraction` argument, if included, is expected to be the numerator of $\frac{\mathtt{.fraction}\ argument}{2^{64}}$ (*i.e.*, the $2^{-1}$ bit is $bit_{63}$).
  - **unnormal_to_string()** returns a string representation of the value.
      Because of the number of bits available in the `unnormal_t` fields, the significand is represented in base-16, though the exponent is the exponent of 2.
- Accessors
  - **get_unnormal_sign()** returns 0 if the value is positive, 1 if the value is negative
  - **get_unnormal_integer()** returns a `uint64_t` storing the unsigned integer representation of the value's integer portion
  - **get_unnormal_fraction()** returns a `uint64_t` storing the numerator of $\frac{get_fraction()}{2^{64}}$ (*i.e.*, the $2^{-1}$ bit is $bit_{63}$)
  - **get_unnormal_exponent()** returns a `int16_t` storing the two's complement representation of the exponent
  - **is_infinite()** returns 0 if the value is finite (or NaN), 1 if the value is $\pm\infty$
  - **is_not_a_number()** returns 0 if the value is a valid number, 1 if the value is not a number
- Bit shifts (some of these functions are equivalent to each other, to support whichever mental model works for you)
  - **shift_left_once()** aka `decrement_exponent()`, aka `move_binary_point_to_the_right()` -- shifts the significand's bits to the left by one position, having the effect of moving the binary point to the right and decreasing the exponent by one
  - **shift_right_once()** aka `increment_exponent()`, aka `move_binary_point_to_the_left()` -- shifts the significand's bits to the right by one position, having the effect of moving the binary point to the left and increasing the exponent by one
- Alignment functions (shifts bits by specifying the desired result instead of the amount)
  - **place_all_bits_in_integer()** aka `prepare_for_arithmetic()` shifts the significand such that the least-significant `1` bit is in the $2^0$ position, with a corresponding change in the exponent (the fraction, of course, will be 0)
  - **set_integer()** if possible, shifts the significand such that the resulting integer portion is the specified value, with a corresponding changes in the fraction and exponent
  - **set_exponent()** shifts the significand, with a corresponding change in the exponent, such that the resulting exponent is the specified value
- Static Warnings (warnings based on the current bit positions)
  - **addition_is_unreliable()** indicates that there are `1` bits far enough to the left of the binary point that addition could yield a sum whose integer portion exceeds the available bits
- Dynamic Warnings (warnings that result from the last function call)
  - **created_number_is_improbable()** indicates that a call to `unnormal()` was made with all of the fraction's `1` far enough from the binary point that it is unlikely to have been the intended value (because it is *possible* that the requested fraction is also the intended fraction, an Unnormal value with the requested fraction will still be created)
- Prediction Functions (warnings that indicate what will happen in the next operation)
  - **left_shift_will_make_addition_unreliable()** indicates that if the next function is `left_shift_once()` (or one of its aliases) then after that function call,  `addition_is_unreliable()` will return `true`

<!--
- Unmentioned Functions
  - **shift_left()** shifts the significand's bits to the left by a specified amount
  - **shift_right()** shifts the significand's bits to the right by a specified amount

  - **multiplication_is_not_recommended()** indicates that there are `1` bits to the right of the binary point:
    if there are `1` bits in the fraction, then there will be extra bookkeeping that you will be responsible for;
    we recommend that you attempt multiplication only when all `1` bits are in the integer portion
  - **multiplication_is_unreliable()** indicates that there are `1` bits far enough to the left of the binary point that multiplication could yield a product whose integer portion exceeds the available bits

  - **shift_overflowed()** indicates that one or more `1` bit shifted to the left beyond the available bits
  - **shift_underflowed()** indicates that one or more `1` bit shifted to the right beyond the available bits
  - **operation_was_not_performed()** indicates that the previous function did not have the desired result, such as attempting to shift by a negative amount or attempt to set an integer value whose bits are not present in the significand

  - **fraction_will_carry_into_integer_on_addition()** indicates that if the next operation is addition with the specified values, then adding the fractions will carry into the integer portion, requiring you to add 1 to the sum's integer
  - **fraction_will_borrow_from_integer_on_subtraction()** indicates that if the next operation is subtraction with the specified values, then subtracting the fractions will require "borrowing" from the integer portion, requiring you to subtract 1 to the difference's integer
  - **left_shift_will_make_multiplication_unreliable()** indicates that if the next function is `left_shift_once()` (or one of its aliases) then after that function call, `multiplication_is_unreliable()` will return `true`
  - **left_shift_will_overflow()** indicates that if the next function is `left_shift_once()` (or one of its aliases) then after that function call, `shift_overflowed()` will return `true`
  - **right_shift_will_underflow()** indicates that if the next function is `right_shift_once()` (or one of its aliases) then after that function call, `shift_underflowed()` will return `true`
-->

---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |          [➡️](03-constants-queries.md)           |
|:----------------------------------------:|:----------------------------:|:------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Constants and Queries](03-constants-queries.md) |
