## Stage 4: Return-Oriented Programming with String Argument

> 📇 **Scenario, continued**
>
> The animals are all safely back in their enclosures.
> Some guests want to leave and, importantly, paying customers want to enter the zoo.
> The zoo's gates were closed and locked as a precaution when the animals got out, and now you need to unlock them.


In stage 4, you want to cause the program to run the `unlock_zoo_gates` function.
This function takes one argument, the string representation of your student ID.
Your task is not only to cause the program to run `unlock_zoo_gates`, but also to make it appear to that function as though you called it with the string version of your student ID as the argument.

As with stage 3, you will need to conduct a return-oriented programming attack.
As with stage 2, you will need to place the string version of your Student ID on the stack and place the string's address into the appropriate register.

> 📝 **Grading Note**
>
> We will look for your attack string in `data/stage4.hex`.


### Construct Your Attack

- [ ] Examine the available gadgets.
  You may use the gadgets that we seeded into the program for this assignment,
  and you may use incidental gadgets produced when the program was compiled.
- [ ] Knowing what you have to work with, design your attack.
- [ ] Construct your string so that:
    - There is padding from the start of the stack frame until the return address.
    - The original return address is overwritten with the address of the first gadget.
    - The rest of the string is a series of gadget addresses and any data that you need -- including the string version of your student ID -- concluding with `unlock_zoo_gates`'s address.
    - Data and addresses in your attack string are byte-reversed.
- [ ] Save your attack string in `stage4.hex`


### Conduct Your Attack

- [ ] Use the `hex2raw` tool to convert your attack string into raw bytes,
  and use Unix input/output redirection or piping to send those bytes into the target's input stream.

For example:
```shell
build/hex2raw < data/stage4.hex | build/target 4
```

or
```shell
build/hex2raw < data/stage4.hex > data/stage4.raw
build/target 0 < data/stage4.raw
```


---

|                             [⬅️](08-stage3.md)                             |      [⬆️](../README.md)      |       [➡️](10-fixing-code.md)        |
|:--------------------------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Stage 3: Return_oriented Programming with Integer Argument](08-stage3.md) | [Front Matter](../README.md) | [Fixing the Code](10-fixing-code.md) |
