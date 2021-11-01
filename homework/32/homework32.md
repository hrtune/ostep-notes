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

1, First let’s make sure you understand how the programs generally
work, and some of the key options. Study the code in the file called
`vector-deadlock.c`, as well as in `main-common.c` and related
files.
Now, run `./vector-deadlock -n 2 -l 1 -v`, which instantiates
two threads (-n 2), each of which does one vector add (-l 1),
and does so in verbose mode (-v). Make sure you understand the
output. How does the output change from run to run?

```
->add(0, 1)
<-add(0, 1)
              ->add(0, 1)
              <-add(0, 1)
// '->' means calling the function
// '<-' means returned from the function
```

2, Now add the `-d` flag, and change the number of loops (-l) from 1 to
higher numbers. What happens? Does the code (always) deadlock?

| Loop(s) | Deadlock? (with over 10,000 attempts) |
| ------- | ------------------------------------- |
| 1       | No                                    |
| 2       | No                                    |
| 5       | Yes (on the 6690th attempt)           |
| 10      | Yes (on the 3690th attempt)           |
| 20      | Yes (on the 72nd attempt)             |
| 100     | Yes (on the 150th attempt)            |

3, How does changing the number of threads (-n) change the outcome
of the program? Are there any values of -n that ensure no
deadlock occurs?

> -n 1 (no concurrency)

4, Now examine the code in `vector-global-order.c`. First, make
sure you understand what the code is trying to do; 

- Do you understand why the code avoids deadlock? 

  > Because the arguments of vector_add() can be only two of '&v[v0]' and '&[v1]', ordering by pointer number always makes the code avoid deadlock.

- Also, why is there a special
  case in this vector add() routine when the source and destination
  vectors are the same?

  > A thread can not hold two identical locks.

5, Now run the code with the following flags: `-t -n 2 -l 100000 -d`. How long does the code take to complete? 

```
$ ./vector-global-order -t -n 2 -l 100000 -d
Time: 0.04 seconds
```

- How does the total time change when you increase the number of loops, or the number
  of threads?

  - When increasing the number of loops:  the time proportinally increases.

  - When increasing the number of threads: 

    ![image1](C:\Users\Sakiharu\Documents\GitHub\ostep-notes\homework\32\f32-1.jpg)

What happens if you turn on the parallelism flag (-p)? How much
would you expect performance to change when each thread is working
on adding different vectors (which is what -p enables) versus
working on the same ones?

```
./vector-global-order -t -n 2 -l 1000000
Time: 1.08 seconds

./vector-global-order -t -n 2 -l 1000000 -p
Time: 0.16 seconds
```

> Racing to hold the same lock causes the delay.

Now let’s study `vector-try-wait.c`. First make sure you understand
the code. Is the first call to `pthread-mutex-trylock()` really needed?

Now run the code. How fast does it run compared to the global
order approach? How does the number of retries, as counted by
the code, change as the number of threads increases?

```
./vector-global-order -t -n 2 -l 1000000
Time: 1.12 seconds

./vector-try-wait -t -n 2 -l 1000000
Retries: 
Time: 0.59 seconds
```

| Number of threads | Retries (on 1,000,000 loops) |
| ----------------- | ---------------------------- |
| 2                 | 101886                       |
| 3                 | 167499                       |
| 4                 | 235407                       |
| 5                 | 643721                       |

> Because of racing the same lock(s) by threads.

Now let’s look at `vector-avoid-hold-and-wait.c`. What is
the main problem with this approach? How does its performance
compare to the other versions, when running both with -p and
without it?

```
./vector-avoid-hold-and-wait -t -n 2 -l 1000000
Time: 1.25 seconds
```

> It seems to be even worse than ./vector-global-order.

| Lock type (with two threads, million times loops) | Time (seconds) | Time (with -p) |
| ------------------------------------------------- | -------------- | -------------- |
| ./vector-global-order                             | 1.11           | 0.15           |
| ./vector-try-wait                                 | 0.60           | 0.15           |
| ./vector-avoid-hold-and-wait                      | 1.23           | 0.39           |
| ./vector-nolock                                   | 1.38           | 0.67           |

Finally, let’s look at `vector-nolock.c`. This version doesn’t use
locks at all; does it provide the exact same semantics as the other
versions? Why or why not?

> Yes, because the fetch_and_add() is implemented by one atomic operation.

Now compare its performance to the other versions, both when
threads are working on the same two vectors (no -p) and when
each thread is working on separate vectors (-p). How does this
no-lock version perform?

> It performs the worst in time.
>
> cf. https://stackoverflow.com/questions/9601427/is-inline-assembly-language-slower-than-native-c-code