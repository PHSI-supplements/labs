# PointerLab

Even though this lab is a "Chapter 1" lab, I recommend that it be assigned to
students *after* KeyboardLab (a "Chapter 2" lab). Aside from the obvious
dependences (this lab makes use of `decapitalize()` and `is_even()` from
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
but clang happily continues with this particular piece of undefined behavior
in the most straight-forward manner possible.

The second code reading problem does involve pointers, and again recent versions
of gcc provide protection for programmers (though I'm not sure that a
segmentation fault is the right answer) while clang takes the approach of
issuing a warning and assuming that if you don't heed the warning then you must
be doing exactly what you mean to be doing. Indeed, it was the change in the
way that gcc handles this scenario that led me to abandon the old lab assignment
and write the lab assignment that became KeyboardLab and PointerLab (that, and
while quines are fun, I'm not sure they're the best problem to give to students
learning C).

Finally we get to the meat of the lab: creating and traversing a linked list.
The old lab used a singly-linked list and provided all data already sorted
(which, in my mind, doesn't really motivate using a linked list), but much to
my surprise, using a double-linked list and having students complete an
insertion sort as the data is read from a file was enough to make this too much
for a single-week's effort. This contributed to me breaking KeyboardLab and
PointerLab into separate assignments and also to me providing partial credit
for a singly-linked list and for no sorting. (If I were to leave KeyboardLab
and PointerLab as a single assignment and try to reduce it to one week, I'd
make the insertion sort and the `previous` pointer bonus credit.)

I don't currently have an autograder for this lab, but that will change soon.
