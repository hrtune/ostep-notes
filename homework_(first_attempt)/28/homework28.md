# Homework

This program, x86.py, allows you to see how different thread interleavings
either cause or avoid race conditions. See the README for details
on how the program works and its basic inputs, then answer the
questions below.
Questions

First let’s get ready to run x86.py with the flag -p flag.s. This
code “implements” locking with a single memory flag. Can you
understand what the assembly code is trying to do?

```
(flag.s)
.var flag
.var count

.main
.top

.acquire
mov  flag, %ax      # get flag
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again
mov  $1, flag       # store 1 into flag

# critical section
mov  count, %ax     # get the value at the address
add  $1, %ax        # increment it
mov  %ax, count     # store it back

# release lock
mov  $0, flag       # clear the flag now

# see if we're still looping
sub  $1, %bx
test $0, %bx
jgt .top	

halt


```

When you run with the defaults, does flag.s work as expected?
Does it produce the correct result? Use the -M and -R flags to trace
variables and registers (and turn on -c to see their values). Can you
predict what value will end up in flag as the code runs?

```
$ python3 x86.py -p flag.s -M flag -R ax,bx -c
 flag      ax    bx          Thread 0                Thread 1

    0       0     0
    0       0     0   1000 mov  flag, %ax
    0       0     0   1001 test $0, %ax
    0       0     0   1002 jne  .acquire
    1       0     0   1003 mov  $1, flag
    1       0     0   1004 mov  count, %ax
    1       1     0   1005 add  $1, %ax
    1       1     0   1006 mov  %ax, count
    0       1     0   1007 mov  $0, flag
    0       1    -1   1008 sub  $1, %bx
    0       1    -1   1009 test $0, %bx
    0       1    -1   1010 jgt .top
    0       1    -1   1011 halt
    0       0     0   ----- Halt;Switch -----  ----- Halt;Switch -----
    0       0     0                            1000 mov  flag, %ax
    0       0     0                            1001 test $0, %ax
    0       0     0                            1002 jne  .acquire
    1       0     0                            1003 mov  $1, flag
    1       1     0                            1004 mov  count, %ax
    1       2     0                            1005 add  $1, %ax
    1       2     0                            1006 mov  %ax, count
    0       2     0                            1007 mov  $0, flag
    0       2    -1                            1008 sub  $1, %bx
    0       2    -1                            1009 test $0, %bx
    0       2    -1                            1010 jgt .top
    0       2    -1                            1011 halt
```

> Yes.

Change the value of the register %bx with the -a flag (e.g., -a
bx=2,bx=2 if you are running just two threads). What does the
code do? How does it change your answer for the question above?

```
$ python3 x86.py -p flag.s -M flag,count -R ax,bx -a bx=2,bx=2 -c
 flag count      ax    bx          Thread 0                Thread 1

    0     0       0     2
    0     0       0     2   1000 mov  flag, %ax
    0     0       0     2   1001 test $0, %ax
    0     0       0     2   1002 jne  .acquire
    1     0       0     2   1003 mov  $1, flag
    1     0       0     2   1004 mov  count, %ax
    1     0       1     2   1005 add  $1, %ax
    1     1       1     2   1006 mov  %ax, count
    0     1       1     2   1007 mov  $0, flag
    0     1       1     1   1008 sub  $1, %bx
    0     1       1     1   1009 test $0, %bx
    0     1       1     1   1010 jgt .top
    0     1       0     1   1000 mov  flag, %ax
    0     1       0     1   1001 test $0, %ax
    0     1       0     1   1002 jne  .acquire
    1     1       0     1   1003 mov  $1, flag
    1     1       1     1   1004 mov  count, %ax
    1     1       2     1   1005 add  $1, %ax
    1     2       2     1   1006 mov  %ax, count
    0     2       2     1   1007 mov  $0, flag
    0     2       2     0   1008 sub  $1, %bx
    0     2       2     0   1009 test $0, %bx
    0     2       2     0   1010 jgt .top
    0     2       2     0   1011 halt
    0     2       0     2   ----- Halt;Switch -----  ----- Halt;Switch -----
    0     2       0     2                            1000 mov  flag, %ax
    0     2       0     2                            1001 test $0, %ax
    0     2       0     2                            1002 jne  .acquire
    1     2       0     2                            1003 mov  $1, flag
    1     2       2     2                            1004 mov  count, %ax
    1     2       3     2                            1005 add  $1, %ax
    1     3       3     2                            1006 mov  %ax, count
    0     3       3     2                            1007 mov  $0, flag
    0     3       3     1                            1008 sub  $1, %bx
    0     3       3     1                            1009 test $0, %bx
    0     3       3     1                            1010 jgt .top
    0     3       0     1                            1000 mov  flag, %ax
    0     3       0     1                            1001 test $0, %ax
    0     3       0     1                            1002 jne  .acquire
    1     3       0     1                            1003 mov  $1, flag
    1     3       3     1                            1004 mov  count, %ax
    1     3       4     1                            1005 add  $1, %ax
    1     4       4     1                            1006 mov  %ax, count
    0     4       4     1                            1007 mov  $0, flag
    0     4       4     0                            1008 sub  $1, %bx
    0     4       4     0                            1009 test $0, %bx
    0     4       4     0                            1010 jgt .top
    0     4       4     0                            1011 halt
```

Set bx to a high value for each thread, and then use the -i flag to
generate different interrupt frequencies; what values lead to a bad
outcomes? Which lead to good outcomes?

>The value 'count' should be bx * 2 as the number of threads is 2.

```
(-a bx=100,bx=100 -i 3)
	0   133   ----- Halt;Switch -----  ----- Halt;Switch -----
    0   133   ------ Interrupt ------  ------ Interrupt ------
    0   133                            1009 test $0, %bx
    0   133                            1010 jgt .top
    0   133                            1011 halt
// ended up with 133 rather than 200 because...

	0     0   1000 mov  flag, %ax
    0     0   1001 test $0, %ax
    0     0   1002 jne  .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------
    0     0                            1000 mov  flag, %ax
    0     0                            1001 test $0, %ax
    0     0                            1002 jne  .acquire
    0     0   ------ Interrupt ------  ------ Interrupt ------
    1     0   1003 mov  $1, flag
    1     0   1004 mov  count, %ax
// the thread 1 is holding the flag but the flag value was not updated when the interrupt ocurrs thus the thread 2 also could enter the critical section.
```

```
(-i 11)
    0   199   ------ Interrupt ------  ------ Interrupt ------
    0   199                            1000 mov  flag, %ax
    0   199                            1001 test $0, %ax
    0   199                            1002 jne  .acquire
    1   199                            1003 mov  $1, flag
    1   199                            1004 mov  count, %ax
    1   199                            1005 add  $1, %ax
    1   200                            1006 mov  %ax, count
    0   200                            1007 mov  $0, flag
    0   200                            1008 sub  $1, %bx
    0   200                            1009 test $0, %bx
    0   200                            1010 jgt .top
    0   200   ------ Interrupt ------  ------ Interrupt ------
    0   200   1011 halt
    0   200   ----- Halt;Switch -----  ----- Halt;Switch -----
    0   200                            1011 halt
    
    // setting the -i value to multiples of 11 is okay because the whole main loop consists of 11 lines (from 1000 to 1010)
```

Now let’s look at the program test-and-set.s. First, try to understand
the code, which uses the xchg instruction to build a simple
locking primitive. How is the lock acquire written? How about
lock release?

```
.var mutex
.var count

.main
.top

.acquire
mov  $1, %ax
xchg %ax, mutex     # atomic swap of 1 and mutex
test $0, %ax        # if we get 0 back: lock is free!
jne  .acquire       # if not, try again

# critical section
mov  count, %ax     # get the value at the address
add  $1, %ax        # increment it
mov  %ax, count     # store it back

# release lock
mov  $0, mutex

# see if we're still looping
sub  $1, %bx
test $0, %bx
jgt .top

halt
```

> 'xchg' does getting a flag value and setting a new flag value in one line.
>
> Releasing a lock is just to set 0 to the flag(mutex)

Now run the code, changing the value of the interrupt interval (-i)
again, and making sure to loop for a number of times. Does the
code always work as expected? Does it sometimes lead to an inefficient
use of the CPU? How could you quantify that?

> Yes, the code always works as expected.

Use the -P flag to generate specific tests of the locking code. For
example, run a schedule that grabs the lock in the first thread, but
then tries to acquire it in the second. Does the right thing happen?
What else should you test?

> It does right.

Now let’s look at the code in peterson.s, which implements Peterson’s
algorithm (mentioned in a sidebar in the text). Study the
code and see if you can make sense of it.

```
# array of 2 integers (each size 4 bytes)
# load address of flag into fx register
# access flag[] with 0(%fx,%index,4)
# where %index is a register holding 0 or 1
# index reg contains 0 -> flag[0], if 1->flag[1]
.var flag   2     

# global turn variable
.var turn

# global count
.var count

.main

# put address of flag into fx
lea flag, %fx

# assume thread ID is in bx (0 or 1, scale by 4 to get proper flag address)
mov %bx, %cx   # bx: self, now copies to cx
neg %cx        # cx: - self
add $1, %cx    # cx: 1 - self

.acquire
mov $1, 0(%fx,%bx,4)    # flag[self] = 1
mov %cx, turn           # turn       = 1 - self

.spin1
mov 0(%fx,%cx,4), %ax   # flag[1-self]
test $1, %ax            
jne .fini               # if flag[1-self] != 1, skip past loop to .fini

.spin2                  # just labeled for fun, not needed
mov turn, %ax
test %cx, %ax           # compare 'turn' and '1 - self'
je .spin1               # if turn==1-self, go back and start spin again

# fall out of spin
.fini

# do critical section now
mov count, %ax
add $1, %ax
mov %ax, count

.release
mov $0, 0(%fx,%bx,4)    # flag[self] = 0


# end case: make sure it's other's turn
mov %cx, turn           # turn       = 1 - self
halt


```

Now run the code with different values of -i. What kinds of different
behavior do you see? Make sure to set the thread IDs appropriately
(using -a bx=0,bx=1 for example) as the code assumes
it.

> At least either of flags will be 1 on the first 'test' statement.
>
> The turn will be either 1 or 0.
>
> So, even if both of the flags is 0, still either of two threads can go to the critical section.