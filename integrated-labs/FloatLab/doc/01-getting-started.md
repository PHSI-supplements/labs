## Getting Started

> 📇 **Scenario**
>
> Herb tells you that, Eclectic Electronics tested the integrated circuit that the C-licon tool created from your ALU code, and they've concluded that C-licon is ready to use for their new experimental microprocessor.
> He tasks you with writing C code (that will be used by the C-licon tool) to implement a Floating Point Unit (FPU).
> Your task will be to implement floating point addition, subtraction, multiplication, and division.
> You can use any bit operations and, thanks to the ALU you wrote, you can use any integer arithmetic operations (use the conventional + - * / operators).
> Because the FPU has not yet been implemented, you cannot use C's floating point operations, you cannot use `float`s nor `double`s, and you cannot use library functions.

During your lab period, the TAs will provide a refresher of the IEEE&nbsp;754 format, with a particular emphasis on single-precision floating point numbers.
During the remaining time, the TAs will be available to answer questions.


### Configuring the Project

#### From VS Code

If you open *only* the `FloatLab` directory in VS Code, then VS Code will automatically configure the project.
If instead you open the whole lab repository (so `FloatLab` is just a subdirectory), then VS Code will *not* configure the `FloatLab` project automatically.
If autoconfiguration doesn't happen, then open the Command Palette.
From the Command Palette, select `CMake: Select Configure Preset`.
Then select the preset of your choice:

- `default` -- developing on nuros
- `personal-computer` -- developing on your computer

#### From the Command Line

- `cmake --preset default` -- developing on nuros
- `cmake --preset personal-computer` -- developing on your computer


### How the Program will Parse Numbers

When you run the *build/floatlab*, you will be prompted:

```
Enter a value, a two-operand arithmetic expression,
    "decode <value>", "recode <value>",
    or "quit":
```

When you enter a value, if it is prepended with `***0x***` then the parser will treat it as a bit vector;
otherwise, the parser will treat it as a floating point value.

For now, type `***quit***` to exit the program.


### Problem Decomposition

As was the case with IntegerLab -- as is the case for a great many problems -- FloatLab is best solved by decomposing it into smaller, manageable problems and then using the solutions to the smaller problems to solve the larger problem.
While the TAs' review of the IEEE 754 format is fresh on your minds, we recommend that you and your partner think about some bitmasks that would be useful for this lab.
After that, create some constants based on your understanding of IEEE 754.
You can then use some of the bitmasks and your understanding of IEEE 754 to create some simple functions to test qualities of an IEEE 754 formatted value.

With those small problems taken care of, you can use them to determine an IEEE 754 formatted value's mathematical value.
You'll first do this to be able to print a floating point value, and then you'll do this to convert a floating point number into a form that will make arithmetic easier.
Then you'll use your understanding of IEEE 754 to place a floating point value into the IEEE 754 format.

With those tasks complete, you have everything you need to apply your understanding of floating point arithmetic to implement the `add()`, `subtract()`, `multiply()`, and `divide()` functions.


### Descriptions of FloatLab Files, Data Structures, and Helper Functions

#### floatlab.c

Do not edit *floatlab.c*.

This file contains the driver code for the lab, as well as a couple of helper functions.
It parses your input, calls the appropriate arithmetic function, and displays the output.

#### fpu.h

Do not edit *fpu.h*.

This header file contains a type definition.
**`ieee754_t`** is a 32-bit bit vector that represents a floating point number.
The bit vector is to be interpreted as though it were a single-precision floating point value in the IEEE 754 format.
The value may be in the normal form, the subnormal form, or one of the special cases (NaN, infinity, or zero).

The header file also contains several function declarations.
The requirements for these functions will be discussed later in this assignment.

#### unnormal.h & unnormal.c
Do not edit *unnormal.h*.
Do not edit *unnormal.c*.

These files provide an encapsulation of the **`unnormal_t`** data type.
The data type and its functions are described on the [next page](02-unnormal_t.md).

#### fpu.c

This file contains stubs for constants and functions you need to create.

- Constants
  - **SIGN_BIT_MASK** can be used to determine whether an `ieee754_t` value is positive or negative
  - **EXPONENT_BITS_MASK** can be used to isolate the bits used to encode the exponent in an `ieee754_t` value
  - **FRACTION_BITS_MASK** can be used to isolate the bits used for the fraction in an `ieee754_t` value
  - **EXPONENT_BIAS** is the single-precision exponent bias
  - **NUMBER_OF_FRACTION_BITS** is the number of bits used for the fraction field in a single-precision floating point number
  - **NAN** is a bit vector for an `ieee754_t` value that is not a number
  - **INFINITY** is the bit vector for an `ieee754_t` value that is too great to be represented with the available bits
- Query functions
  - **is_infinity()** reports whether an `ieee754_t` value is positive or negative infinity
  - **is_nan()** reports whether an `ieee754_t` value is a legal NaN bit vector
  - **is_zero()** reports whether an `ieee754_t` value is positive or negative zero
  - **is_negative()** reports whether an `ieee754_t` value is negative
- Functions to examine `ieee754_t` values
  - **ieee754_to_string()** converts an `ieee754_t` value into a meaningful string
  - **decode()** converts an `ieee754_t` value into an `unnormal_t` value
- Function to encode and round_to_nearest_even `ieee754_t` values
  - **encode()** converts an `unnormal_t` value into an `ieee754_t` value, applying rounding as necessary
- Arithmetic functions
  - **add()** adds two `ieee754_t` values
  - **negate()** negates an `ieee754_t` value
  - **subtract()** uses `add()` and `negate()` to subtract an `ieee754_t` value from another (this is a one-line function provided for you)
  - **multiply()** multiplies two `ieee754_t` values
  - **divide()** divides an `ieee754_t` value by another, under a limited set of circumstances

---

|                 |      [⬆️](../README.md)      |               [➡️](02-unnormal_t.md)               |
|:---------------:|:----------------------------:|:--------------------------------------------------:|
|                 | [Front Matter](../README.md) | [`unnormal_t` and Its Functions](02-unnormal_t.md) |
