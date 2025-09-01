## Appendix A: Differences and Similarities between Java and C that are Relevant to this Assignment

In some regards, Java keeps things simple: every variable is a reference, except when it isn't.
In other regards, C keeps things simple: you always know whether the variable you're using is a value or a pointer.

### Comparing Strings

You probably learned that when comparing Java strings, using the equality operator `==` is error-prone.
When comparing two `String` literals (or variables assigned to `String` literals), the equality operator usually acts as a naive programmer would expect:
`"abc" == "abc"` evaluates to `true`.
When one or both of the Strings are generated at runtime, such as from user input, then the equality operator rarely evaluates to `true`:
`userInput == "abc"` will evaluate to `false` even when the user entered "abc".

The reason for this is that when comparing objects (other than boxed types), Java's comparators compare the objects' references;
that is, Java comparators compare the objects' memory addresses.
Using the `==` operator to compare strings evaluates to `true` only when the two strings occupy the same address;
that is, they are both literally the same `String` object.
This is why you were taught to use Java's `String.equals()` method to compare strings.

Comparing C strings' variables has the same pitfall:
because the string variables are pointers to the first character in their respective strings, using arithmetic comparators will compare the strings' addresses.
If you want to compare two C strings, you would use the `strcmp()`\footnote{See footnote~\ref{note:stringFunctions}.} function.
The wrinkle is that `strcmp()` returns `0` (*i.e.*, `false`) when the two strings are equal;
you will often see the idiom `if (!strcmp(string1, string2)) {`.

The `strcmp(string1, string2)` function actually performs a lexicographic comparison of the strings, returning a negative value if `string1` occurs alphabetically earlier than `string2`, zero if every character in the two strings match, and a positive value if `string1` occurs alphabetically later than `string2`.
In this regard, C's `strcmp()` function is more like Java's `String.compareTo()` method than `String.equals()`.

### Copying Strings

Because Java Strings are immutable objects, you can safely copy a string by simply copying its reference (this is called *aliasing*).
You can safely write the statement `string1 = string2;` without worrying about changes to `string2` causing changes in `string1`
(if you were to make changes to `string2`, it would result in a new String object being assigned to the `string2` variable).

For mutable objects, creating an alias (that is, copying the reference) results in the situation that changes made through one variable are visible through the other variable.
For example, if you have Java the statements `list1 = list2; list2.add(foo);` then `list1.size() == list2.size() && list1.contains(foo)` will evaluate to `true`.
If the object's class implements the `Cloneable` interface then you can make a copy of an object without aliasing it.
If you have the statements `list1 = list2.clone(); list2.add(foo);` then `list1.size() == list2.size()` will evaluate to `false`.

In general, C strings are mutable.\footnote{
The exceptions are string literals, which are immutable, and strings declared as a pointer to a constant, which if treated as mutable will result in undefined behavior.
}
This means that you generally don't want to create an alias.\footnote{
Sometimes you can't create an alias.
If the left-hand-side of an assignment is a constant pointer or is effectively a constant pointer -- such as an array inside a struct -- then it cannot be re-assigned.
}
Instead, use the `strcpy(destination, source)` or `strncpy(destination, source, n)`\footnote{See footnote~\ref{note:stringFunctions}.} function to copy the `source` string into the memory pointed to by `destination`.
The `strcpy()` function will continue copying until encountering the terminating `NUL` in the `source` string -- this is very slightly faster (not enough that you'd notice) but is safe only if you can prove that `destination` has enough memory allocated for the string.
The `strncpy()` function will copy until encountering the terminating `NUL` or until it has copied $n-1$ characters (after which it will append a terminating `NUL`) -- this is safer because you can ensure that the string copied to `destination` will fit within the space allocated for it.

### Allocating and Deallocating Memory

Java's `new` keyword allocates space for the new object, inferring the amount of space needed based on the class's definition.
In C, you use the `malloc()` function to allocate space\footnote{
There are a small handful of alternate functions, each with their own use cases, but `malloc()` is most-suitable for this lab.
}, and you must be explicit about how much space you need.
An idiom is to combine `malloc()` with the `sizeof()` function, as you saw in PokerLab, and as you'll see near the start of Section~\ref{subsubsec:cImplementation}.

Java uses a *garbage collector* to reclaim memory allocated for objects that are no longer in use.
The unpredictability of when garbage collection happens makes an automatic garbage collector unsuitable for many of C's uses.
For this reason (among others), the programmer is responsible for deallocating memory that is no longer needed.
This is done with the `free()` function.

While a variable will go out of scope at the end of the code block in which it was declared, memory allocated in that code block persists unless explicitly `free`d.
Once the last pointer pointing to that memory goes out of scope, you no longer have a way to `free` that memory, resulting in a *memory leak*.
On the other hand, `free`ing memory while it is still being used by another pointer can result in undefined behavior.
This requires careful thought to make sure that you `free` all memory that you allocated, but only after it is safe to do so.

For many short-running programs, such as those you often write in school, you often can ignore the need to `free` allocated memory since all the program's memory will be reclaimed by the operating system when the program terminates.
A member of the C Standard Committee recently described this as having a maid that will clean up your mess.\footnote{
Sarcasm alert: \url{https://twitter.com/__phantomderp/status/1619322783162568705}, \\ \url{https://twitter.com/__phantomderp/status/1619323139665846273}
}

I advise you not to rely on that "maid" even for a "short-running program," such as this one.
In an earlier version of this lab, there were a dozen or so students whose code, when tested against a 75,000-word file, would quickly consume all the server's physical memory.
As the first of these programs thrashed the virtual memory system, it prevented other services from working effectively, including the one that I had precautionarily introduced to kill a test after a couple of minutes.
It consumed enough resources that the system administrator couldn't log in to determine why the server had slowed to a crawl.
As I was already logged in, I was able to kill the process as the system administrator was preparing to disconnect the server from the power line.
The system administrator later commented about the resources it consumed, '`You ought never to see a `T' in the memory column'' (Figure~\ref{fig:tooMuchMemoryUsed}).

\center
\includegraphics{too-much-memory-used}
\caption{Screenshot showing a student's program consuming 0.022 terabytes of physical memory;
the allocated virtual memory is not visible in the image.\label{fig:tooMuchMemoryUsed}}


### Declaration vs Definition

In C, types, variables, and functions must be *declared* earlier in the file (or in an `#include`d file) than their first use;
however, they typically do not need to be *defined* until later.
A declaration provides establishes the existence and scope, and it provides enough information for the compiler to check for mismatches.
For example, a function "prototype" commonly found in header files simply provides the name of a function and its signature.
You can have arbitrarily many declarations for the same entity as long as they don't conflict with each other.

A definition, on the other hand, provides all the details.
(A definition is also implicitly a declaration.)
For example, a function's definition has all of its code.
An entity can only have one definition within its scope.
Functions, for example, typically have global scope, and so you cannot have multiple functions with the same name, even if they're in different files.

You are more likely, by far, to see function declarations that are not definitions than you are to see anything else declared without a definition.
In a future lab, you'll see an example of a variable declaration that has its definition in a separate file.

In this lab, we have an example of a type declaration that occurs separately from its definition.
In *list.h.*, we declare a `struct list_definition` type (and `typedef` it to `list_t`) without a definition.
Because none of the function prototypes in *list.h* need to know anything about `list_t` other than its existence, and because none of the code in *challenge-response.c* depends on the definition, you are able to write code for the challenge-response system without regard to the underlying representation.
We provide a definition of `struct list_definition` in *array_list.h* and another definition in *linked_list.h*.
We crafted the Makefile so that when you build *arraylistlab*, only the definition in *array_list.h* is included;
similarly, when you build *linkedlistlab*, only the definition in *linked_list.h* is included.
In doing so, we ensure that each executable has only one definition of `struct list_definition`.

Note that the code in *linked_list.c* does depend on `struct list_definition`'s definition, but that's okay because *linked_list.c* `#include`s *linked_list.h*.

### The `static` Keyword

In Java, the `static` keyword is used to make a field or method be shared among all instances of a class, and even be available without having an instance of the class.
The C programming language doesn't have classes, so clearly `static` cannot mean the same thing.

In C, `static` can be used in two different ways.
In a future lab, we'll see the use of `static` for function-scoped variables.
In this lab, we have two functions in *linked_list.c* that are modified with the `static` keyword.

When function or variable that is declared outside of any function is modified with the `static` keyword, it no longer has global scope;
instead, its scope is limited to the file.
You can think of it as roughly corresponding to Java's `private` visibility modifier.
This has two implications:
- A file-scoped function or variable cannot be accessed from code in another file
- Another file-scoped function or variable of the same name can be defined in another file without violating the rule against multiple definitions

---

|   [⬅️](13-grading.md)    |      [⬆️](../README.md)      |           [➡️](BB-data-structure.md)            |
|:------------------------:|:----------------------------:|:-----------------------------------------------:|
| [Grading](13-grading.md) | [Front Matter](../README.md) | [Appendix B: Linked List](BB-data-structure.md) |
