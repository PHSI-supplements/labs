## About `ThreadSanitizer`

`ThreadSanitizer` is a data race detector for C and C++ code that is packaged as part of the GCC and sa part of Clang.
You can read more about it here:
- https://github.com/google/sanitizers/wiki/ThreadSanitizerCppManual
- https://clang.llvm.org/docs/ThreadSanitizer.html

You wouldn't want to include `ThreadSanitizer` as part of a production build:
it uses a lot of memory, it causes the program to run slowly, and it can have undesirable interactions with a process's memory allocation upper limit.

But for testing?
Absolutely.
(If your development environment doesn't experience that memory allocation upper limit problem.
There's a reason that we didn't use ThreadSanitizer when students completed the lab assignments on nuros.)

If `ThreadSanitizer` finds a race condition, it provides diagnostic information to help you identify the cause.
Let us look at the diagnostics generated when we run the starter code.
(After you've finished the [previous task](04-understand-race-condition.md#your-task-show-that-an-incorrect-output-is-possible), nothing here should surprise you.)

Here we present four warnings; we'll group them based on which variable is subject to the race, which wasn't the order that they were presented to us.
You may see additional warnings, or you may see fewer.
`ThreadSanitizer` isn't a static analyzer;
it instruments code and checks memory accesses during execution.
If a memory access doesn't occur during execution, then `ThreadSanitizer` won't report issues for that access.


### Race for `status`

These two warnings are caused by a data race detected for the `status` variable.
Both warnings state "Location is global 'status' of size 4 at 0xaaaaaaac0010 (duplicator+0x20010)" (the address may be different for you).


#### Write after write

This warning identifies two writes to `status`: one on line 46 and another on line 73.

Both threads modify the same variable, but there is no synchronization that establishes which write must happen first.
This is a *write-after-write* data race.
Even though each write stores a complete integer value, the absence of synchronization makes the program's behavior undefined.

```text
==================
WARNING: ThreadSanitizer: data race (pid=102)
  Write of size 4 at 0xaaaaaaac0010 by thread T1:
    #0 read_original /csce231/DuplicatorLab/src/duplicator.c:46 (duplicator+0xf10) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Previous write of size 4 at 0xaaaaaaac0010 by thread T2:
    #0 write_copy /csce231/DuplicatorLab/src/duplicator.c:73 (duplicator+0x1024) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Location is global 'status' of size 4 at 0xaaaaaaac0010 (duplicator+0x20010)

  Thread T1 (tid=104, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:93 (duplicator+0x1158) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Thread T2 (tid=105, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:94 (duplicator+0x1174) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

SUMMARY: ThreadSanitizer: data race /csce231/DuplicatorLab/src/duplicator.c:46 in read_original
==================
```

This next warning is similar to the previous one, except there's a different pair of writes that were used to detect the race condition.

```text
==================
WARNING: ThreadSanitizer: data race (pid=102)
  Write of size 4 at 0xaaaaaaac0010 by thread T1:
    #0 read_original /csce231/DuplicatorLab/src/duplicator.c:50 (duplicator+0xf98) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Previous write of size 4 at 0xaaaaaaac0010 by thread T2:
    #0 write_copy /csce231/DuplicatorLab/src/duplicator.c:73 (duplicator+0x1024) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Location is global 'status' of size 4 at 0xaaaaaaac0010 (duplicator+0x20010)

  Thread T1 (tid=104, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:93 (duplicator+0x1158) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Thread T2 (tid=105, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:94 (duplicator+0x1174) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

SUMMARY: ThreadSanitizer: data race /csce231/DuplicatorLab/src/duplicator.c:50 in read_original
==================
```


#### Read after write

This warning identifies a read of `status` on line 72 and a write to `status` on line 46.

Because the threads access the same variable without synchronization, there is no guarantee that the reader will observe the value written by the other thread. 
This is a read-after-write data race.

```text
=================
WARNING: ThreadSanitizer: data race (pid=102)
  Read of size 4 at 0xaaaaaaac0010 by thread T2:
    #0 write_copy /csce231/DuplicatorLab/src/duplicator.c:72 (duplicator+0x10a4) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Previous write of size 4 at 0xaaaaaaac0010 by thread T1:
    #0 read_original /csce231/DuplicatorLab/src/duplicator.c:46 (duplicator+0xf10) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Location is global 'status' of size 4 at 0xaaaaaaac0010 (duplicator+0x20010)

  Thread T2 (tid=105, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:94 (duplicator+0x1174) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Thread T1 (tid=104, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:93 (duplicator+0x1158) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

SUMMARY: ThreadSanitizer: data race /csce231/DuplicatorLab/src/duplicator.c:72 in write_copy
==================
```

What about reading `status` on line 45 after it being written on line 73?

That would also constitute a data race. 
However, `ThreadSanitizer` doesn't need to report every data race that occurs during an execution.
It maintains only a limited history of memory accesses and suppresses reports that appear to be redundant.
There is already sufficient evidence that accesses to `status` are not properly synchronized.


### Race for `shared_buffer`

This warning points us to code that reads from `shared_buffer` on line 74 after it had been written to on line 48:
a read-after-write scenario.
While the detection seems to happen in the `memcpy()` library function, `ThreadSanitizer` helpfully unwinds the call chain to identify the relevant code in *duplicator.c*. 

```text
==================
WARNING: ThreadSanitizer: data race (pid=102)
  Read of size 8 at 0xaaaaaaac0020 by thread T2:
    #0 memcpy /usr/include/aarch64-linux-gnu/bits/string_fortified.h:29 (duplicator+0x104c) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #1 write_copy /csce231/DuplicatorLab/src/duplicator.c:74 (duplicator+0x104c)

  Previous write of size 8 at 0xaaaaaaac0020 by thread T1:
    #0 memcpy /usr/include/aarch64-linux-gnu/bits/string_fortified.h:29 (duplicator+0xf3c) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #1 read_original /csce231/DuplicatorLab/src/duplicator.c:48 (duplicator+0xf3c)

  Location is global 'shared_buffer' of size 120 at 0xaaaaaaac0020 (duplicator+0x20020)

  Thread T2 (tid=105, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:94 (duplicator+0x1174) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

  Thread T1 (tid=104, running) created by main thread at:
    #0 pthread_create ../../../../src/libsanitizer/tsan/tsan_interceptors_posix.cpp:1078 (libtsan.so.2+0x5e83c) (BuildId: 92f14145646a32a217effb45501763763addc1
bd)
    #1 duplicate /csce231/DuplicatorLab/src/duplicator.c:93 (duplicator+0x1158) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)
    #2 main /csce231/DuplicatorLab/src/duplicatorlab.c:37 (duplicator+0xe14) (BuildId: 3c0c394bc9efe3b1d080fda39c404ba2b84fc789)

SUMMARY: ThreadSanitizer: data race /usr/include/aarch64-linux-gnu/bits/string_fortified.h:29 in memcpy
==================
```

---

|              [⬅️](04-understand-race-condition.md)               |      [⬆️](../README.md)      |            [➡️](06-remove-race-condition.md)             |
|:----------------------------------------------------------------:|:----------------------------:|:--------------------------------------------------------:|
| [Understand the Race Condition](04-understand-race-condition.md) | [Front Matter](../README.md) | [Remove the Race Condition](06-remove-race-condition.md) |

