## Stage 3: Return-Oriented Programming with Integer Argument

> 📇 **Scenario, continued**
>
> As you prepare to launch a buffer overflow attack on the system that controls the herbivore enclosures,
> you notice that the buffer's address changes each time you launch the system.
> Unlike your earlier buffer overflow attacks, you now have to contend with a
> 
> > 🛡️ ***System-Level Protection***
> >
> > The stack has a randomized stack offset.
> 
> "No problem," you think to yourself, and you craft a NOP sled.
> Then you discover another
>
> > 🛡️ ***System-Level Protection***
> >
> > The stack's memory section has been flagged as "no execute".
> 
> Terry Vegian calls from the herbivore wing,
> "The mountain deer are starting to get skittish.
> What's taking so long?"
> 
> You realize that you're going to have to use return-oriented programming to lock the herbivore enclosures.


In stage 3, you want to cause the program to run the `lock_herbivore_enclosures` function.
This function takes one argument, the integer representation of your student ID.
Your task is not only to cause the program to run `lock_herbivore_enclosures`, but also to make it appear to that function as though you called it with the integer version of your student ID as the argument.

In stages 1 & 2, you were able to use any assembly instructions that you wanted to use;
you are now constrained to being able to use only assembly instructions that appear in ROP gadgets.
You will need to craft your attack string as a collection of ROP gadget addresses and data, which you will place on the stack through a buffer overflow.

> 📝 **Grading Note**
>
> We will look for your attack string in `data/stage3.hex`.


### Construct Your Attack

- [ ] Examine the available gadgets.
  You may use the gadgets that we seeded into the program for this assignment,
  and you may use incidental gadgets produced when the program was compiled.
- [ ] Knowing what you have to work with, design your attack.
- [ ] Construct your string so that:
  - There is padding from the start of the stack frame until the return address.
  - The original return address is overwritten with the address of the first gadget.
  - The rest of the string is a series of gadget addresses and any data that you need, concluding with `lock_herbivore_enclosures`'s address.
  - Data and addresses in your attack string are byte-reversed.
- [ ] Save your attack string in `stage3.hex`


### Conduct Your Attack

- [ ] Use the `hex2raw` tool to convert your attack string into raw bytes,
  and use Unix input/output redirection or piping to send those bytes into the target's input stream.

For example:
```shell
build/hex2raw < data/stage3.hex | build/target 3
```

or
```shell
build/hex2raw < data/stage3.hex > data/stage3.raw
build/target 0 < data/stage3.raw
```


---

|                            [⬅️ A64](07-rop-a64.md) <br> [⬅️ x86-64](07-rop-x86-64.md)                            |      [⬆️](../README.md)      |                            [➡️](09-stage4.md)                             |
|:----------------------------------------------------------------------------------------------------------------:|:----------------------------:|:-------------------------------------------------------------------------:|
| [Return-Oriented Programming (A64)](07-rop-a64.md) <br> [Return-Oriented Programming (x86-64)](07-rop-x86-64.md) | [Front Matter](../README.md) | [Stage 4: Return-Oriented Programming with String Argument](09-stage4.md) |
