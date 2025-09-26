## Bonus Credit: Arbitrary Division

It is entirely possible that your implementation of `divide()` handles not only the required case of the dividend's significand being a multiple of the divisor's significand,
but it might also handle *any* pair of operands whose quotient can be exactly represented in the IEEE&nbsp;754 format.

When the quotient cannot be represented exactly, then you are sure that the quotient will need to use the `.fraction` field so that when the quotient is encoded as an `ieee754_t` then the quotient will be as precise as the available bits allow.
If you are going to pursue the arbitrary division bonus, then:

- [ ] <font color="red">First, commit and push your code so that you have backup copy of your work</font>
  - You will be able to revert to your original `divide()` implementation if you need to.
- [ ] Implement `divide()` to work for all pairs of operands, even those whose quotients cannot be represented exactly.

> 💡 **Hint**
> 
> If the bits in the `.integer` field are the result of integer division,
> then the bits in the `.fraction` field are derived from the integer remainder (but are not the remainder itself).

Examples:

- Example that rounds down
  - <u>`1 / 11`</u>
- Example that rounds up
  - <u>`1 / 3`</u>

---

|    [⬅️](08-rounding.md)    |      [⬆️](../README.md)      |         [➡️](10-grading.md)          |
|:--------------------------:|:----------------------------:|:------------------------------------:|
| [Rounding](08-rounding.md) | [Front Matter](../README.md) | [Turn-In and Grading](10-grading.md) |
