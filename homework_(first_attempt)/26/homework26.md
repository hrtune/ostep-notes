# Homework 26

This program, x86.py, allows you to see how different thread inter-leavings
either cause or avoid race conditions. See the README for details
on how the program works and its basic inputs, then answer the
questions below.

### Questions

1 To start, let’s examine a simple program, “loop.s”. First, just look at the program, and see if you can understand it: cat loop.s. 

```
$ cat loop.s
.main
.top
sub  $1,%dx
test $0,%dx
jgte .top
halt

in C...
//
while(1){
	dx--;
	if(dx >= 0){
		continue; // jump to the top of this loop
	}
	else{
		break;
	}
}
return 0; // halt

```

Then, run it with these arguments: ./x86.py -p loop.s -t 1 -i 100 -R dx
This specifies a single thread, an interrupt every 100 instructions,
and tracing of register %dx. Can you figure out what the value of
%dx will be during the run? Once you have, run the same above
and use the -c flag to check your answers; note the answers, on
the left, show the value of the register (or memory value) after the
instruction on the right has run.

```
$ python3 x86.py -p loop.s -t 1 -i 100 -R dx
...
// my answer here.
   dx          Thread 0
    0
    -1   1000 sub  $1,%dx
    -1  1001 test $0,%dx
    -1   1002 jgte .top
    -1   1003 halt

```

Now run the same code but with these flags:
./x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx
This specifies two threads, and initializes each %dx register to 3.
What values will %dx see? Run with the -c flag to see the answers.
Does the presence of multiple threads affect anything about your
calculations? Is there a race condition in this code?

```
$ python3 x86.py -p loop.s -t 2 -i 100 -a dx=3,dx=3 -R dx
...

   dx          Thread 0                Thread 1
    3
    2   1000 sub  $1,%dx
    2   1001 test $0,%dx
    2   1002 jgte .top
    1   1000 sub  $1,%dx
    1   1001 test $0,%dx
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    0   1001 test $0,%dx
    0   1002 jgte .top
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   1003 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    1                            1000 sub  $1,%dx
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0                            1000 sub  $1,%dx
    0                            1001 test $0,%dx
    0                            1002 jgte .top
   -1                            1000 sub  $1,%dx
   -1                            1001 test $0,%dx
   -1                            1002 jgte .top
   -1                            1003 halt
```

Now run the following:
./x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx
This makes the interrupt interval quite small and random; use different
seeds with -s to see different interleavings. Does the frequency
of interruption change anything about this program?

```
$ python3 x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx
...

   dx          Thread 0                Thread 1
    3
    2   1000 sub  $1,%dx
    2   1001 test $0,%dx
    2   1002 jgte .top
    3   ------ Interrupt ------  ------ Interrupt ------
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    2   ------ Interrupt ------  ------ Interrupt ------
    1   1000 sub  $1,%dx
    1   1001 test $0,%dx
    2   ------ Interrupt ------  ------ Interrupt ------
    1                            1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1002 jgte .top
    0   1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    0   ------ Interrupt ------  ------ Interrupt ------
    0   1001 test $0,%dx
    0   1002 jgte .top
   -1   1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------
    0                            1000 sub  $1,%dx
   -1   ------ Interrupt ------  ------ Interrupt ------
   -1   1001 test $0,%dx
   -1   1002 jgte .top
    0   ------ Interrupt ------  ------ Interrupt ------
    0                            1001 test $0,%dx
    0                            1002 jgte .top
   -1   ------ Interrupt ------  ------ Interrupt ------
   -1   1003 halt
    0   ----- Halt;Switch -----  ----- Halt;Switch -----
   -1                            1000 sub  $1,%dx
   -1                            1001 test $0,%dx
   -1   ------ Interrupt ------  ------ Interrupt ------
   -1                            1002 jgte .top
   -1                            1003 halt
   
$ python3 x86.py -p loop.s -t 2 -i 3 -r -a dx=3,dx=3 -R dx -s 1
...

   dx          Thread 0                Thread 1
    3
    2   1000 sub  $1,%dx
    3   ------ Interrupt ------  ------ Interrupt ------
    2                            1000 sub  $1,%dx
    2                            1001 test $0,%dx
    2                            1002 jgte .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1001 test $0,%dx
    2   1002 jgte .top
    1   1000 sub  $1,%dx
    2   ------ Interrupt ------  ------ Interrupt ------
    1                            1000 sub  $1,%dx
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1001 test $0,%dx
    1   1002 jgte .top
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1001 test $0,%dx
    1                            1002 jgte .top
    1   ------ Interrupt ------  ------ Interrupt ------
    0   1000 sub  $1,%dx
    0   1001 test $0,%dx
    1   ------ Interrupt ------  ------ Interrupt ------
    0                            1000 sub  $1,%dx
    0                            1001 test $0,%dx
    0                            1002 jgte .top
    0   ------ Interrupt ------  ------ Interrupt ------
    0   1002 jgte .top
    0   ------ Interrupt ------  ------ Interrupt ------
   -1                            1000 sub  $1,%dx
    0   ------ Interrupt ------  ------ Interrupt ------
   -1   1000 sub  $1,%dx
   -1   1001 test $0,%dx
   -1   1002 jgte .top
   -1   ------ Interrupt ------  ------ Interrupt ------
   -1                            1001 test $0,%dx
   -1                          1002 jgte .top
   -1 ------ Interrupt ------  ------ Interrupt ------
   -1 1003 halt
   -1 ----- Halt;Switch -----  ----- Halt;Switch -----
   -1                          1003 halt
```

Next we’ll examine a different program(looping-race-nolock.s).
This program accesses a shared variable located at memory address
2000; we’ll call this variable **value** for simplicity. Run it with a single
thread and make sure you understand what it does, like this:
./x86.py -p looping-race-nolock.s -t 1 -M 2000
What value is found in value (i.e., at memory address 2000) throughout
the run? Use -c to check your answer.

```
$ python3 x86.py -p looping-race-nolock.s -t 1 -M 2000
...

 2000          Thread 0
    0
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax   // ax == 1
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx // bx == -1
    1   1004 test $0, %bx
    1   1005 jgt .top    // (bx > 0) == False
    1   1006 halt
```

Now run with multiple iterations and threads:
./x86.py -p looping-race-nolock.s -t 2 -a bx=3 -M 2000
Do you understand why the code in each thread loops three times?

```
Because of the context switch, each thread holds distinct value of bx.
```

What will the final value of value be?

```
 $ python3 x86.py -p looping-race-nolock.s
 ...
 
 2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax   // ax == 1
    1   1002 mov %ax, 2000
    1  1003 sub  $1, %bx // bx == 2
    1  1004 test $0, %bx
    1  1005 jgt .top
    1  1000 mov 2000, %ax // ax == 1
    1  1001 add $1, %ax  // ax == 2
    2  1002 mov %ax, 2000
    2  1003 sub  $1, %bx // bx == 1
    2   1004 test $0, %bx
    2   1005 jgt .top
    2   1000 mov 2000, %ax // ax == 2
    2   1001 add $1, %ax   // ax == 3
    3   1002 mov %ax, 2000
    3   1003 sub  $1, %bx // bx == 0
    3   1004 test $0, %bx
    3   1005 jgt .top
    3   1006 halt
    3   ----- Halt;Switch -----  ----- Halt;Switch -----
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax  // ax == 4
    4                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx // bx == 2
    ?                            1004 test $0, %bx
    ?                            1005 jgt .top
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax
    5                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx // bx == 1
    ?                            1004 test $0, %bx
    ?                            1005 jgt .top
    ?                            1000 mov 2000, %ax
    ?                            1001 add $1, %ax
    6                            1002 mov %ax, 2000
    ?                            1003 sub  $1, %bx // bx == 0
    ?                            1004 test $0, %bx
    ?                            1005 jgt .top
    ?                            1006 halt
```

Now run with random interrupt intervals:
./x86.py -p looping-race-nolock.s -t 2 -M 2000 -i 4 -r -s 0

```
$ python3 x86.py -p looping-race-nolock.s
 -t 2 -M 2000 -i 4 -r -s 0
2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1000 mov 2000, %ax
    1                            1001 add $1, %ax
    2                            1002 mov %ax, 2000
    2                            1003 sub  $1, %bx
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1004 test $0, %bx
    2   1005 jgt .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2                            1004 test $0, %bx
    2                            1005 jgt .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1006 halt
    2   ----- Halt;Switch -----  ----- Halt;Switch -----
    2                            1006 halt
```

Then change the random seed, setting -s 1, then -s 2, etc. 

```
(-s 1)
 2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax //ax == 0
    0   ------ Interrupt ------  ------ Interrupt ------
    0                            1000 mov 2000, %ax
    0                            1001 add $1, %ax       // ax == 1
    1                            1002 mov %ax, 2000
    1                            1003 sub  $1, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1001 add $1, %ax // ax == 1
    1   1002 mov %ax, 2000 // #0's incrementing is failed.
    1   1003 sub  $1, %bx
    1   1004 test $0, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1004 test $0, %bx
    1                            1005 jgt .top
    1   ------ Interrupt ------  ------ Interrupt ------
    1   1005 jgt .top
    1   1006 halt
    1   ----- Halt;Switch -----  ----- Halt;Switch -----
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1006 halt
    
(-s 2)
 2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   1003 sub  $1, %bx
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1000 mov 2000, %ax
    1                            1001 add $1, %ax
    2                            1002 mov %ax, 2000
    2                            1003 sub  $1, %bx
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1004 test $0, %bx
    2   ------ Interrupt ------  ------ Interrupt ------
    2                            1004 test $0, %bx
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1005 jgt .top
    2   1006 halt
    2   ----- Halt;Switch -----  ----- Halt;Switch -----
    2                            1005 jgt .top
    2                            1006 halt
   
```

Can you tell, just by looking at the thread interleaving, what the final
value of value will be? Does the exact location of the interrupt
matter?

> Yes.

 Where can it safely occur? Where does an interrupt cause
trouble?

> While the adding sequence, the interleaving should not occur.

 In other words, where is the critical section exactly?

> mov 2000, %ax
> add $1, %ax
> mov %ax, 2000

Now use a fixed interrupt interval to explore the program further.
Run:
./x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1
See if you can guess what the final value of the shared variable
value will be. What about when you change -i 2, -i 3, etc.?
For which interrupt intervals does the program give the “correct”
final answer?

```
$ python3 x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 1
 2000          Thread 0                Thread 1
    0
    ?   1000 mov 2000, %ax // ax == 0
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1000 mov 2000, %ax  // ax == 0
    ?   ------ Interrupt ------  ------ Interrupt ------
    0   1001 add $1, %ax  // ax == 1
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1001 add $1, %ax  // ax == 1
    ?   ------ Interrupt ------  ------ Interrupt ------
    1   1002 mov %ax, 2000
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1002 mov %ax, 2000
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1003 sub  $1, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1004 test $0, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1004 test $0, %bx
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?                            1005 jgt .top
    ?   ------ Interrupt ------  ------ Interrupt ------
    ?   1006 halt
    ?   ----- Halt;Switch -----  ----- Halt;Switch -----
    ?   ------ Interrupt ------  ------ Interrupt ------
    1                            1006 halt

$ python3 x86.py -p looping-race-nolock.s -a bx=1 -t 2 -M 2000 -i 3 -c
     2000          Thread 0                Thread 1
    0
    0   1000 mov 2000, %ax
    0   1001 add $1, %ax
    1   1002 mov %ax, 2000
    1   ------ Interrupt ------  ------ Interrupt ------
    1                            1000 mov 2000, %ax
    1                            1001 add $1, %ax
    2                            1002 mov %ax, 2000
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1003 sub  $1, %bx
    2   1004 test $0, %bx
    2   1005 jgt .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2                            1003 sub  $1, %bx
    2                            1004 test $0, %bx
    2                            1005 jgt .top
    2   ------ Interrupt ------  ------ Interrupt ------
    2   1006 halt
    2   ----- Halt;Switch -----  ----- Halt;Switch -----
    2                            1006 halt
```

Now run the same code for more loops (e.g., set -a bx=100). What
interrupt intervals, set with the -i flag, lead to a “correct” outcome?
Which intervals lead to surprising results?

```
(-i 3)
$ python3 x86.py -p looping-race-nolock.s -a bx=100 -t 2 -M 2000 -i 3 -c | grep " 200 "
  200                            1002 mov %ax, 2000
  200   ------ Interrupt ------  ------ Interrupt ------
  200   1003 sub  $1, %bx
  200   1004 test $0, %bx
  200   1005 jgt .top
  200   ------ Interrupt ------  ------ Interrupt ------
  200                            1003 sub  $1, %bx
  200                            1004 test $0, %bx
  200                            1005 jgt .top
  200   ------ Interrupt ------  ------ Interrupt ------
  200   1006 halt
  200   ----- Halt;Switch -----  ----- Halt;Switch -----
  200                            1006 halt
```

> It seems the favorable value for "-i" is any multiples of 3.
>
> Because...

```
# critical section
mov 2000, %ax  # get 'value' at address 2000
add $1, %ax    # increment it
mov %ax, 2000  # store it back
# critical section ends
sub  $1, %bx
test $0, %bx
jgt .top

halt
```

> The loop section has 6 lines altogether, including 3 for the critical section and the other 3 for the rest.
>
> So, interrupting every 3 lines(or multiple of 3 lines) never cause the race condition.

We’ll examine one last program in this homework (wait-for-me.s).
Run the code like this:
./x86.py -p wait-for-me.s -a ax=1,ax=0 -R ax -M 2000
This sets the %ax register to 1 for thread 0, and 0 for thread 1, and
watches the value of %ax and memory location 2000 throughout
the run. 

How should the code behave?  How is the value at location
2000 being used by the threads? What will its final value be?

```
 2000      ax          Thread 0                Thread 1
    0       1
    0       1   1000 test $1, %ax
    0       1   1001 je .signaller
    1       1   1006 mov  $1, 2000
    1       1   1007 halt
    1       0   ----- Halt;Switch -----  ----- Halt;Switch -----
    1       0                            1000 test $1, %ax
    1       0                            1001 je .signaller
    1       0                            1002 mov  2000, %cx
    1       0                            1003 test $1, %cx
    1       0                            1004 jne .waiter
    1       0                            1005 halt
```

Now switch the inputs:
./x86.py -p wait-for-me.s -a ax=0,ax=1 -R ax -M 2000
How do the threads behave? What is thread 0 doing?

> #0 is waiting for the #1 ,which can only change the value of 2000 to 1.

 How would
changing the interrupt interval (e.g., -i 1000, or perhaps to use
random intervals) change the trace outcome? Is the program efficiently
using the CPU?

> No.  #0 is just waiting for interrupting all the time. (,which is called 'spin')

