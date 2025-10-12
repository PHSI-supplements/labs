## About the Duplicator

When you build the project, you will get an executable file called *duplicator*.
The *duplicator* executable is supposed to make a copy of a text file.
Unfortunately, it doesn't quite work right.

The *duplicator* executable takes two command-line arguments, first the name of the file to be copied, and then the name of the new file that will be a copy of the first.
(This is not a replacement for the UNIX *cp* command;
even after you get it working correctly, *duplicator* will not accurately copy non-text files.[^1]
We designed *duplicator* specifically for text files so that it's easier for you to see when it doesn't work right.)

[^1] *duplicator* probably shouldn't be used to copy prehistoric animals' DNA, either.


For example, running the program with the command 
```shell
build/duplicator data/paleolama.txt copy.txt
```
will create a new file, *copy.txt* that is almost -- but not quite -- a copy of *paleolama.txt*.
As a shortcut, you can run the command
```shell
build/duplicator data/paleolama.txt copy.txt; cat copy.txt
````
to display the contents of *copy.txt* after creating it.
For reference, here are the contents of the original file:

```text
% cat paleolama.txt
  (\__/)
(o '' )
   \  \
    \  \
     \  ____________
     |              |\\
     |__  _________ |
     || ||      || ||
     || ||      || ||
```
    
Here is one possible result:

```text
% build/duplicator data/paleolama.txt copy.txt; cat copy.txt
  (\__/)
   \  \
   \  \
    \  \
     \  ____________
     |              |\\
     |__  _________ |
     || ||      || ||
     || ||      || ||
```

Here is another:

```text
% build/duplicator data/paleolama.txt copy.txt; cat copy.txt
(o '' )
(o '' )
(o '' )
   \  \
    \  \
     \  ____________
     |__  _________ |
     |__  _________ |
     || ||      || ||
     || ||      || ||
```

Clearly, neither of these outputs are accurate copies of the original file.
The problem is that there is a **race condition** in *duplicator.c*.

> 🎯 **Your Goal**
> 
> After you have finished this assignment, you will have removed the race condition, and the command
> ```shell
> build/duplicator data/paleolama.txt copy.txt
> ```
> will create *copy.txt* that is a perfect copy of *paleolama.txt*.

---

|       [⬅️](01-getting-started.md)        |      [⬆️](../README.md)      |             [➡️](03-understanding-code.md)              |
|:----------------------------------------:|:----------------------------:|:-------------------------------------------------------:|
| [Getting Started](01-getting-started.md) | [Front Matter](../README.md) | [Understand the Starter Code](03-understanding-code.md) |
