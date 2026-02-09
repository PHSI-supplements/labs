## Zero- and Sign-Extension

When casting a value from a larger integer type to a smaller integer type, we simply truncate the excess bits and re-interpret what remains.

When casting a value from a smaller integer type to a larger integer type, we want to preserve its value.
If the original type is unsigned, then we *zero-extend* the value, placing zeroes in the newly-available bits.
(For example, zero-extending `0b1010'1000` from 8 bits to 16 bits gives us `0b0000'0000'1010'1000`.)
If the original type is signed, then we *sign-extend* the value, copying the original most-significant bit into each of the newly-available bits.
(For example, sign-extending `0b1010'1000` from 8 bits to 16 bits gives us `0b1111'1111'1010'1000` because the original most significant bit is `1`,
and sign-extending `0010'1000` to 16 bits gives us `0b0000'0000'0010'1000` because the original most significant bit is `0`.)


### Zero-Extension

In `zero_extend()`, you will interpret the `value` argument as though it is an 8-, 16-, or 32-bit unsigned value, depending on what `from_size` is.
That is, the only bits you care about are the lower 8, 16, or 32.
You will zero-extend it to become an 8-, 16-, or 32-bit unsigned value, depending on what `to_size` is,
according to these rules ($variable_{x..y}$ refers to a range of bits in the `variable`'s bit vector):

| $from\_size$ |  $to\_size$  | |      $result_{31..16}$       |      $result_{15..8}$       |      $result_{7..0}$       |
|:------------:|:------------:|-|:----------------------------:|:---------------------------:|:--------------------------:|
|  `ONE_BYTE`  |  `ONE_BYTE`  | | $value_{31..16}$ (unchanged) | $value_{15..8}$ (unchanged) | $value_{7..0}$ (unchanged) |
|  `ONE_BYTE`  | `TWO_BYTES`  | | $value_{31..16}$ (unchanged) |              0              | $value_{7..0}$ (unchanged) |
|  `ONE_BYTE`  | `FOUR_BYTES` | |              0               |              0              | $value_{7..0}$ (unchanged) |
| `TWO_BYTES`  | `TWO_BYTES`  | | $value_{31..16}$ (unchanged) | $value_{15..8}$ (unchanged) | $value_{7..0}$ (unchanged) |
| `TWO_BYTES`  | `FOUR_BYTES` | |              0               | $value_{15..8}$ (unchanged) | $value_{7..0}$ (unchanged) |
| `FOUR_BYTES` | `FOUR_BYTES` | | $value_{31..16}$ (unchanged) | $value_{15..8}$ (unchanged) | $value_{7..0}$ (unchanged) |

You do not need to handle the case of `to_size` being less than `from_size`.
You do not need to handle the cases of `to_size` or `from_size` being values other than those shown in the table.

- [ ] Implement `zero_extend()` to zero-extend the input value from its original size up to but not exceeding its new size.


### Sign-Extension

In `sign_extend()`, you will interpret the `value` argument as though it is an 8-, 16-, or 32-bit signed value, depending on what `from_size` is.
That is, the only bits you care about are the lower 8, 16, or 32.
You will zero-extend it to become an 8-, 16-, or 32-bit signed value, depending on what `to_size` is,
according to these rules ($variable_{x..y}$ refers to a range of bits in the `variable`'s bit vector):

| $from\_size$ |  $to\_size$  | |         $result_{31..16}$          |        $result_{15..8}$        |      $result_{7..0}$       |
|:------------:|:------------:|-|:----------------------------------:|:------------------------------:|:--------------------------:|
|  `ONE_BYTE`  |  `ONE_BYTE`  | |    $value_{31..16}$ (unchanged)    |  $value_{15..8}$ (unchanged)   | $value_{7..0}$ (unchanged) |
|  `ONE_BYTE`  | `TWO_BYTES`  | |    $value_{31..16}$ (unchanged)    | $value_7$ (duplicated 8 times) | $value_{7..0}$ (unchanged) |
|  `ONE_BYTE`  | `FOUR_BYTES` | |  $value_7$ (duplicated 16 times)   | $value_7$ (duplicated 8 times) | $value_{7..0}$ (unchanged) |
| `TWO_BYTES`  | `TWO_BYTES`  | |    $value_{31..16}$ (unchanged)    |  $value_{15..8}$ (unchanged)   | $value_{7..0}$ (unchanged) |
| `TWO_BYTES`  | `FOUR_BYTES` | | $value_{15}$ (duplicated 16 times) |  $value_{15..8}$ (unchanged)   | $value_{7..0}$ (unchanged) |
| `FOUR_BYTES` | `FOUR_BYTES` | |    $value_{31..16}$ (unchanged)    |  $value_{15..8}$ (unchanged)   | $value_{7..0}$ (unchanged) |

You do not need to handle the case of `to_size` being less than `from_size`.
You do not need to handle the cases of `to_size` or `from_size` being values other than those shown in the table.

- [ ] Implement `sign_extend()` to sign-extend the input value from its original size up to but not exceeding its new size.


### Check your work

- [ ] Compile and run *integerlab*, trying a few values.

For example:

```
Enter ... "extend <value> <from_size> <to_size>" ...: extend 0x12345678 8 16
Bit vector: 0x12345678
Unsigned: initial 8-bit value:         120
	Expected 16-bit value:         120 (0x12340078)	Actual 16-bit value:         120 (0x12340078)
Signed: initial 8-bit value:           120
	Expected 16-bit value:         120 (0x12340078)	Actual 16-bit value:         120 (0x12340078)

Enter ... "extend <value> <from_size> <to_size>" ...: extend 0xABCDEF90 ONE_BYTE TWO_BYTES
Bit vector: 0xabcdef90
Unsigned: initial 8-bit value:         144
	Expected 16-bit value:         144 (0xabcd0090)	Actual 16-bit value:         144 (0xabcd0090)
Signed: initial 8-bit value:          -112
	Expected 16-bit value:        -112 (0xabcdff90)	Actual 16-bit value:        -112 (0xabcdff90)

Enter ... "extend <value> <from_size> <to_size>" ...: extend 0xABCDEF98 16 32
Bit vector: 0xabcdef98
Unsigned: initial 16-bit value:       61336
	Expected 32-bit value:       61336 (0x0000ef98)	Actual 32-bit value:       61336 (0x0000ef98)
Signed: initial 16-bit value:         -4200
	Expected 32-bit value:       -4200 (0xffffef98)	Actual 32-bit value:       -4200 (0xffffef98)
```

- [ ] Check your code with other values, comparing your actual results with the expected results.
- [ ] Run the constraint checker: `ctest --test-dir build --output-on-failure`

---

|         [⬅️](04-logical-operations.md)         |      [⬆️](../README.md)      |        [➡️](06-adders.md)        |
|:----------------------------------------------:|:----------------------------:|:--------------------------------:|
| [Logical Operations](04-logical-operations.md) | [Front Matter](../README.md) | [Adder "Hardware"](06-adders.md) |
