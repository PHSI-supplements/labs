## Getting Started

> 📇 **Scenario**
>
> All work at the Pleistocene Petting Zoo has stopped while Archie tries to find a ~~gullible~~...
>
> All work at the Pleistocene Petting Zoo has stopped while Archie tries to find a reasonable insurance company.
> Rather than furloughing staff, he's asked everybody to help out with his other startup companies for a week or two.
> He specifically asked that you help out with Eclectic Electronics.
> 
> Herb Bee, the chief engineer, explains that Eclectic Electronics is developing a patent-pending C-licon tool that will convert C code into an integrated circuit that has the same functionality as the original C code.
> To test it out, he tasked you with writing the code to implement an Arithmetic Logic Unit (ALU).
> Your task will be to implement integer addition, subtraction, multiplication, and division.
> Even though high-level languages' *logical* boolean operations normally are not part of an ALU, Herb wants you to include these in the ALU to see if that can make some programs run faster.
> Because bitwise operations and bit shift operations have already been implemented, you will be able to use C's bitwise and bit shift operators,
> but because arithmetic operations have not yet been implemented, you cannot use C's arithmetic operators.
> Because C library functions generally make use of arithmetic operations (which have not yet been implemented), you cannot use library functions.

During your lab period, the TAs will review ripple-carry addition, overflow for unsigned and signed integers, and bitshift-based multiplication and division.
During the remaining time, the TAs will be available to answer questions.

### Configuring the Project

#### From VS Code

If you open *only* the `IntegerLab` directory in VS Code, then VS Code will automatically configure the project.
If instead you open the whole lab repository (so `IntegerLab` is just a subdirectory), then VS Code will *not* configure the `IntegerLab` project automatically.
If autoconfiguration doesn't happen, then open the Command Palette.
From the Command Palette, select `CMake: Select Configure Preset`.
Then select the preset of your choice:

- `default` -- developing on nuros
- `personal-computer` -- developing on your computer

#### From the Command Line

- `cmake --preset default` -- developing on nuros
- `cmake --preset personal-computer` -- developing on your computer

### Suggestion for Loops

Some of the functions in this assignment will require loops that execute a predetermined number of iterations.
The obvious approach, the one that you were surely taught, is to set a loop counter to 0 and then increment the counter until it reaches the desired number of iterations.
Because you cannot use C's arithmetic operations in this assignment, you cannot use this approach until *after* you have implemented addition.

<span style="background-color: yellow;">An alternative that will work within this assignment's constraints is to use bit shifts.</span> <br>
Notice that a 16-bit unsigned integer initially set to 1 will become 0 after it has been left-shifted 16 times.
Similarly, a 32-bit unsigned integer initially set to 1 will become 0 after it has been left-shifted 32 times.
<span style="background-color: yellow;">You might find that this alternative "loop counter" will be a useful bitmask in some of your functions.</span>

<!--
(If you need to iterate an arbitrary number of times, then an unsigned integer initially set to $2^{n-1}$ will become 0 after it has been right-shifted $n$ times, assuming that the integer type you use has at least $n$ bits.
We do not anticipate that you will need to iterate an arbitrary number of times.)
-->

### How the Program will Parse Numbers

When you run the *build/integerlab*, you will be prompted:

```
Enter a one- or two-operand logical expression,
    a two-operand comparison expression, a two-operand arithmetic expression,
    "lg <value>" or "exponentiate <value>" to test your powers-of-two code,
    "is_negative <value>" to determine if 2's complement value is negative,
    "extend <value> <from_size> <to_size>" to zero- and sign-extend a value,
    "add1 <binary_value1> <binary_value2> <carry_in>" for 1-bit full adder,
    "add32 <hex_value1> <hex_value2> <carry_in>" for 32-bit ripple-carry adder,
    "mul2 <hex_value> <hex_power_of_two>" for power-of-two-multiplier,
    or "quit":
```

When you enter a value, if it is prepended with `0x` then the parser will parse it as a hexadecimal value;
otherwise, except as noted in the [sections for the one-bit full adder and the ripple-carry adder](06-adders.md), the parser will treat it as a decimal value.

### Problem Decomposition

#### Logical Operations

The logical operations offer little opportunity for decomposition: determine whether each operand should be interpreted as true or false, and find a way to return the appropriate boolean value.

#### Comparison Operations

Inequality comparison requires that you use a mathematical operation to deduce which operand is greater than the other (this requires arithmetic to be implemented first).
Equality comparison can be decomposed either into using that mathematical operation and deducing that neither operand is greater than the other, or it can be decomposed into determining whether the two operands have the same bit pattern.

#### Arithmetic

Arithmetic, however, is a little more complex.
Before you can add sixteen bit positions, you must be able to add one bit position.
By chaining the carry bits for each bit position, you can add an arbitrary number of bit positions.
You must also be able to detect both signed and unsigned overflow.
Finally, you must be able to use an adder to perform subtraction.

Before you can multiply arbitrary values together, you must be able to multiply a value by a power of two.
You must also be able to add those intermediate products together;
because the multiplicand and multiplier are 16-bit values, you need to be prepared to add 32-bit values as part of this multiplication.

Implementing division requires that you be able to determine whether the divisor is 0 and also that you be able to divide a value by a power of two.

### Descriptions of IntegerLab Files and Data Structures

#### alu.h

Do not edit *alu.h*.

This header file contains three type definitions:

- `one_bit_adder_t` is a structure to hold the 1-bit inputs (`a`, `b`, `c_in`) and 1-bit outputs (`sum`, `c_out`) of a one-bit full adder.
- `alu_result_t` is a structure to hold the outputs from an arithmetic logic unit.
  Its fields are:
  - `result`, a 16-bit bit vector that is considered "the" result of the computation
  - `supplemental_result`, a 16-bit bit vector that stores additional result data from instructions that place their results in two registers
  - `unsigned_overflow`, a 1-bit flag to indicate whether overflow occurred when interpreting the source operands as unsigned values
  - `signed_overflow`, a 1-bit flag to indicate whether overflow occurred when interpreting the source operands as signed values
  - `divide_by_zero`, a 1-bit flag to indicate whether there was an attempt to divide by zero.
- `data_size_t` is an enumerated type to represent data sizes: 8 bits (`ONE_BYTE`), 16 bits (`TWO_BYTES`), and 32 bits (`FOUR_BYTES`).
  Its primary use is to support calls to `zero_extend()` and `sign_extend()`.

The header file also contains four macros, `is_zero()`, `is_not_zero()`, `is_power_of_two()` and `LOWER_BITS_MASK()` to bootstrap your ALU code.
The `is_zero()` and `is_not_zero()` macros act like functions and return a boolean value to indicate whether an integer is 0 or not.
<small>(The astute student will quickly realize that `is_not_zero()` is not necessary and, with a little thought, will realize that they can write `is_zero()` as a function within the constraints of this assignment.)</small>
The `is_power_of_two()` macro checks whether a value is a power of two; it exists primarily to for some precondition checks in the starter code, but you may use it as well.
The `LOWER_BITS_MASK()` macro will generate a bit vector whose lower $n$ bits are 1s and whose remaining bits are 0s
(for example, `LOWER_BITS_MASK(5)` will produce `0x1F`).

Finally, the header file contains eight inequality comparison functions for 16-bit integers that you can use;
however, <font color="red">these functions will *not* work until you have implemented `subtract()`</font>.

|          |          $<$           |        $\leq$        |        $\geq$         |            $>$            |
|:--------:|:----------------------:|:--------------------:|:---------------------:|:-------------------------:|
| unsigned | `unsigned_less_than()` | `unsigned_at_most()` | `unsigned_at_least()` | `unsigned_greater_than()` |
|  signed  |  `signed_less_than()`  |  `signed_at_most()`  |  `signed_at_least()`  |  `signed_greater_than()`  |

#### basetwo.c

This is the first of two files that you will edit.

There are two functions in *basetwo.c* that will allow you to demonstrate an understanding of powers-of-two and/or an understanding of some uses of bit shifts.

- `lg()` returns the base-2 logarithm of its argument, assuming its argument is a positive power-of-two;
  if the argument is 0 or is not a power-of-two, then there are no guarantees about the function's return value
- `exponentiate()` creates a power-of-two by raising 2 to the provided exponent, assuming the exponent is a non-negative value strictly less than 32;
  if the argument is negative or is greater than 31, then there are no guarantees about the function's return value

These functions are inverses of each other: $x = \log_2 2^x \Leftrightarrow y = 2^{\log_2 y}$.

Strictly speaking, you can write your ALU code without these functions;
however, some students in the past had difficulty finding solutions for their ALU code without obtaining a base-2 logarithm and/or calling a function to create a power-of-two.
Rather than tempt you to violate one of the assignment's constraints by calling the *math* library's `log2()`, `exp2()`, and/or `pow()` functions, we now have you write your own code for these functions.

#### alu.c

This file will contain most of the code that you write, and the functions in *alu.c* are in the order in which you will likely write them.
- A simple check
  - `is_negative()` returns a boolean value to indicate whether the argument, when interpreted as a signed integer, is negative 
- Equality comparisons
  - `equal()` returns `true` if and only if $value1 = value2$
  - `not_equal()` returns `true` if and only if $value1 \not = value2$
- Logical operations
  - `logical_not()` returns the logical inverse of the argument
  - `logical_and()` returns the logical conjunction of the two arguments
  - `logical_or()` returns the logical disjunction of the two arguments
- Zero- and sign-extension
  - `zero_extend()` will interpret its `value` argument as an 8- or 16-bit unsigned integer
    and zero-extend the value so that the bit vector returned can be interpreted as a 16- or 32-bit unsigned integer
  - `sign_extend()` will interpret its `value` argument as an 8- or 16-bit signed integer
    and sign-extend the value so that the bit vector returned can be interpreted as a 16- or 32-bit signed integer
- Addition and subtraction
  - `one_bit_full_addition()` performs addition for one bit position, determining both the sum bit and the carry-out bit
  - `ripple_carry_addition()` adds two 32-bit values to each other and to a carry-in bit
  - `add()` adds two 16-bit values to each other
  - `subtract()` subtracts a 16-bit value from another
- Signed Inequality comparisons
  - `less_than()` returns `true` if and only if $value1 < value2$ when these values are signed integers
  - `at_most()` returns `true` if and only if $value1 \leq value2$ when these values are signed integers
  - `at_least()` returns `true` if and only if $value1 \geq value2$ when these values are signed integers
  - `greater_than()` returns `true` if and only if $value1 > value2$ when these values are signed integers
- Unsigned multiplication and division
  - `multiply_by_power_of_two()` multiplies the first argument by the second, assuming that the second argument is zero or a power of two;
    there are no guarantees if this assumption is not satisfied
  - `unsigned_multiply()` multiplies two 16-bit values to each other, if the arguments are interpreted as unsigned integers
  - `unsigned_divide()` divides a 16-bit value by another, if the arguments are interpreted as unsigned integers
- Signed multiplication and division (bonus credit)
  - `signed_multiply()` multiplies two 16-bit values to each other, if the arguments are interpreted as signed integers
  - `signed_divide()` divides a 16-bit value by another, if the arguments are interpreted as signed integers

#### Other files

There are a few other files that serve as driver code and code to help you test your code.
Do not modify these files.

---

|                 |      [⬆️](../README.md)      |        [➡️](02-utility-functions.md)         |
|:---------------:|:----------------------------:|:--------------------------------------------:|
|                 | [Front Matter](../README.md) | [Utility Functions](02-utility-functions.md) |
