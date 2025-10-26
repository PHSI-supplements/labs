## Appendix C: Variable Modifiers

C has some keywords that can be used to modify variables.
In some cases, these keywords define scoping rules;
in other cases, these keywords provide information to the compiler that it can use when optimizing the resulting assembly code.

#### const

[Textbook Appendix C, "Variables that Don't, and Constants that Aren't"](https://unl.grlcontent.com/compeng2e/page/appendixc#c7)

In ListLab, you encountered the `const` keyword.
When used as part of an ordinary variable declaration, it prevents the variable from being modified after it has been initialized.
(Much to some peoples' surprise, this does not actually make it a constant as far as C's syntax rules are concerned.)

When used with a pointer, the `const` keyword tells the compiler that it can make optimizations under the assumption that whatever the pointer points to will not change.
Code that breaks this promise will have compile-time warnings, but it will compile and run -- but it often will have runtime errors.
(There is another way to use `const` with a pointer that declares the pointer itself to be unchanging.)

#### volatile

[Textbook Appendix C, "Variables that Don't, and Constants that Aren't"](https://unl.grlcontent.com/compeng2e/page/appendixc#c7)

In DuplicatorLab, you encountered the `volatile` keyword.
A `volatile` variable is the opposite of a `const` variable:
not only can it change, it can spontaneously change.
The `volatile` keyword tells the compiler that it cannot optimize-away a variable that is never written to.
It also tells the compiler that it cannot optimize-away a variable that is never read.

With threaded code such as what you saw in DuplicatorLab, it's tempting to believe that a sufficiently thorough static analysis of the code will reveal that a variable is being written to and/or read from multiple threads.
When working with memory-mapped input/output registers in this lab, you will read from variables that do not have a single line of code *anywhere* changing their values, and yet their values will change.
Similarly, you will write to variables that do not have a single line of code anywhere that reads from them, and yet it is important that those variables be updated.

#### extern

[Textbook Appendix C, "Declarations and Definitions, revisited"](https://unl.grlcontent.com/compeng2e/page/appendixc#c10)

When present, you will typically see externalized variables declared in header files, though they can be declared in a `.c` file, and even in a function body.
When a variable is *declared* with the `extern` modifier, it does not *define* a new variable.
Instead, it allows code in one `.c` file to access global variables that are defined in another `.c` file.
That is, it makes a global variable even more global.

#### static

[Textbook Appendix C, "Static Does Not Mean What You Think It Means"](https://unl.grlcontent.com/compeng2e/page/appendixc#c9)

The other modifier you will see in this lab is the `static` keyword.
If you've programmed in Java, beware that C's `static` keyword is not the same as Java's `static` keyword.\footnote{
    Nor can it be.
    Java's `static` keyword declares a field to belong to the whole class;
    C does not have classes.
}

<u>**Static global variables**</u>

When used with a global variable, the `static` keyword limits that variable's scope to code to the `.c` file it's defined in (or to the `.c` file that `#include`s the `.h` file it's defined in).
This allows other code in *other* files to have static global variables with the same name without a naming collision.
That is, it makes a global variable a little less global.

Similarly, the `static` keyword can limit a function's scope.

<u>**Static local variables**</u>

When used with a scope-limited variable, such as a variable declared in a function, the `static` modifier causes the variable to be something of a hybrid variable.
Unlike a normal function-local variable, which is allocated on the program stack, these `static` variables are allocated on the heap.
When a function returns, normal function-local variables are deallocated because the function's stack frame is popped.
A `static` variable, however, is *not* deallocated when its function returns.
That means that its last value is still available the next time that the function is called.
A `static` variable used in this way looks like a global variable -- its value is preserved between function calls -- but it is still scope-limited to the function it's declared in.

You can see examples of `static` variables in the I/O test code.

You should explicitly initialize a `static` variable on the same line that it is declared.
Such an initializer must be a compile-time constant.
The variable will only be initialized once; it will *not* be reinitialized each time the function is called.
(If it were reinitialized, that would rather defeat the point of the variable preserving its value between function calls, right?)
If you do not explicitly initialize the variable then, unlike ordinary function-local variables, a `static` variable will automatically be initialized to 0.

---

|              [⬅️](BB-datasheet-links.md)               |      [⬆️](../README.md)      |                         |
|:------------------------------------------------------:|:----------------------------:|:-----------------------:|
| [Links to the Cow Pi Datasheet](BB-datasheet-links.md) | [Front Matter](../README.md) |                         |
