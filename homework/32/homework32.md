# Homework

This homework lets you explore some real code that deadlocks (or
avoids deadlock). The different versions of code correspond to different
approaches to avoiding deadlock in a simplified vector add() routine.
Specifically:
• vector-deadlock.c: This version of vector add() does not
try to avoid deadlock and thus may indeed do so.
• vector-global-order.c: This version acquires locks in a global
order to avoid deadlock.
• vector-try-wait.c: This version iswilling to release a lockwhen
it senses deadlock might occur.
• vector-avoid-hold-and-wait.c: This version uses a global
lock around lock acquisition to avoid deadlock.
• vector-nolock.c: This version uses an atomic fetch-and-add instead
of locks.
See the README for details on these programs and their common
substrate.

## Questions

First let’s make sure you understand how the programs generally
work, and some of the key options. Study the code in the file called
`vector-deadlock.c`, as well as in `main-common.c` and related
files.
Now, run `./vector-deadlock -n 2 -l 1 -v`, which instantiates
two threads (-n 2), each of which does one vector add (-l 1),
and does so in verbose mode (-v). Make sure you understand the
output. How does the output change from run to run?

1. Now add the -d flag, and change the number of loops (-l) from 1 to
  higher numbers. What happens? Does the code (always) deadlock?
2. How does changing the number of threads (-n) change the outcome
  of the program? Are there any values of -n that ensure no
  deadlock occurs?
3. Now examine the code in vector-global-order.c. First, make
  sure you understand what the code is trying to do; do you understand
  why the code avoids deadlock? Also, why is there a special
  case in this vector add() routine when the source and destination
  vectors are the same?