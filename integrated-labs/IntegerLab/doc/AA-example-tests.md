## Appendix: Example Tests

| Function                   | Example Input                        |
|:---------------------------|:-------------------------------------|
| exponentiate()             | exponentiate 10                      |
| lg()                       | lg 32                                |
| is_negative()              | is_negative 0x2000                   |
| is_negative()              | is_negative 0xA000                   |
| equal()                    | 0x3000 == 0x3000                     |
| equal()                    | 0x3000 == 0x5555                     |
| not_equal()                | 0x3000 != 0x3000                     |
| not_equal()                | 0x3000 != 0x5555                     |
| logical_not()              | !0                                   |
| logical_not()              | !50                                  |
| logical_and()              | 0 && 10 (do the full truth table)    |
| logical_or()               | 0 \|\| 10 (do the full truth table)  |
| one_bit_full_addition()    | add1 0 1 0 (do the full truth table) |
| ripple_carry_addition()    | add32 0x12345678 0x0 0               |
| ripple_carry_addition()    | add32 0x70000000 0xA0000000 0        |
| ripple_carry_addition()    | add32 0x70000000 0x8FFFFFFF 0        |
| ripple_carry_addition()    | add32 0x12345678 0x0FEDCBA9 1        |
| add()                      | 0x1234 + 0x5678                      |
| add()                      | 0xE000 + 0x7000                      |
| add()                      | 0x3000 + 0x7000                      |
| subtract()                 | 0xD000 - 0                           |
| subtract()                 | 0xD000 - 0xD000                      |
| subtract()                 | 0xD000 - 0xA000                      |
| subtract()                 | 0x4000 - 0xD000                      |
| subtract()                 | 0x9000 - 0x5000                      |
| multiply_by_power_of_two() | mul2 15 0x0                          |
| multiply_by_power_of_two() | mul2 15 0x1                          |
| multiply_by_power_of_two() | mul2 15 0x200                        |
| unsigned_multiply()        | 9000 * 3                             |
| unsigned_multiply()        | 30000 * 3                            |
| unsigned_divide()          | 500 / 0                              |
| unsigned_divide()          | 256 / 4                              |
| unsigned_divide()          | 500 / 16                             |
| signed_multiply()          | 30000 * 3                            |
| signed_multiply()          | -25633 * 12                          |
| signed_multiply()          | 9 * -25633                           |
| signed_divide()            | 500 / 16                             |
| signed_divide()            | -24576 / 0x40                        |

---

|         [⬅️](09-grading.md)          |      [⬆️](../README.md)      |                   |
|:------------------------------------:|:----------------------------:|:-----------------:|
| [Turn-In and Grading](09-grading.md) | [Front Matter](../README.md) |                   |
