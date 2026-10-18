## Stage 2: Code Injection with String Argument

> 📇 **Scenario, continued**
>
> Responding to the call of the dinner bell, the animals are all returning to their enclosures, en route to their feeding pens.
> Watching megafauna salivate, you reflect that someone should have put down a "Caution: **VERY** Wet Floor" sign.
> 
> As you see the last of the carnivores enters its enclosure, you realize that it's time to lock the enclosures so that they don't get out again.

In stage 2, you want to cause the program to run the `lock_carnivore_enclosures` function.
This function takes one argument, the string representation of your student ID.
Your task is not only to cause the program to run `lock_carnivore_enclosures`, but also to make it appear to that function as though you called it with the string version of your student ID as the argument.

Your attack string will include the string version of your student ID, encoded in ASCII, so that the student ID string ends up on the stack.
You will need to craft some assembly code that places the address of the string version of your student ID in the appropriate register.
The machine code corresponding to that assembly code will be part of your attack string.

> 📝 **Grading Note**
>
> We will look for your attack string in `data/stage2.hex`.


### Construct Your Attack

- [ ] Determine where on the stack you want the string version of your student ID to be, and place the ASCII encoding of it in the appropriate spot in your attack string.
- [ ] Write one or more assembly instructions and identify data (if any) & addresses that you need on the stack so that:
  - The 64-bit address of the string version of your student ID will be in the register used for a function's first argument, `x0`.
  - `lock_carnivore_enclosures`'s address in register `x30` (aka, `lr`) so that when the `ret` in your attack code executes, the program will "return" to `lock_carnivore_enclosures`.
  - Your assembly instructions conclude with a `ret` instruction.
- [ ] Determine the bytes for your assembly instructions' machine code
  - Option 1: [Use tools](AA-assemble-disassemble.md)
  - Option 2: [Encode the instructions by hand](BB-A64-encoding.md)
- [ ] Construct your attack string so that:
  - The bytes for your attack code begin at the start of the buffer.
  - There is padding to fill the rest of the stack frame.
  - The original return address with the buffer's address so that the program "returns" to code that you will place in the buffer.
  - The string version of your student ID and other data (if any) that you need on the stack will be where your instructions need it.
  - Instructions, data, and addresses in your attack string are byte-reversed.
  > 0️⃣✅ **Include Leading Zeros, if any**
  >
  > Because the string version of your student ID is an array of characters, the value cannot be misinterpreted as a different number base.
  > This is because it *isn't* being interpreted as a number.
  > The leading 0 is simply the character `0`.
  > You should include all eight digit characters in the string version of your student ID.
  
  > 😖 **Avoid Frustration**
  >
  > If the return address that you need to overwrite is in `caller`'s stack frame (instead of `get_input`'s frame), then
  > - Examine `caller`'s assembly code to note what changes are made to the stack and to the stack pointer.
  >   Do not place data at locations that will be overwritten!
  > - Take the change to `sp` into account when planning data locations and/or offsets from `sp`.
  >   When `caller`'s epilogue deallocates its stack frame, you don't want any important data to be in deallocated memory where the checkpoint function might overwrite it.
- [ ] Save your attack string in `stage2.hex`


### Conduct Your Attack

- [ ] Use the `hex2raw` tool to convert your attack string into raw bytes,
  and use Unix input/output redirection or piping to send those bytes into the target's input stream.

For example:
```shell
build/hex2raw < data/stage2.hex | build/target 2
```

or
```shell
build/hex2raw < data/stage2.hex > data/stage2.raw
build/target 0 < data/stage2.raw
```


---

|                      [⬅️](05-stage1-a64.md)                       |      [⬆️](../README.md)      |             [➡️](07-rop-a64.md)              |
|:-----------------------------------------------------------------:|:----------------------------:|:--------------------------------------------:|
| [Stage 1: Code Injection with Integer Argument](05-stage1-a64.md) | [Front Matter](../README.md) | [Return-Oriented Programming](07-rop-a64.md) |
