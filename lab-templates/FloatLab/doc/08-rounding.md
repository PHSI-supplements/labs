## Rounding

Until now, when a number requires more fraction bits than are available, the program has simply truncated the excess bits when encoding it into an `ieee754_t`;
that is, the numbers have been rounded toward zero.

After you implement `round_to_nearest_even()`, numbers will be rounded toward the nearest representable value, with ties going toward even.

Observe that when your program reaches
```c
/* DETERMINE WHETHER TO ROUND UP OR ROUND DOWN */
```
then:

- `unrounded_number` is the value after truncating the extra fraction bits.
  - Its least significant bit ($bit_{0}$) is the number's *least significant retained bit*.
- `truncated_portion` contains the bits that were cut off, shifted so that:
  - its most significant bit ($bit_{63}$) is the number's *first dropped bit*, and
  - its remaining bits ($bit_{62..0}$) are the number's *trailing dropped bits*.

Apply the rounding rules discussed in class and in the textbook:

- [ ] Determine whether the number should be rounded up or down, setting `should_round_up` accordingly.
- [ ] Add code to round the number up when `should_round_up` is true.

If the number should be rounded down then there is nothing to be done; `unrounded_number` is already the value you would get by rounding down.


#### Check Your Work

- [ ] Check your rounding code by using arithmetic functions.
  - When the rounded-off portion is less than halfway, you always round down
    - <u>`0x40000000 + 0x33FFFFFF`</u>
    - <u>`0x40000001 + 0x33FFFFFF`</u>
  - When the rounded-off portion is more than halfway, you always round up
    - <u>`0x40000000 + 0x34000001`</u>
    - <u>`0x40000001 + 0x34000001`</u>
  - When the rounded-off portion is exactly halfway, you round to even
    - <u>`0x40000000 + 0x34000000`</u>
    - <u>`0x40000001 + 0x34000000`</u>
  - Sometimes rounding can carry all the way to the integer portion, causing the exponent to change
    - <u>`0x407FFFFF + 0x34000000`</u>

---

|            [⬅️](07-add-subtract.md)            |      [⬆️](../README.md)      |                [➡️](09-arbitrary-division.md)                |
|:----------------------------------------------:|:----------------------------:|:------------------------------------------------------------:|
| [Addition and Subtraction](07-add-subtract.md) | [Front Matter](../README.md) | [Bonus Credit: Arbitrary Division](09-arbitrary-division.md) |
