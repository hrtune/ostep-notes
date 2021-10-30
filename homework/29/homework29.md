# Homework (Code)

In this homework, you’ll gain some experience with writing concurrent
code and measuring its performance. Learning to build high-performance
code is a critical skill and thus gaining a little experience here with it is
quite worthwhile.

### Questions

We’ll start by redoing the measurements within this chapter. Use
the call gettimeofday() to measure time within your program.
How accurate is this timer? What is the smallest interval it can measure?
Gain confidence in its workings, as we will need it in all subsequent
questions. You can also look into other timers, such as the
cycle counter available on x86 via the rdtsc instruction.

Now, build a simple concurrent counter and measure how long it
takes to increment the counter many times as the number of threads
increases. How many CPUs are available on the system you are
using? Does this number impact your measurements at all?

```
$ ./concurrent-counter 1 (<- number of thread)
counter value: 100
delay time is: 76 (us)
$ ./concurrent-counter 2
counter value: 200
delay time is: 62 (us)
$ ./concurrent-counter 3
counter value: 300
delay time is: 47 (us)
$ ./concurrent-counter 4
counter value: 400
delay time is: 41 (us)
$ ./concurrent-counter 5
counter value: 500
delay time is: 45 (us)
$ ./concurrent-counter 6
counter value: 600
delay time is: 42 (us)
```

> My processor on which I measured delay time has 4 cores in it.
>
> Thus, setting a number of thread to more than of 4 is not effective for performance here. (as I expected.)

Next, build a version of the sloppy counter. Once again,measure its
performance as the number of threads varies, as well as the threshold.
Do the numbers match what you see in the chapter?

| Threshold ↓\ Thread(s) → | 1     | 2     | 3     | 4     |
| ------------------------ | ----- | ----- | ----- | ----- |
| 1                        | 0.048 | 0.16  | 0.126 | 0.141 |
| 5                        | 0.031 | 0.09  | 0.078 | 0.095 |
| 10                       | 0.028 | 0.09  | 0.076 | 0.089 |
| 20                       | 0.028 | 0.085 | 0.073 | 0.088 |

> 1.2 million counts in seconds

Build a version of a linked list that uses hand-over-hand locking
[MS04], as cited in the chapter. You should read the paper first
to understand how it works, and then implement it. Measure its
performance. When does a hand-over-hand list work better than a
standard list as shown in the chapter?



Pick your favorite interesting data structure, such as a B-tree or
other slightly more interested structure. Implement it, and start
with a simple locking strategy such as a single lock. Measure its
performance as the number of concurrent threads increases.

Finally, think of a more interesting locking strategy for this favorite
data structure of yours. Implement it, and measure its performance.
How does it compare to the straightforward locking approach?