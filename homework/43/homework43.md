# Homework 43

This section introduces lfs.py, a simple LFS simulator you can use
to understand better how an LFS-based file system works. Read the
README for details on how to run the simulator.
Questions

1, Run `./lfs.py -n 3`, perhaps varying the seed (-s). Can you figure
out which commands were run to generate the final file system
contents? Can you tell which order those commands were issued?

```
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

create file /ku3
write file /ku3 <- write file  /ku3 offset=7 size=4
create file /qg9

FINAL file system contents:
[   0 ] ?    checkpoint: 14 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] ?    [.,0] [..,0] -- -- -- -- -- --
[   2 ] ?    type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] ?    chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ] ?    [.,0] [..,0] [ku3,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] ?    z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0
[   9 ] ?    type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 8
[  10 ] ?    chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  11 ] ?    [.,0] [..,0] [ku3,1] [qg9,2] -- -- -- --
[  12 ] ?    type:dir size:1 refs:2 ptrs: 11 -- -- -- -- -- -- --
[  13 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  14 ] ?    chunk(imap): 12 9 13 -- -- -- -- -- -- -- -- -- -- -- -- --
```

> Yes, I can. Because the more the imap table (or inodes) is positioned in tail, the newer.

Finally, can you determine the liveness of each block in the final
file system state? Use -o to show which commands were run, and
-c to show the liveness of the final file system state. How much
harder does the task become for you as you increase the number of
commands issued (i.e., change -n 3 to -n 5)?

```
(-n 3)
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

create file /ku3
write file  /ku3 offset=7 size=4
create file /qg9

FINAL file system contents:
[   0 ] live checkpoint: 14 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ]      [.,0] [..,0] -- -- -- -- -- --
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ]      [.,0] [..,0] [ku3,1] -- -- -- -- --
[   5 ]      type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] live z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0z0
[   9 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 8
[  10 ]      chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  11 ] live [.,0] [..,0] [ku3,1] [qg9,2] -- -- -- --
[  12 ] live type:dir size:1 refs:2 ptrs: 11 -- -- -- -- -- -- --
[  13 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  14 ] live chunk(imap): 12 9 13 -- -- -- -- -- -- -- -- -- -- -- -- --
```

```
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

create file /ku3
write file  /ku3 offset=7 size=4
create file /qg9
link file   /qg9 /is8
create dir  /cl6

FINAL file system contents:
[   0 ] live checkpoint: 23 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ]      [.,0] [..,0] -- -- -- -- -- --
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ]      [.,0] [..,0] [ku3,1] -- -- -- -- --
[   5 ]      type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] live x0x0x0x0x0x0x0x0x0x0x0x0x0x0x0x0
[   9 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- -- -- 8
[  10 ]      chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  11 ]      [.,0] [..,0] [ku3,1] [qg9,2] -- -- -- --
[  12 ]      type:dir size:1 refs:2 ptrs: 11 -- -- -- -- -- -- --
[  13 ]      type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  14 ]      chunk(imap): 12 9 13 -- -- -- -- -- -- -- -- -- -- -- -- --
[  15 ]      [.,0] [..,0] [ku3,1] [qg9,2] [is8,2] -- -- --
[  16 ]      type:dir size:1 refs:2 ptrs: 15 -- -- -- -- -- -- --
[  17 ] live type:reg size:0 refs:2 ptrs: -- -- -- -- -- -- -- --
[  18 ]      chunk(imap): 16 9 17 -- -- -- -- -- -- -- -- -- -- -- -- --
[  19 ] live [.,0] [..,0] [ku3,1] [qg9,2] [is8,2] [cl6,3] -- --
[  20 ] live [.,3] [..,0] -- -- -- -- -- --
[  21 ] live type:dir size:1 refs:3 ptrs: 19 -- -- -- -- -- -- --
[  22 ] live type:dir size:1 refs:2 ptrs: 20 -- -- -- -- -- -- --
[  23 ] live chunk(imap): 21 9 17 22 -- -- -- -- -- -- -- -- -- -- -- --
```

> I manually confirmed each live section so '-n 3' takes 7 steps to determine whether each block is live or not.
>
> Likewise, '-5' takes 9 steps. The workload get bigger as the number of operation get bigger, perhaps. 

If you find the above painful, you can help yourself a little bit by
showing the set of updates caused by each specific command. To do
so, run `./lfs.py -n 3 -i`. Now see if it is easier to understand
what each command must have been. 

```
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

create file /tg4,1

[   0 ] ?    checkpoint: 7 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
[   4 ] ?    [.,0] [..,0] [tg4,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --


command? <- write file  /tg4 offset=6 size=0

[   0 ] ?    checkpoint: 9 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
[   8 ] ?    type:reg size:6 refs:1 ptrs: -- -- -- -- -- -- -- --
[   9 ] ?    chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- --


create file /lt0

[   0 ] ?    checkpoint: 13 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
[  10 ] ?    [.,0] [..,0] [tg4,1] [lt0,2] -- -- -- --
[  11 ] ?    type:dir size:1 refs:2 ptrs: 10 -- -- -- -- -- -- --
[  12 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  13 ] ?    chunk(imap): 11 8 12 -- -- -- -- -- -- -- -- -- -- -- -- --



FINAL file system contents:
[   0 ] ?    checkpoint: 13 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] ?    [.,0] [..,0] -- -- -- -- -- --
[   2 ] ?    type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] ?    chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ] ?    [.,0] [..,0] [tg4,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] ?    type:reg size:6 refs:1 ptrs: -- -- -- -- -- -- -- --
[   9 ] ?    chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  10 ] ?    [.,0] [..,0] [tg4,1] [lt0,2] -- -- -- --
[  11 ] ?    type:dir size:1 refs:2 ptrs: 10 -- -- -- -- -- -- --
[  12 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  13 ] ?    chunk(imap): 11 8 12 -- -- -- -- -- -- -- -- -- -- -- -- --
```

Change the random seed to
get different commands to interpret (e.g., -s 1, -s 2, -s 3, etc.).

To further test your ability to figure out what updates are made to
disk by each command, run the following: `./lfs.py -o -F -s 100` (and perhaps a few other random seeds). This just shows a set of commands and does NOT show you the final state of the file
system. Can you reason about what the final state of the file system must be?

```
INITIAL file system contents:
[   0 ] live checkpoint: 3 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] live [.,0] [..,0] -- -- -- -- -- --
[   2 ] live type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] live chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --

create file /us7
write file  /us7 offset=4 size=0
write file  /us7 offset=7 size=7

[   0 ]      checkpoint: 12 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ]      [.,0] [..,0] -- -- -- -- -- --
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ]      [.,0] [..,0] [us7,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] ?    type:reg size:4 refs:1 ptrs: -- -- -- -- -- -- -- --
[   9 ] ?    chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  10 ] ?    x0x0x0x0x0x0x0x0x0x0x0x0x0x0x0x0
[  11 ] ?    type:reg size:4 refs:1 ptrs: -- -- -- -- -- -- -- 10 !! the size is 8
[  12 ] ?    chunk(imap): 5 11 -- -- -- -- -- -- -- -- -- -- -- -- -- --
```

Now see if you can determine which files and directories are live
after a number of file and directory operations. Run tt `./lfs.py-n 20 -s 1` and then examine the final file system state. Can you figure out which pathnames are valid?

```
FINAL file system contents:
[   0 ] live checkpoint: 99 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] ?    [.,0] [..,0] -- -- -- -- -- --
[   2 ] ?    type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] ?    chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ] ?    [.,0] [..,0] [tg4,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] ?    type:reg size:6 refs:1 ptrs: -- -- -- -- -- -- -- --
[   9 ] ?    chunk(imap): 5 8 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  10 ] ?    [.,0] [..,0] [tg4,1] [lt0,2] -- -- -- --
[  11 ] ?    type:dir size:1 refs:2 ptrs: 10 -- -- -- -- -- -- --
[  12 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  13 ] ?    chunk(imap): 11 8 12 -- -- -- -- -- -- -- -- -- -- -- -- --
[  14 ] ?    n0n0n0n0n0n0n0n0n0n0n0n0n0n0n0n0
[  15 ] ?    y1y1y1y1y1y1y1y1y1y1y1y1y1y1y1y1
[  16 ] ?    p2p2p2p2p2p2p2p2p2p2p2p2p2p2p2p2
[  17 ] ?    l3l3l3l3l3l3l3l3l3l3l3l3l3l3l3l3
[  18 ] ?    h4h4h4h4h4h4h4h4h4h4h4h4h4h4h4h4
[  19 ] ?    o5o5o5o5o5o5o5o5o5o5o5o5o5o5o5o5
[  20 ] ?    y6y6y6y6y6y6y6y6y6y6y6y6y6y6y6y6
[  21 ] ?    type:reg size:8 refs:1 ptrs: -- 14 15 16 17 18 19 20
[  22 ] ?    chunk(imap): 11 8 21 -- -- -- -- -- -- -- -- -- -- -- -- --
[  23 ] ?    [.,0] [..,0] [tg4,1] [lt0,2] [oy3,1] -- -- --
[  24 ] ?    type:dir size:1 refs:2 ptrs: 23 -- -- -- -- -- -- --
[  25 ] ?    type:reg size:6 refs:2 ptrs: -- -- -- -- -- -- -- --
[  26 ] ?    chunk(imap): 24 25 21 -- -- -- -- -- -- -- -- -- -- -- -- --
[  27 ] ?    [.,0] [..,0] [tg4,1] [lt0,2] [oy3,1] [af4,3] -- --
[  28 ] ?    type:dir size:1 refs:2 ptrs: 27 -- -- -- -- -- -- --
[  29 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  30 ] ?    chunk(imap): 28 25 21 29 -- -- -- -- -- -- -- -- -- -- -- --
[  31 ] ?    a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0
[  32 ] ?    type:reg size:6 refs:2 ptrs: -- 31 -- -- -- -- -- --
[  33 ] ?    chunk(imap): 28 32 21 29 -- -- -- -- -- -- -- -- -- -- -- --
[  34 ] live u0u0u0u0u0u0u0u0u0u0u0u0u0u0u0u0
[  35 ] ?    v1v1v1v1v1v1v1v1v1v1v1v1v1v1v1v1
[  36 ] ?    x2x2x2x2x2x2x2x2x2x2x2x2x2x2x2x2
[  37 ] ?    t3t3t3t3t3t3t3t3t3t3t3t3t3t3t3t3
[  38 ] ?    v4v4v4v4v4v4v4v4v4v4v4v4v4v4v4v4
[  39 ] ?    n5n5n5n5n5n5n5n5n5n5n5n5n5n5n5n5
[  40 ] ?    type:reg size:8 refs:1 ptrs: 34 35 36 37 38 39 19 20
[  41 ] ?    chunk(imap): 28 32 40 29 -- -- -- -- -- -- -- -- -- -- -- --
[  42 ] ?    o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0o0
[  43 ] ?    l1l1l1l1l1l1l1l1l1l1l1l1l1l1l1l1
[  44 ] ?    b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2b2
[  45 ] ?    w3w3w3w3w3w3w3w3w3w3w3w3w3w3w3w3
[  46 ] ?    o4o4o4o4o4o4o4o4o4o4o4o4o4o4o4o4
[  47 ] ?    f5f5f5f5f5f5f5f5f5f5f5f5f5f5f5f5
[  48 ] ?    n6n6n6n6n6n6n6n6n6n6n6n6n6n6n6n6
[  49 ] ?    type:reg size:8 refs:2 ptrs: -- 42 43 44 45 46 47 48
[  50 ] ?    chunk(imap): 28 49 40 29 -- -- -- -- -- -- -- -- -- -- -- --
[  51 ] ?    [.,0] [..,0] -- [lt0,2] [oy3,1] [af4,3] -- --
[  52 ] ?    type:dir size:1 refs:2 ptrs: 51 -- -- -- -- -- -- --
[  53 ] ?    type:reg size:8 refs:1 ptrs: -- 42 43 44 45 46 47 48
[  54 ] ?    chunk(imap): 52 53 40 29 -- -- -- -- -- -- -- -- -- -- -- --
[  55 ] ?    m0m0m0m0m0m0m0m0m0m0m0m0m0m0m0m0
[  56 ] ?    j1j1j1j1j1j1j1j1j1j1j1j1j1j1j1j1
[  57 ] ?    i2i2i2i2i2i2i2i2i2i2i2i2i2i2i2i2
[  58 ] ?    type:reg size:8 refs:1 ptrs: -- -- -- -- -- 55 56 57
[  59 ] ?    chunk(imap): 52 53 40 58 -- -- -- -- -- -- -- -- -- -- -- --
[  60 ] live a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0
[  61 ] ?    f1f1f1f1f1f1f1f1f1f1f1f1f1f1f1f1
[  62 ] ?    type:reg size:8 refs:1 ptrs: -- -- -- -- -- 60 61 57
[  63 ] ?    chunk(imap): 52 53 40 62 -- -- -- -- -- -- -- -- -- -- -- --
[  64 ] live e0e0e0e0e0e0e0e0e0e0e0e0e0e0e0e0
[  65 ] live p1p1p1p1p1p1p1p1p1p1p1p1p1p1p1p1
[  66 ] live type:reg size:8 refs:1 ptrs: -- -- -- -- -- 60 64 65
[  67 ] ?    chunk(imap): 52 53 40 66 -- -- -- -- -- -- -- -- -- -- -- --
[  68 ] live u0u0u0u0u0u0u0u0u0u0u0u0u0u0u0u0
[  69 ] live v1v1v1v1v1v1v1v1v1v1v1v1v1v1v1v1
[  70 ] live g2g2g2g2g2g2g2g2g2g2g2g2g2g2g2g2
[  71 ] ?    v3v3v3v3v3v3v3v3v3v3v3v3v3v3v3v3
[  72 ] ?    r4r4r4r4r4r4r4r4r4r4r4r4r4r4r4r4
[  73 ] ?    c5c5c5c5c5c5c5c5c5c5c5c5c5c5c5c5
[  74 ] ?    type:reg size:8 refs:1 ptrs: 34 68 69 70 71 72 73 20
[  75 ] ?    chunk(imap): 52 53 74 66 -- -- -- -- -- -- -- -- -- -- -- --
[  76 ] live a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0a0
[  77 ] live a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1a1
[  78 ] live t2t2t2t2t2t2t2t2t2t2t2t2t2t2t2t2
[  79 ] live g3g3g3g3g3g3g3g3g3g3g3g3g3g3g3g3
[  80 ] live type:reg size:8 refs:1 ptrs: 34 68 69 70 76 77 78 79
[  81 ] ?    chunk(imap): 52 53 80 66 -- -- -- -- -- -- -- -- -- -- -- --
[  82 ] ?    [.,0] [..,0] [ln7,4] [lt0,2] [oy3,1] [af4,3] -- --
[  83 ] ?    [.,4] [..,0] -- -- -- -- -- --
[  84 ] ?    type:dir size:1 refs:3 ptrs: 82 -- -- -- -- -- -- --
[  85 ] ?    type:dir size:1 refs:2 ptrs: 83 -- -- -- -- -- -- --
[  86 ] ?    chunk(imap): 84 53 80 66 85 -- -- -- -- -- -- -- -- -- -- --
[  87 ] ?    type:reg size:8 refs:1 ptrs: -- 42 43 44 45 46 47 48
[  88 ] ?    chunk(imap): 84 87 80 66 85 -- -- -- -- -- -- -- -- -- -- --
[  89 ] ?    [.,4] [..,0] [zp3,5] -- -- -- -- --
[  90 ] ?    type:dir size:1 refs:2 ptrs: 89 -- -- -- -- -- -- --
[  91 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  92 ] ?    chunk(imap): 84 87 80 66 90 91 -- -- -- -- -- -- -- -- -- --
[  93 ] live [.,4] [..,0] [zp3,5] [zu5,6] -- -- -- --
[  94 ] live type:dir size:1 refs:2 ptrs: 93 -- -- -- -- -- -- --
[  95 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  96 ] ?    chunk(imap): 84 87 80 66 94 91 95 -- -- -- -- -- -- -- -- --
[  97 ] live [.,0] [..,0] [ln7,4] [lt0,2] -- [af4,3] -- --
[  98 ] live type:dir size:1 refs:3 ptrs: 97 -- -- -- -- -- -- --
[  99 ] live chunk(imap): 98 -- 80 66 94 91 95 -- -- -- -- -- -- -- -- --
```

> `[  93 ] live [.,4] [..,0] [zp3,5] [zu5,6] -- -- -- --`
>
> `[  97 ] live [.,0] [..,0] [ln7,4] [lt0,2] -- [af4,3] -- --`
>
> From above two directory contents, 
>
> /
> /ln7 , /lt0, /af4
> /ln7/zp3, /ln7/zu5
>
> are valid.

Run tt `./lfs.py -n 20 -s 1 -c -v` to see the results. Run with -o to see if your answers
match up given the series of random commands. Use different random
seeds to get more problems.

Now let’s issue some specific commands. First, let’s create a file
and write to it repeatedly. To do so, use the -L flag, which lets you
specify specific commands to execute. In this case, let’s create the
file ”/foo” and write to it 4 times:
`./lfs.py -L c,/foo:w,/foo,0,1:w,/foo,1,1:w,/foo,2,1:w,/foo,3,1 -o`. 
See if you can determine the liveness of the final file system state; use -c to check your answers.

```
create file /foo
write file  /foo offset=0 size=1
write file  /foo offset=1 size=1
write file  /foo offset=2 size=1
write file  /foo offset=3 size=1

FINAL file system contents:
[   0 ] live checkpoint: 19 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] ?    [.,0] [..,0] -- -- -- -- -- --
[   2 ] ?    type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] ?    chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- --
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] live v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0
[   9 ] ?    type:reg size:1 refs:1 ptrs: 8 -- -- -- -- -- -- --
[  10 ] ?    chunk(imap): 5 9 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  11 ] live t0t0t0t0t0t0t0t0t0t0t0t0t0t0t0t0
[  12 ] ?    type:reg size:2 refs:1 ptrs: 8 11 -- -- -- -- -- --
[  13 ] ?    chunk(imap): 5 12 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  14 ] live k0k0k0k0k0k0k0k0k0k0k0k0k0k0k0k0
[  15 ] ?    type:reg size:3 refs:1 ptrs: 8 11 14 -- -- -- -- --
[  16 ] ?    chunk(imap): 5 15 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  17 ] live g0g0g0g0g0g0g0g0g0g0g0g0g0g0g0g0
[  18 ] live type:reg size:4 refs:1 ptrs: 8 11 14 17 -- -- -- --
[  19 ] live chunk(imap): 5 18 -- -- -- -- -- -- -- -- -- -- -- -- -- --
```

Now, let’s do the same thing, but with a single write operation instead
of four. Run `./lfs.py -o -L c,/foo:w,/foo,0,4` to
create file ”/foo” and write 4 blocks with a single write operation.
Compute the liveness again, and check if you are right with -c.

```
create file /foo
write file  /foo offset=0 size=4

FINAL file system contents:
[   0 ] live checkpoint: 13 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] ?    [.,0] [..,0] -- -- -- -- -- --
[   2 ] ?    type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] ?    chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ] live [.,0] [..,0] [foo,1] -- -- -- -- --
[   5 ] live type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] live v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0v0
[   9 ] live t1t1t1t1t1t1t1t1t1t1t1t1t1t1t1t1
[  10 ] live k2k2k2k2k2k2k2k2k2k2k2k2k2k2k2k2
[  11 ] live g3g3g3g3g3g3g3g3g3g3g3g3g3g3g3g3
[  12 ] live type:reg size:4 refs:1 ptrs: 8 9 10 11 -- -- -- --
[  13 ] live chunk(imap): 5 12 -- -- -- -- -- -- -- -- -- -- -- -- -- --
```

What is the main difference between writing a file all at once (as
we do here) versus doing it one block at a time (as above)? 

> The filespan of the file foo is smaller if it is written at once.

What does this tell you about the importance of buffering updates in main
memory as the real LFS does?

> Buffering make each writes smaller and thus the read time of the file become less.

Let’s do another specific example. First, run the following command:
`./lfs.py -L c,/foo:w,/foo,0,1`. What does this set
of commands do? 

> It writes the file foo with size 1.

Now, run `./lfs.py -L c,/foo:w,/foo,7,1`.
What does this set of commands do? 

> It writes the file foo with size 8

How are the two different?

> The offset where to write the file foo is different.

What can you tell about the size field in the inode from these two
sets of commands?

> If you write to a file initially,
>
> (file size) = (offset) + 1

Now let’s look explicitly at file creation versus directory creation.
Run `./lfs.py -L c,/foo` and `./lfs.py -L d,/foo` to create
a file and then a directory. What is similar about these runs, and
what is different?

> Those two create something which is named "foo".
>
> The former create a file instead of a directory, which is created by the latter command.

The LFS simulator supports hard links as well. Run the following
command to study how they work:
`./lfs.py -L c,/foo:l,/foo,/bar:l,/foo,/goo -o -i`.

```
create file /foo

[   0 ] ?    checkpoint: 7 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
[   4 ] ?    [.,0] [..,0] [foo,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --


link file   /foo /bar

[   0 ] ?    checkpoint: 11 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
[   8 ] ?    [.,0] [..,0] [foo,1] [bar,1] -- -- -- --
[   9 ] ?    type:dir size:1 refs:2 ptrs: 8 -- -- -- -- -- -- --
[  10 ] ?    type:reg size:0 refs:2 ptrs: -- -- -- -- -- -- -- --
[  11 ] ?    chunk(imap): 9 10 -- -- -- -- -- -- -- -- -- -- -- -- -- --


link file   /foo /goo

[   0 ] ?    checkpoint: 15 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
...
[  12 ] ?    [.,0] [..,0] [foo,1] [bar,1] [goo,1] -- -- --
[  13 ] ?    type:dir size:1 refs:2 ptrs: 12 -- -- -- -- -- -- --
[  14 ] ?    type:reg size:0 refs:3 ptrs: -- -- -- -- -- -- -- --
[  15 ] ?    chunk(imap): 13 14 -- -- -- -- -- -- -- -- -- -- -- -- -- --



FINAL file system contents:
[   0 ] ?    checkpoint: 15 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ] ?    [.,0] [..,0] -- -- -- -- -- --
[   2 ] ?    type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ] ?    chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ] ?    [.,0] [..,0] [foo,1] -- -- -- -- --
[   5 ] ?    type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] ?    type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ] ?    chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] ?    [.,0] [..,0] [foo,1] [bar,1] -- -- -- --
[   9 ] ?    type:dir size:1 refs:2 ptrs: 8 -- -- -- -- -- -- --
[  10 ] ?    type:reg size:0 refs:2 ptrs: -- -- -- -- -- -- -- --
[  11 ] ?    chunk(imap): 9 10 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  12 ] ?    [.,0] [..,0] [foo,1] [bar,1] [goo,1] -- -- --
[  13 ] ?    type:dir size:1 refs:2 ptrs: 12 -- -- -- -- -- -- --
[  14 ] ?    type:reg size:0 refs:3 ptrs: -- -- -- -- -- -- -- --
[  15 ] ?    chunk(imap): 13 14 -- -- -- -- -- -- -- -- -- -- -- -- -- --
```

What blocks are written out when a hard link is created? How is
this similar to just creating a new file, and how is it different? 

> 4 blocks are written out when a hard link is created as when the file is created.
>
> If a hard link is created, it points the same imap entry as that of the target file.

How does the reference count field change as links are created?

> It is incremented by 1.

LFS makes many different policy decisions. We do not explore
many of them here – perhaps something left for the future – but here
is a simple one we do explore: the choice of inode number. First, run
`./lfs.py -p c100 -n 10 -o -a s` to show the usual behavior
with the ”sequential” allocation policy, which tries to use free
inode numbers nearest to zero. Then, change to a ”random” policy
by running `./lfs.py -p c100 -n 10 -o -a r` (the -p c100
flag ensures 100 percent of the random operations are file creations).
What on-disk differences does a random policy versus a sequential
policy result in?

```
$ python3 lfs.py -p c100 -n 10 -o -a s -c
...
FINAL file system contents:
[   0 ] live checkpoint: 43 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   1 ]      [.,0] [..,0] -- -- -- -- -- --
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ]      [.,0] [..,0] [kg5,1] -- -- -- -- --
[   5 ]      type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ]      chunk(imap): 5 6 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ]      [.,0] [..,0] [kg5,1] [hm5,2] -- -- -- --
[   9 ]      type:dir size:1 refs:2 ptrs: 8 -- -- -- -- -- -- --
[  10 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  11 ]      chunk(imap): 9 6 10 -- -- -- -- -- -- -- -- -- -- -- -- --
[  12 ]      [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] -- -- --
[  13 ]      type:dir size:1 refs:2 ptrs: 12 -- -- -- -- -- -- --
[  14 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  15 ]      chunk(imap): 13 6 10 14 -- -- -- -- -- -- -- -- -- -- -- --
[  16 ]      [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] [zv9,4] -- --
[  17 ]      type:dir size:1 refs:2 ptrs: 16 -- -- -- -- -- -- --
[  18 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  19 ]      chunk(imap): 17 6 10 14 18 -- -- -- -- -- -- -- -- -- -- --
[  20 ]      [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] [zv9,4] [xr4,5] --
[  21 ]      type:dir size:1 refs:2 ptrs: 20 -- -- -- -- -- -- --
[  22 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  23 ]      chunk(imap): 21 6 10 14 18 22 -- -- -- -- -- -- -- -- -- --
[  24 ] live [.,0] [..,0] [kg5,1] [hm5,2] [ht6,3] [zv9,4] [xr4,5] [px9,6]
[  25 ]      type:dir size:1 refs:2 ptrs: 24 -- -- -- -- -- -- --
[  26 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  27 ]      chunk(imap): 25 6 10 14 18 22 26 -- -- -- -- -- -- -- -- --
[  28 ]      [gu5,7] -- -- -- -- -- -- --
[  29 ]      type:dir size:2 refs:2 ptrs: 24 28 -- -- -- -- -- --
[  30 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  31 ]      chunk(imap): 29 6 10 14 18 22 26 30 -- -- -- -- -- -- -- --
[  32 ]      [gu5,7] [kv6,8] -- -- -- -- -- --
[  33 ]      type:dir size:2 refs:2 ptrs: 24 32 -- -- -- -- -- --
[  34 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  35 ]      chunk(imap): 33 6 10 14 18 22 26 30 34 -- -- -- -- -- -- --
[  36 ]      [gu5,7] [kv6,8] [wg3,9] -- -- -- -- --
[  37 ]      type:dir size:2 refs:2 ptrs: 24 36 -- -- -- -- -- --
[  38 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  39 ]      chunk(imap): 37 6 10 14 18 22 26 30 34 38 -- -- -- -- -- --
[  40 ] live [gu5,7] [kv6,8] [wg3,9] [og9,10] -- -- -- --
[  41 ] live type:dir size:2 refs:2 ptrs: 24 40 -- -- -- -- -- --
[  42 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  43 ] live chunk(imap): 41 6 10 14 18 22 26 30 34 38 42 -- -- -- -- --
```

```
$ python3 lfs.py -p c100 -n 10 -o -a r -c
FINAL file system contents:
[   0 ] live checkpoint: 52 38 -- -- -- 23 -- 13 53 -- -- 48 8 -- 33 --
[   1 ]      [.,0] [..,0] -- -- -- -- -- --
[   2 ]      type:dir size:1 refs:2 ptrs: 1 -- -- -- -- -- -- --
[   3 ]      chunk(imap): 2 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   4 ]      [.,0] [..,0] [kg5,205] -- -- -- -- --
[   5 ]      type:dir size:1 refs:2 ptrs: 4 -- -- -- -- -- -- --
[   6 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[   7 ]      chunk(imap): 5 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[   8 ] live chunk(imap): -- -- -- -- -- -- -- -- -- -- -- -- -- 6 -- --
[   9 ]      [.,0] [..,0] [kg5,205] [hm5,114] -- -- -- --
[  10 ]      type:dir size:1 refs:2 ptrs: 9 -- -- -- -- -- -- --
[  11 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  12 ]      chunk(imap): 10 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  13 ] live chunk(imap): -- -- 11 -- -- -- -- -- -- -- -- -- -- -- -- --
[  14 ]      [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] -- -- --
[  15 ]      type:dir size:1 refs:2 ptrs: 14 -- -- -- -- -- -- --
[  16 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  17 ]      chunk(imap): 15 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  18 ]      chunk(imap): -- -- -- -- 16 -- -- -- -- -- -- -- -- -- -- --
[  19 ]      [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] [zv9,81] -- --
[  20 ]      type:dir size:1 refs:2 ptrs: 19 -- -- -- -- -- -- --
[  21 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  22 ]      chunk(imap): 20 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  23 ] live chunk(imap): -- 21 -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  24 ]      [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] [zv9,81] [xr4,130] --
[  25 ]      type:dir size:1 refs:2 ptrs: 24 -- -- -- -- -- -- --
[  26 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  27 ]      chunk(imap): 25 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  28 ]      chunk(imap): -- -- 26 -- -- -- -- -- -- -- -- -- -- -- -- --
[  29 ] live [.,0] [..,0] [kg5,205] [hm5,114] [ht6,20] [zv9,81] [xr4,130] [px9,238]
[  30 ]      type:dir size:1 refs:2 ptrs: 29 -- -- -- -- -- -- --
[  31 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  32 ]      chunk(imap): 30 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  33 ] live chunk(imap): -- -- -- -- -- -- -- -- -- -- -- -- -- -- 31 --
[  34 ]      [gu5,27] -- -- -- -- -- -- --
[  35 ]      type:dir size:2 refs:2 ptrs: 29 34 -- -- -- -- -- --
[  36 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  37 ]      chunk(imap): 35 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  38 ] live chunk(imap): -- -- -- -- 16 -- -- -- -- -- -- 36 -- -- -- --
[  39 ]      [gu5,27] [kv6,141] -- -- -- -- -- --
[  40 ]      type:dir size:2 refs:2 ptrs: 29 39 -- -- -- -- -- --
[  41 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  42 ]      chunk(imap): 40 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  43 ]      chunk(imap): -- -- 26 -- -- -- -- -- -- -- -- -- -- 41 -- --
[  44 ]      [gu5,27] [kv6,141] [wg3,180] -- -- -- -- --
[  45 ]      type:dir size:2 refs:2 ptrs: 29 44 -- -- -- -- -- --
[  46 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  47 ]      chunk(imap): 45 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  48 ] live chunk(imap): -- -- -- -- 46 -- -- -- -- -- -- -- -- -- -- --
[  49 ] live [gu5,27] [kv6,141] [wg3,180] [og9,140] -- -- -- --
[  50 ] live type:dir size:2 refs:2 ptrs: 29 49 -- -- -- -- -- --
[  51 ] live type:reg size:0 refs:1 ptrs: -- -- -- -- -- -- -- --
[  52 ] live chunk(imap): 50 -- -- -- -- -- -- -- -- -- -- -- -- -- -- --
[  53 ] live chunk(imap): -- -- 26 -- -- -- -- -- -- -- -- -- 51 41 -- --
```

What does this say about the importance of choosing
inode numbers in a real LFS?

> It is better to sequentially allocate inode numbers because the whole blocks written out by the sequential policy is smaller than that by the random policy.

One last thing we’ve been assuming is that the LFS simulator always
updates the checkpoint region after each update. In the real
LFS, that isn’t the case: it is updated periodically to avoid long
seeks. Run `./lfs.py -N -i -o -s 1000` to see some operations
and the intermediate and final states of the file system when
the checkpoint region isn’t forced to disk. 

What would happen if the checkpoint region is never updated? 

> The file system would remain with only root directory.

What if it is updated periodically?

> Good.

Could you figure out how to recover the file system to the
latest state by rolling forward in the log?

> Read the next address of the checkpoint and check if the content is valid.
>
> Do the same thing again and again until an invalid block appears.
>
> The last valid imap table is the correct checkpoint.