# Homework 50

This section introduces afs.py, a simple AFS simulator you can use
to shore up your knowledge of how the Andrew File System works. Read
the README file for more details.
Questions

Run a few simple cases to make sure you can predict what values
will be read by clients. Vary the random seed flag (-s) and see
if you can trace through and predict both **intermediate values** as
well as the **final values** stored in the files. Also vary the number of
files (**-f**), the number of clients (**-C**), and the read ratio (**-r**, from
between 0 to 1) to make it a bit more challenging. You might also
want to generate slightly longer traces to make for more interesting
interactions, e.g., (-n 2 or higher).

```
$ python3 afs.py -s 0
...
      Server                         c0                          c1
file:a contains:0
                            open:a [fd:0]
                                                        open:a [fd:0]
                                                        read:0 -> value? // 0
                                                        close:0
                            write:0 value? -> 1 // 0 -> 1
                                                        open:a [fd:1]
                                                        read:1 -> value? // 0
                            close:0
                                                        invalidate file:a cache: {'a': {'data': 0, 'dirty': False, 'refcnt': 1, 'valid': True}}
                                                        close:1
                            open:a [fd:1]
                            read:1 -> value? // 1
                            close:1
file:a contains:1                            
```

```
$ python3 afs.py -s 1 -C 3 -f 2 -r 0.1 -n 3
      Server                         c0                          c1                          c2
file:a contains:0
file:b contains:1
                                                                                    open:b [fd:0]
                            open:a [fd:0]
                            write:0 0 -> 2
                                                        open:b [fd:0]
                                                                                    read:0 -> 1
                                                        write:0 1 -> 3
                            close:0
                                                        close:0
a:2, b:3                                                        
                                                                                    invalidate file:b cache: {'b': {'data': 1, 'dirty': False, 'refcnt': 1, 'valid': True}}
                            open:b [fd:1]
                            write:1 3 -> 4
                                                        open:a [fd:1]
                                                        read:1 -> 2
                            close:1
a:2, b:4                           
                                                        invalidate file:b cache: {'b': {'data': 3, 'dirty': False, 'refcnt': 0, 'valid': True}, 'a': {'data': 2, 'dirty': False, 'refcnt': 1, 'valid': True}}
                                                                                    invalidate file:b cache: {'b': {'data': 1, 'dirty': False, 'refcnt': 1, 'valid': False}}
                            open:a [fd:2]
                            write:2 2 -> 5
                                                        close:1
                            close:2
a:5, b:4                            
                                                        invalidate file:a cache: {'b': {'data': 3, 'dirty': False, 'refcnt': 0, 'valid': False}, 'a': {'data': 2, 'dirty': False, 'refcnt': 0, 'valid': True}}
                                                                                    close:0
                                                        open:b [fd:2]
                                                        write:2 4 -> 6
                                                                                    open:a [fd:1]
                                                                                    write:1 5 -> 7
                                                                                    close:1
a:7, b:4                                                                                    
                            invalidate file:a cache: {'a': {'data': 5, 'dirty': False, 'refcnt': 0, 'valid': True}, 'b': {'data': 4, 'dirty': False, 'refcnt': 0, 'valid': True}}
                                                        invalidate file:a cache: {'b': {'data': 6, 'dirty': True, 'refcnt': 1, 'valid': True}, 'a': {'data': 2, 'dirty': False, 'refcnt': 0, 'valid': False}}
                                                                                    open:a [fd:2]
                                                                                    write:2 7 -> 8
                                                        close:2
                            invalidate file:b cache: {'a': {'data': 5, 'dirty': False, 'refcnt': 0, 'valid': False}, 'b': {'data': 4, 'dirty': False, 'refcnt': 0, 'valid': True}}
                                                                                    invalidate file:b cache: {'a': {'data': 8, 'dirty': True, 'refcnt': 1, 'valid': True}}
                                                                                    close:2
a:8, b:6                                                                                    
                            invalidate file:a cache: {'a': {'data': 5, 'dirty': False, 'refcnt': 0, 'valid': False}, 'b': {'data': 4, 'dirty': False, 'refcnt': 0, 'valid': False}}
                                                        invalidate file:a cache: {'b': {'data': 6, 'dirty': False, 'refcnt': 0, 'valid': True}, 'a': {'data': 2, 'dirty': False, 'refcnt': 0, 'valid': False}}
file:a contains:8
file:b contains:6
```

Now do the same thing and see if you can predict each callback that
the AFS server initiates. Try different random seeds, and make sure
to use a high level of detailed feedback (e.g., -d 3) to see when callbacks
occur when you have the program compute the answers for
you (with -c). Can you guess exactly when each callback occurs?
What is the precise condition for one to take place?

```
$ python3 afs.py -s 2 -d 3 -c
      Server                         c0                          c1
file:a contains:0
                                                        open:a [fd:0]
getfile:a c:c1 [0]

                                                        write:0 0 -> 1

                                                        close:0
putfile:a c:c1 [1]

                            open:a [fd:0]
getfile:a c:c0 [1]

                            write:0 1 -> 2

                            close:0
putfile:a c:c0 [2]
callback: c:c1 file:a
                                                        invalidate file:a cache: {'a': {'data': 1, 'dirty': False, 'refcnt': 0, 'valid': True}}
                                                        invalidate a

                                                        open:a [fd:1]
getfile:a c:c1 [2]

                                                        read:1 -> 2

                                                        close:1

                            open:a [fd:1]

                            read:1 -> 2

                            close:1

file:a contains:2
```

> Each callback occurs when one modified and closed a file which the other one has accessed once.

Similar to above, run with some different random seeds and see if
you can predict the exact cache state at each step. Cache state can
be observed by running with -c and -d 7.

```
$ python3 afs.py -s 3 -d 7 -c
ARG seed 3
ARG numclients 2
ARG numsteps 2
ARG numfiles 1
ARG readratio 0.5
ARG actions
ARG schedule
ARG detail 7

[(1, 'a', 0), (3, 0), (4, 0), (1, 'a', 1), (3, 1), (4, 1)]
[(1, 'a', 0), (2, 0), (4, 0), (1, 'a', 1), (3, 1), (4, 1)]
      Server                         c0                          c1
file:a contains:0
                            open:a [fd:0]
getfile:a c:c0 [0]
                            [a: 0 (v=1,d=0,r=1)] // opened by c0

                            write:0 0 -> 1
                            [a: 1 (v=1,d=1,r=1)] // written but yet to be flushed 

                                                        open:a [fd:0]
getfile:a c:c1 [0]
                                                        [a: 0 (v=1,d=0,r=1)] // incremented stale reference count

                            close:0
putfile:a c:c0 [1]
callback: c:c1 file:a
                                                        invalidate file:a cache: {'a': {'data': 0, 'dirty': False, 'refcnt': 1, 'valid': True}}
                                                        invalidate a
                                                        [a: 0 (v=0,d=0,r=1)] // invalidated
                            [a: 1 (v=1,d=0,r=0)] // closed and flushed

                                                        read:0 -> 0
                                                        [a: 0 (v=0,d=0,r=1)]

                            open:a [fd:1]
                            [a: 1 (v=1,d=0,r=1)] // opened

                                                        close:0

                            write:1 1 -> 2
                            [a: 2 (v=1,d=1,r=1)] // written

                                                        open:a [fd:1]
getfile:a c:c1 [1]
                                                        [a: 1 (v=1,d=0,r=1)]

                                                        write:1 1 -> 3
                                                        [a: 3 (v=1,d=1,r=1)]

                                                        close:1
putfile:a c:c1 [3]
callback: c:c0 file:a
                            invalidate file:a cache: {'a': {'data': 2, 'dirty': True, 'refcnt': 1, 'valid': True}}
                            invalidate a
                            [a: 2 (v=0,d=1,r=1)]
                                                        [a: 3 (v=1,d=0,r=0)] // not updated

                            close:1
putfile:a c:c0 [2]
callback: c:c1 file:a
                                                        invalidate file:a cache: {'a': {'data': 3, 'dirty': False, 'refcnt': 0, 'valid': True}}
                                                        invalidate a
                                                        [a: 3 (v=0,d=0,r=0)]
                            [a: 2 (v=1,d=0,r=0)]

file:a contains:2
```

Now let’s construct some specific workloads. Run the simulation
with `-A oa1:w1:c1,oa1:r1:c1` flag. What are different possible
values observed by client 1 when it reads the file a, when running
with the random scheduler? (try different random seeds to
see different outcomes)? Of all the possible schedule interleavings
of the two clients’ operations, how many of them lead to client 1
reading the value 1, and how many reading the value 0?

```
$ python3 afs.py -A oa1:w1:c1,oa1:r1:c1 -s 4
      Server                         c0                          c1
file:a contains:0
                            open:a [fd:1]
                            write:1 0 -> 1
                            close:1
                                                        open:a [fd:1]
                                                        read:1 -> 1
                                                        close:1
file:a contains:1
```

```
$ python3 afs.py -A oa1:w1:c1,oa1:r1:c1 -s 5
      Server                         c0                          c1
file:a contains:0
                                                        open:a [fd:1]
                                                        read:1 -> 0
                                                        close:1
                            open:a [fd:1]
                            write:1 0 -> 1
                            close:1
                                                        invalidate file:a cache: {'a': {'data': 0, 'dirty': False, 'refcnt': 0, 'valid': True}}
file:a contains:1
```

Now let’s construct some specific schedules. When running with
the `-A oa1:w1:c1,oa1:r1:c1` flag, also run with the following
schedules: `-S 01`, `-S 100011`, `-S 011100`, and others of which
you can think. What value will client 1 read?

```
$ ... -S 01
(c1 read file a:0)
$ ... -S 100011
(c1 read file a:0)
$ ... -S 011100
(c1 read file a:0)
$ ... -S 000111
(c1 read file a:1)
```



Now run with this workload: `-A oa1:w1:c1,oa1:w1:c1`, and
vary the schedules as above. What happens when you run with `-S`
`011100`? 

```
      Server                         c0                          c1
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                                                        write:1 0 -> 1
                                                        close:1
                            invalidate file:a cache: {'a': {'data': 0, 'dirty': False, 'refcnt': 1, 'valid': True}}
                            write:1 0 -> 2
                            close:1        // last writes wins
                                                        invalidate file:a cache: {'a': {'data': 1, 'dirty': False, 'refcnt': 0, 'valid': True}}
file:a contains:2
```

What about when you run with `-S 010011`? What is
important in determining the final value of the file?

```
file:a contains:0
                            open:a [fd:1]
                                                        open:a [fd:1]
                            write:1 0 -> 1
                            close:1
                                                        invalidate file:a cache: {'a': {'data': 0, 'dirty': False, 'refcnt': 1, 'valid': True}}
                                                        write:1 0 -> 2
                                                        close:1
                            invalidate file:a cache: {'a': {'data': 1, 'dirty': False, 'refcnt': 0, 'valid': True}}
file:a contains:2
```

> The last client who wrote a value win.

