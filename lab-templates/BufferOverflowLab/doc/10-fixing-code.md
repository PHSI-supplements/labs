## Fixing the Code

> 📇 **Scenario, continued**
>
> Everything seems to have been set right.
> You have a suspicion that if this disaster were to have happened seven months from now,
> that you'd have a couple more functions to execute and would have to contend with a
> 
> > 🛡️ ***Compiler-Level Protection***
> >
> > A stack canary would detect a buffer overflow when the buffer is on the stack.
> 
> Fortunately (?) that protection is not in place.
> 
> Now that you think about it, you were able to save the day only because the software had a buffer overflow vulnerability.
> While you were able to take advantage of that, 
> it would probably be a good idea to remove security vulnerabilities from the software that controls the Pleistocene Petting Zoo's safety systems. 


### 🛡️ Programmer-Level Protection

If we ignore the code in `get_input` that acts as instrumentation and optional guardrails for this assignment,
`get_input` boils down to this code:

```c
size_t get_input(void) {
    char buffer[BUFFER_SIZE];
    printf("\nSYSTEM READY > ");
    gets(buffer);
    printf("\n\n");
    return get_input_size();
}
```

What change can you make to this function to prevent a buffer overflow? 

- [ ] Open the [BufferOverflowLab Fixing the Code](https://canvas.unl.edu/courses/209782/assignments/2287658) quiz in Canvas.
- [ ] Place your answer in the Canvas quiz.


---

|                            [⬅️](09-stage4.md)                             |      [⬆️](../README.md)      |      [➡️](11-bonus.md)      |
|:-------------------------------------------------------------------------:|:----------------------------:|:---------------------------:|
| [Stage 4: Return-Oriented Programming with String Argument](09-stage4.md) | [Front Matter](../README.md) | [Bonus Credit](11-bonus.md) |
