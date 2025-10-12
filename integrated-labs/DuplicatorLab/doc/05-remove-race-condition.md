## Remove the Race Condition

You will eliminate the race condition by using the `mutex` mutual exclusion token.

### Initialize and Destroy the Mutex

Before using a mutual exclusion token, you must first initialize it.

- [ ] Use `pthread_mutex_init()` to initialize the `mutex` mutual exclusion token.
  - We recommend that you do so in the `duplicate()` function, using the default attribute, before any threads are created.
    The syntax is in [Chapter&nbsp;8](https://unl.grlcontent.com/compeng2e/page/chapter8) and [Appendix&nbsp;C](https://unl.grlcontent.com/compeng2e/page/appendixc#c18) of the textbook.

As a matter of good code hygiene, you should destroy a mutual exclusion token when it is no longer required.

- [ ] Use `pthread_mutex_destroy()` to release the `mutex` mutual exclusion token's resources.
  - We recommend that you do so in the `duplicate()` function after all threads have been joined.
    The syntax is in [Chapter&nbsp;8](https://unl.grlcontent.com/compeng2e/page/chapter8) and [Appendix&nbsp;C](https://unl.grlcontent.com/compeng2e/page/appendixc#c18) of the textbook.


### Determine Where to Lock and Unlock the Mutex

Recall from Chapter&nbsp;8 that if a thread tries to lock a mutual exclusion token and the mutex is already locked, then the thread will *block* until another thread unlocks the mutex.
You want to use the mutex to ensure that if a thread is accessing the shared state then no other threads can access the shared state.
You also want to make sure that no thread blocks indefinitely.

Suppose we were to lock the mutex between lines&nbsp;4 and 5, and between lines&nbsp;D and E, while unlocking the mutex immediately before each function returns.
Then one of the threads is certain to starve.
For example:

```text
               B
               C
               D
               (mutex locked)
               E   (write_copy enters loop)
     2
     3
     4
     (read_original blocked for mutex)
               F   (buffer is empty)
               J   (buffer is empty)
               M
               E
               F   (buffer is empty)
               J   (buffer is empty)
               M
               E
               *et cetera*
```

    
- [ ] Think about where locking and unlocking the mutual exclusion token would prevent undesirable interleavings while still allowing desirable interleavings to occur.
  Make sure that it would not prevent the functionally-correct interleaving shown earlier.
- [ ] In *answers.txt*, identify where in the original code the mutex should be locked and unlocked, using the line numbers from [the section about understanding the code](03-understanding-code.md).
- [ ] In *answers.txt*, make a copy of the interleaving you provided for your answer to the first question and paste it into the space for your answer to the fourth question.
- [ ] Introduce "(mutex locked)", "(mutex unlocked)", "(read_original blocked for mutex)", and "(write_copy blocked for mutex)" wherever appropriate to the interleaving in your fourth answer,
  up to the point that a thread getting blocked will prevent the buffer containing "second line" from being overwritten prematurely.
  - You can delete the remaining portion of your interleaving in your fourth answer that occurs after that.
        
    
### Lock and Unlock the Mutex in the Code
    
- [ ] Add calls to `pthread_mutex_lock()` and `pthread_mutex_unlock()`, as appropriate, in `read_original()` and `write_copy()` to lock and unlock the mutex.
  - These locations should correspond to your answers to the second and third questions in *answers.txt*.
    The syntax is in [Chapter&nbsp;8](https://unl.grlcontent.com/compeng2e/page/chapter8) and [Appendix&nbsp;C](https://unl.grlcontent.com/compeng2e/page/appendixc#c18) of the textbook.
  
- [ ] Test your code!
  - [ ] Run this command a dozen times to make sure the file is copied correctly:
    ```shell
    build/duplicator data/threelines.txt copy.txt; cat copy.txt
    ```
  - [ ] Then try this command several times:
    ```shell
    build/duplicator data/paleolama.txt copy.txt; cat copy.txt
    ```

If you find that you are not producing identical copies of the originals, or if the program never terminates, then revisit [your lock/unlock placement](#determine-where-to-lock-and-unlock-the-mutex).

You can test with larger files, using `diff` instead of `cat` to check for differences.
(If `diff` produces no output, then there is no difference between the files.)
For example:
```shell
build/duplicator src/duplicator.c copy.c; diff src/duplicator.c copy.c
```
or:
```shell
build/duplicator data/answers.txt copy.txt; diff data/answers.txt copy.txt
```

---

|              [⬅️](04-understand-race-condition.md)               |      [⬆️](../README.md)      |         [➡️](06-grading.md)          |
|:----------------------------------------------------------------:|:----------------------------:|:------------------------------------:|
| [Understand the Race Condition](04-understand-race-condition.md) | [Front Matter](../README.md) | [Turn-In and Grading](06-grading.md) |
