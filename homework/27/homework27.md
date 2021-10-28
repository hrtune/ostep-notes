# Homework (Code)

In this section, we’ll write some simple multi-threaded programs and
use a specific tool, called helgrind, to find problems in these programs.
Read the README in the homework download for details on how to
build the programs and run helgrind.

## Questions

1: First build `main-race.c`. Examine the code so you can see the
(hopefully obvious) data race in the code. Now run `helgrind` (by
typing `valgrind --tool=helgrind main-race`) to see how it
reports the race. 

Does it point to the right lines of code? 

> No.

What other
information does it give to you?

```
Possible data race during write of size 4 at 0x10C014 by thread #1
==252== Locks held: none
==252==    at 0x109236: main (main-race.c:15)
==252==
==252== This conflicts with a previous write of size 4 by thread #2
==252== Locks held: none
==252==    at 0x1091BE: worker (main-race.c:8)
==252==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==252==    by 0x4861608: start_thread (pthread_create.c:477)
==252==    by 0x499D292: clone (clone.S:95)
==252==  Address 0x10c014 is 0 bytes inside data symbol "balance"
```

> It tells me there may be a conflict between #1 and #2

What happens when you remove one of the offending lines of code?
Now add a lock around one of the updates to the shared variable,
and then around both. What does helgrind report in each of these
cases?

```
$ valgrind --tool=helgrind ./main-race-halflocked 2>&1
...
==1213== Possible data race during read of size 4 at 0x10C024 by thread #1
==1213== Locks held: 1, at address 0x10C040
==1213==    at 0x1092AA: main (main-race-halflocked.c:23)
==1213==
==1213== This conflicts with a previous write of size 4 by thread #2
==1213== Locks held: none
==1213==    at 0x10921E: worker (main-race-halflocked.c:11)
==1213==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1213==    by 0x4861608: start_thread (pthread_create.c:477)
==1213==    by 0x499D292: clone (clone.S:95)
==1213==  Address 0x10c024 is 0 bytes inside data symbol "balance"
==1213==
...

$ valgrind --tool=helgrind ./main-race-halflocked 2>&1
==1216== Helgrind, a thread error detector
==1216== Copyright (C) 2007-2017, and GNU GPL'd, by OpenWorks LLP et al.
==1216== Using Valgrind-3.15.0 and LibVEX; rerun with -h for copyright info
==1216== Command: ./main-race-locked
==1216==
==1216==
==1216== Use --history-level=approx or =none to gain increased speed, at
==1216== the cost of reduced accuracy of conflicting-access information
==1216== For lists of detected and suppressed errors, rerun with: -s
==1216== ERROR SUMMARY: 0 errors from 0 contexts (suppressed: 7 from 7)
```

> Happy for no errors.

Now let’s look at main-deadlock.c. Examine the code. This
code has a problem known as **deadlock** (which we discuss in much
more depth in a forthcoming chapter). Can you see what problem
it might have?

```c
(main-deadlock.c)
...

void* worker(void* arg) {
    if ((long long) arg == 0) {
	Pthread_mutex_lock(&m1);
	Pthread_mutex_lock(&m2);
    } else {
	Pthread_mutex_lock(&m2);
	Pthread_mutex_lock(&m1);
    }
    Pthread_mutex_unlock(&m1);
    Pthread_mutex_unlock(&m2);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    Pthread_create(&p1, NULL, worker, (void *) (long long) 0);
    Pthread_create(&p2, NULL, worker, (void *) (long long) 1);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    return 0;
}
```

> Both threads do have each m1 and m2 lock, therefore they have deadlocks.

Now run helgrind on this code. What does helgrind report?

```
(helgrind report)
==1223== Thread #3: lock order "0x10C040 before 0x10C080" violated
==1223==
==1223== Observed (incorrect) order is: acquisition of lock at 0x10C080
==1223==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1223==    by 0x109269: worker (main-deadlock.c:13)
==1223==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1223==    by 0x4861608: start_thread (pthread_create.c:477)
==1223==    by 0x499D292: clone (clone.S:95)
==1223==
==1223==  followed by a later acquisition of lock at 0x10C040
==1223==    at 0x483FEDF: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1223==    by 0x109298: worker (main-deadlock.c:14)
==1223==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1223==    by 0x4861608: start_thread (pthread_create.c:477)
==1223==    by 0x499D292: clone (clone.S:95)
```

Now run helgrind on main-deadlock-global.c. Examine
the code; does it have the same problem that main-deadlock.c
has?

```c
(main-deadlock-global.c)
...
void* worker(void* arg) {
    Pthread_mutex_lock(&g);
    if ((long long) arg == 0) {
	Pthread_mutex_lock(&m1);
	Pthread_mutex_lock(&m2);
    } else {
	Pthread_mutex_lock(&m2);
	Pthread_mutex_lock(&m1);
    }
    Pthread_mutex_unlock(&m1);
    Pthread_mutex_unlock(&m2);
    Pthread_mutex_unlock(&g);
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p1, p2;
    Pthread_create(&p1, NULL, worker, (void *) (long long) 0);
    Pthread_create(&p2, NULL, worker, (void *) (long long) 1);
    Pthread_join(p1, NULL);
    Pthread_join(p2, NULL);
    return 0;
}

```

Should helgrind be reporting the same error? 

> No, because it seems there are no deadlocks.

What does this tell you about tools like helgrind?

> It might not be helpful for detecting deadlocks.

Let’s next look at main-signal.c. This code uses a variable (done)
to signal that the child is done and that the parent can now continue.

```c
int done = 0;

void* worker(void* arg) {
    printf("this should print first\n");
    done = 1;
    return NULL;
}

int main(int argc, char *argv[]) {
    pthread_t p;
    Pthread_create(&p, NULL, worker, NULL);
    while (done == 0){
    }
    printf("this should print last\n");
    return 0;
}

```

Why is this code inefficient? (what does the parent end up spending
its time doing, particularly if the child thread takes a long time
to complete?)

> spinning.

Now run helgrind on this program. What does it report? Is the
code correct?

```
==1251== Possible data race during read of size 4 at 0x10C014 by thread #1
==1251== Locks held: none
==1251==    at 0x109239: main (main-signal.c:16)
==1251==
==1251== This conflicts with a previous write of size 4 by thread #2
==1251== Locks held: none
==1251==    at 0x1091C5: worker (main-signal.c:9)
==1251==    by 0x4842B1A: ??? (in /usr/lib/x86_64-linux-gnu/valgrind/vgpreload_helgrind-amd64-linux.so)
==1251==    by 0x4861608: start_thread (pthread_create.c:477)
==1251==    by 0x499D292: clone (clone.S:95)
==1251==  Address 0x10c014 is 0 bytes inside data symbol "done"
==1251==
```

Now look at a slightly modified version of the code, which is found
in main-signal-cv.c. This version uses a condition variable to
do the signaling (and associated lock). Why is this code preferred
to the previous version? Is it correctness, or performance, or both?

> Those are for both.
>
> The cond_wait makes better performance and the associated lock ensure the integrity of the data.

Once again run helgrind on main-signal-cv. Does it report
any errors?

> No, never.