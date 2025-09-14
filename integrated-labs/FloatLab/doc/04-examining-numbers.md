## Examining IEEE 754-Compliant Values

### TL;DR

- [ ] Implement `get_754_integer()` to produce the implicit integer portion of the significand.
- [ ] Implement `get_754_fraction()` to return the fraction bits exactly as they appear in the `number`.
- [ ] Implement `get_754_exponent()` to produce the two's complement representation of the exponent that you get after removing the bias from the `number`'s `E` field.
- [ ] Compile and run *floatlab*, trying a few values, starting with values whose IEEE 754 representation are easy to check.
- [ ] Create some bit vectors to see that the sign, significand, and exponent are all what you expect, based on your understanding of the IEEE&nbsp;754 format.
  - Don't forget to check subnormal numbers, too.


- [ ] Assign the appropriate value to `fraction` in the `decode()` function, such that the $2^{-1}$ bit is in `fraction`'s $bit_{63}$.
- [ ] Compile and run *floatlab*, decoding a few values  (example usage: <u>`decode 12.375`</u>).}


### Extracting the Integer, Fraction, and Exponent

There are three functions that extract the components of a value's magnitude.
These three functions all assume that the value is a finite number:
the value might be a normal number;
it might be a subnormal number;
it might be zero.

- [ ] Implement `get_754_integer()` to produce the implicit integer portion of the significand.
- [ ] Implement `get_754_fraction()` to return the fraction bits exactly as they appear in the `number`.
- [ ] Implement `get_754_exponent()` to produce the two's complement representation of the exponent that you get after removing the bias from the `number`'s `E` field.

You will use `ieee754_to_string()` to test your code.

#### Check Your Work

- [ ] Compile and run *floatlab*, trying a few values, starting with values whose IEEE 754 representation are easy to check.

For example:
```
Enter a value, a two-operand arithmetic expression,
    "decode <value>", "recode <value>",
    or "quit": 1
0x3f800000	+1.0000,0000,0000,0000,0000,000_{2} x 2^{0}

Enter a value, ... or "quit": .25
0x3e800000	+1.0000,0000,0000,0000,0000,000_{2} x 2^{-2}

Enter a value, ... or "quit": 15.625
0x417a0000	+1.1111,0100,0000,0000,0000,000_{2} x 2^{3}
```

- [ ] Try a few more on your own.
- [ ] Create some bit vectors to see that the sign, significand, and exponent are all what you expect, based on your understanding of the IEEE&nbsp;754 format.

For example:
```
Enter a value, ... or "quit": 0xF22AAAAA
0xf22aaaaa	-1.0101,0101,0101,0101,0101,010_{2} x 2^{101}
```

Don't forget to check subnormal numbers, too.
For example:
```
Enter a value, ... or "quit": 5e-40
0x000571cc	+0.0000,1010,1110,0011,1001,100_{2} x 2^{-126}
```


### Decoding Numbers from the IEEE 754 Format into `unnormal_t`

The `decode()` function converts an IEEE&nbsp;754-compliant `ieee754_t` value into a format that facilitates arithmetic.
As described [earlier](02-unnormal_t.md), the `unnormal_t` structure that is returned by `decode()` has fields for the sign bit, the integer portion, the fractional portion, and the exponent.
It also has flags for Not-a-Number and for Infinity.
Unlike the IEEE&nbsp;754 format, an `unnormal_t` value can have more than one bit in its integer portion.

You have already done most of the work to populate an `unnormal_t` structure.
In `decode()` you will need to left-shift the `fraction` returned by `get_754_fraction()` by several places such that the $2^{-1}$ bit is in $bit_{63}$ (the most-significant bit) of an `uint64_t` bit vector, the $2^{-2}$ bit is in $bit_{62}$, and so on.
This is because the `unnormal()` function call expects the `.fraction` named field to be the numerator of
$$\frac{\mathtt{.fraction}\ argument}{2^{64}}$$

#### A Visualization

Envision the 64 bits in the `.integer` field and the 64 bits in the `.fraction` field:
$$ i_{63} i_{62} i_{61} i_{60} \cdots i_3 i_2 i_1 i_0\ \mathbf{.} \ f_{63} f_{62} f_{61} f_{60} \cdots f_3 f_2 f_1 f_0 $$

If we have the number $1\frac{3}{4}$, and if we were to place the `ieee754_t`'s fraction bits directly into the `unnormal_t`'s `.fraction` field, then we would have:
$$ 0\mathrm{b}\ 0000 \cdots 0001\ \mathbf{.} \ 0000 \cdots 0110'0000 \cdots 0000 $$
giving us the value $1\frac{3 \times 2^{21}}{2^{64}} = 1\frac{3}{2^{43}}$, which not what we want.
On the other hand, if we were to shift the fraction bits by $(64 - NUMBER\_OF\_FRACTION\_BITS)$ places, then we would have:
$$ 0\mathrm{b}\ 0000 \cdots 0001\ \mathbf{.} \ 1100 \cdots 0000 $$
giving us the value $1\frac{3 \times 2^{62}}{2^{64}} = 1\frac{3}{2^2} = 1\frac{3}{4}$.

This is why the fraction bits need to be shifted so that the bit corresponding to the $2^{-1}$ place is in $bit_{63}$.

#### Examples

Suppose that the number is $68588.0_{10} = 1.0000'1011'1110'11_{2} \times 2^{16}$.
In the IEEE&nbsp;754 normal form, this is 0x4785'F600 = 0b0<u>100'0111'1</u>000'0101'1111'0110'0000'0000 (we have underlined the $E$ field to help you follow the discussion).

In the `unnormal_t` data structure, the `.integer` is 1, the `.exponent` is 16, and the `.fraction` is 0x0BEC'0000'0000'0000.
Mathematically, that is the `.fraction` field because the fraction field needs to be the numerator of
$$ \frac{BEC'0000'0000'0000_{16}}{1'0000'0000'0000'0000_{16}} $$
That is why you need to left-shift the `fraction` by several places (so that the $2^{-1}$ bit is in the most-significant bit) before passing it to the `unnormal()` function.

To see this from a practical perspective, let us consider some of the functions defined for `unnormal_t`.
In these examples, assume that all numbers are stored in `unnormal_t` data structures.

- **shift_left_once($1.0000'1011'1110'11_{2} \times 2^{16}$)** will return a *copy* of the original `unnormal_t` data structure, except that the significand's bits have been left-shifted by one, and the fraction has been decreased by one;
  specifically, it will return \
  $10.0001'0111'1101'1_{2} \times 2^{15}$.
  (The original data structure will be unchanged.)
- **shift_right($10.0001'0111'1101'1_{2} \times 2^{15}$, 4)** will return \
  $0.0010'0001'0111'1101'1_{2} \times 2^{19}$:
  the significand's bits have been right-shifted by four, and the fraction has increased by four.
- **place_all_bits_in_integer($0.0010'0001'0111,1101'1_{2} \times 2^{19}$)** will return \
  $100'0010'1111'1011.0_{2} \times 2^{2}$.
- **set_exponent($100'0010'1111'1011.0_{2} \times 2^{2}$, 0)** will return \
  $1,0000'1011'1110'1100.0_{2} \times 2^{0}$.
- **set_integer($1'0000'1011'1110'1100.0_{2} \times 2^{0}$, 1)** will return \
  $1.0000'1011'1110'11_{2} \times 2^{16}$.

#### Decoding Numbers

The `integer` and `exponent` variables can obtain their correct values directly from the `get_754_integer()` and `get_754_exponent()` functions.
The `fraction` variable, however, needs to shift the value obtained from `get_754_fraction()`.

- [ ] Assign the appropriate value to `fraction` in the `decode()` function.
  - Because the value obtained from `get_754_fraction()` has the fraction bits in the `NUMBER_OF_FRACTION_BITS` least-significant bits,
    and because the most significant bit is $bit_{63}$, placing the $2^{-1}$ bit in the most significant bit can be accomplished by shifting the fraction bits by $(64 - NUMBER\_OF\_FRACTION\_BITS)$ places.
    
#### Check Your Work 

- [ ] Compile and run *floatlab*, decoding a few values.

We have provided a function that will print a `unnormal_t` value.
When you run *floatlab*, you can specify that you want to decode a value, such as <u>`decode 12.375`</u>.
The program will then print the value, based on the `unnormal_t` fields.
Because there are 64 bits available for the integer portion and another 64 bits for the fractional portion, the `unnormal_t` value will be printed in base-16:
```
Enter a value, a two-operand arithmetic expression,
    "decode <value>", "recode <value>",
    or "quit": decode 12.375
+0000000000000001.8c00000000000000_{16} x 2^{3}
```
Because $12.375_{10} = 1.1000'11_{2} \times 2^3$, we can see that $1.8\mathrm{C}_{16} \times 2^3$ is correct.

- [ ] Try some other numbers that you can easily convert to base-two by hand, and see if your `decode()` function correctly unpacks their IEEE&nbsp;754 representation and correctly sets the `unnormal_t` fields.

---

|          [⬅️](03-constants-queries.md)           |      [⬆️](../../IntegerLab/README.md)      |                    [➡️](05-normalization.md)                     |
|:------------------------------------------------:|:------------------------------------------:|:----------------------------------------------------------------:|
| [Constants and Queries](03-constants-queries.md) | [Front Matter](../../IntegerLab/README.md) | [Encoding Numbers into the IEEE 754 Format](05-normalization.md) |
