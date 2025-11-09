## Understand the Starter Code

Before you can fix the code, you need to have an idea of how it works.


### Shared State

```c
volatile char shared_buffer[BUFFER_SIZE] = {0};

volatile enum {
    BUFFER_HAS_DATA, BUFFER_IS_EMPTY, FINISHED
} status = BUFFER_IS_EMPTY;

pthread_mutex_t mutex;
```

We have three global variables.
The `shared_buffer` is exactly what it says it is, an array that is used to pass strings from one thread to another.
The `status` enumerated type is primarily used to communicate whether a new line from the source file has been placed in the shared buffer and whether the contents of the shared buffer have been written to the destination file.
The `mutex` variable is a mutual exclusion token that you will use to eliminate the race condition.

Notice that `shared_buffer` and `status` are qualified with the keyword `volatile`.
Like the `const` qualifier, the `volatile` qualifier is used to provide a hint to the compiler, but it does so for the opposite reason.
A `const` variable should not be modified by the program, allowing the compiler to make optimizations based on that fact.
On the other hand, a `volatile` variable not only can change, it can change spontaneously: the compiler must assume that something will cause the variable to change other than the code that it can see.


### Reading from the Source File

```c
 1. void *read_original(void *arg) {
 2.     FILE *source_file = (FILE *) arg;
 3.     char local_buffer[BUFFER_SIZE];
 4.     bool copying = true;
 5.     while (copying) {
 6.         if (status == BUFFER_IS_EMPTY) {
 7.             status = BUFFER_HAS_DATA;
 8.             if (fgets(local_buffer, BUFFER_SIZE, source_file)) {
 9.                 memcpy((char *) shared_buffer, local_buffer, BUFFER_SIZE);
10.             } else {
11.                 status = FINISHED;
12.                 copying = false;
13.             }
14.         } else {
15.             ;
16.         }
17.     }
18.     return nullptr;
19. }
```

The overall structure of this code is that the loop that starts on line&nbsp;5 will continuously loop until the end of the source file is reached.
In each loop iteration, the value of the `status` enum is checked (line&nbsp;6).
If the `status` indicates that anything that the `read_original()` function previously put in the shared buffer has been copied, then the `status` is changed (line&nbsp;7), and the next line from the source file is read (line&nbsp;8).
If there was no next line, then the program sets the loop's termination condition (line&nbsp;12).
But if there was a line in the file, then that line is copied from a local buffer into the shared buffer on line&nbsp;9.

You probably haven't seen the `memcpy()` function before.
It is very similar to `strncpy()`, except for two differences:
`memcpy()` works on arbitrary memory and not just strings;
and `strncpy()` copies $\min\left(\mathtt{strlen(buffer)},\mathtt{BUFFER\_SIZE}\right)$ bytes, whereas `memcpy` copies exactly $\mathtt{BUFFER\_SIZE}$ bytes.

To give an idea of why declaring the shared variables to be `volatile` is important, view `read_original()` from the compiler's perspective (the compiler typically looks at one function at a time when generating assembly code).
Clearly, `copying` is true the first time that the program reaches line&nbsp;5 so the loop body will execute at least once.
If `status` is not `BUFFER_IS_EMPTY` then the compiler doesn't see any way for that to change, and the compiler would expect that case to result in an infinite, do-nothing loop.
If `status` is `BUFFER_IS_EMPTY`, then `status` will be changed;
depending on how the file read goes, the function will either return or enter into an infinite, do-nothing loop.
If the shared variables are not `volatile`, and if optimizations are enabled, then the compiler is free to turn `read_original()` into this code that it thinks is functionally-equivalent (but isn't when viewed from the big-picture):

```c
void *goto_style_misoptimized_read_original(void *arg) {
    FILE *source_file = (FILE *) arg;
    char local_buffer[BUFFER_SIZE];
    if (status != BUFFER_IS_EMPTY) goto loop;
    if (fgets(local_buffer, BUFFER_SIZE, source_file)) goto update_buffer;
    status = FINISHED;
    return nullptr;
update_buffer:
    status = BUFFER_HAS_DATA;
    memcpy((char *) shared_buffer, local_buffer, BUFFER_SIZE);
loop:
    goto loop;
}
```

Clearly we don't want that to happen, and so we have declared the shared variables to be `volatile`.


### Writing to the Destination File

```c
A. void *write_copy(void *arg) {
B.     FILE *destination_file = (FILE *) arg;
C.     char local_buffer[BUFFER_SIZE];
D.     bool copying = true;
E.     while (copying) {
F.         if (status == BUFFER_HAS_DATA) {
G.             status = BUFFER_IS_EMPTY;
H.             memcpy(local_buffer, (char *) shared_buffer, BUFFER_SIZE);
I.             fputs(local_buffer, destination_file);
J.         } else if (status == FINISHED) {
K.             copying = false;
L.         } else {
M.             ;
N.         }
O.     }
P.     return nullptr;
Q. }
```

Much like `read_original()`, the `write_copy()` function loops until `read_original()` indicates that there are no more lines to be copied on line&nbsp;11;
when this is detected, `write_copy()` sets its loop termination condition on line&nbsp;K.
In each iteration, if `status` indicates that `read_original()` placed a line of text in `shared_buffer` (line&nbsp;F), then `write_copy()` changes `status` (line&nbsp;G).
The function then copies the contents of `shared_buffer` into `local_buffer` (line&nbsp;H) and then writes the contents of `local_buffer` to the destination file on line&nbsp;I.

The shared buffer was a possible bottleneck.
If `read_original()` directly placed the source file's contents into `shared_buffer` and `write_copy()` directly moved `shared_buffer`'s contents into the destination file, then either one function would have to wait for the other to finish its file access, or we'd risk both functions accessing the shared buffer at the same time.
By using local buffers when accessing files, one thread can safely access the shared buffer while the other is accessing a file.


### Thread Management

```c
  i. void duplicate(FILE *source_file, FILE *destination_file) {
 ii.     pthread_t source_thread, destination_thread;
iii.     pthread_create(&source_thread, nullptr, read_original, source_file);
 iv.     pthread_create(&destination_thread, nullptr, write_copy, destination_file);
  v.     pthread_join(source_thread, nullptr);
 vi.     pthread_join(destination_thread, nullptr);
vii. }
```

The `duplicate()` function's job is to launch the reading and writing threads (lines&nbsp; iii–iv) and to prevent the process from terminating by blocking until both threads finish (lines&nbsp;v-vi).
Later you will also use this function to initialize and clean-up the mutual exclusion token.


### Discussion

Clearly the code could have been written differently.
While the code might have been more concise, the more concise forms would have required you to rewrite the code to accommodate the mutual exclusion token.
Instead, we did that for you (except for introducing the mutual exclusion token).
Some very minor re-ordering of a couple of lines of code would decrease the likelihood of a visible error in the output but would not eliminate the race condition.
The ordering of the lines here is intended to maximize the chances of a visible error when using the small files that we provided with the starter code.

> ❗️ **Important**
> 
> As you work on this assignment, do not change any of the existing lines of code, and do not rearrange any of the existing lines of code!

---

|          [⬅️](02-about-duplicator.md)          |      [⬆️](../README.md)      |              [➡️](04-understand-race-condition.md)               |
|:----------------------------------------------:|:----------------------------:|:----------------------------------------------------------------:|
| [About the Duplicator](02-about-duplicator.md) | [Front Matter](../README.md) | [Understand the Race Condition](04-understand-race-condition.md) |
