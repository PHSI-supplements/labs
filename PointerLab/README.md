# PointerLab

I generally assign this lab t after KeyboardLab. Aside from the obvious
dependencies (this lab can make use of `decapitalize()` and `is_even()` from
KeyboardLab), I think that the confidence students get from KeyboardLab will
make PointerLab a little less scary. The exception being the small handful of
students who are already comfortable with C -- but in my experience, students
who haven't encountered C before get intimidated by pointers, and even those
who learned C as part of CS1 still aren't entirely comfortable with pointers.
(We can try to alleviate some of this by pointing out that Java references
aren't all that different from C pointers except for the absence of garbage
collection.)

This lab warms up with a couple of code reading problems. The first one doesn't
even involve pointers, but it does involve a difference between C and Java.
Obviously I'm not going to state here what that is, but I will note that Archie
doesn't have the problem with gcc but does with clang, because recent
versions of gcc provide a little more protection for programmers than it used
to (good for programmers, bad for me trying to make a point to my students),
but clang happily continues to deal with this particular piece of undefined
behavior in one of the more straight-forward manners possible.

The second code reading problem does involve pointers, and again recent versions
of gcc provide protection for programmers (though I'm not sure that a
segmentation fault is the right answer) while clang takes the approach of
issuing a warning and assuming that if you don't heed the warning then you must
be doing exactly what you mean to be doing. Indeed, it was the change in the
way that gcc handles this scenario that led me to abandon the old lab assignment
and write the KeyboardLab and PointerLab (that, and while quines are fun, I'm 
not sure they're the best problem to give to students learning C).

Finally, we get to the meat of the lab: creating and traversing a linked list.
The old lab used a singly-linked list and provided all data already sorted
(which, in my mind, doesn't really motivate using a linked list), but much to
my surprise, using a double-linked list and having students complete an
insertion sort as the data is read from a file challenges students enough that
many complain that this is too much for a week-long lab. I disagree, and I've
found that this becomes a useful lesson in not putting work off until the last
minute. Most students get most of the possible points.

The greatest challenge on the grading side is that some students manage to
introduce some nasty memory leaks, far worse than my back-of-the-envelope
calculation suggested was the worst-case scenario. As our sysadmin put it:
"When running `top`, you should never see a 'T' in the 'allocated memory'
column." The autograder is designed to terminate a grading thread that runs
too long, but once the server's virtual memory starts thrashing, the
autograder's core thread doesn't get the CPU time to do that.

The current, unsatisfying solution is to monitor the autograder's resource usage
and kill it when there's runaway code. Set aside the submissions already graded,
set aside the offending submission for manual grading, and restart the
autograder on the remaining submissions. My longer-term solution will be to
rewrite the autograder core to use a different concurrency model so that we can
tell the OS to kill a grading child process once it uses too much memory
(setting the threshold well below the amount of physical memory). I expect this
rewrite to be ready for Spring 2023.
