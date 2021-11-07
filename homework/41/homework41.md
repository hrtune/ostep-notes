Homework
This section introduces ffs.py, a simple FFS simulator you can use
to understand better how FFS-based file and directory allocation work.
See the README for details on how to run the simulator.

## Questions

1, Examine the file `in.largefile`, and then run the simulator with
flag `-f in.largefile` and `-L 4`. The latter sets the **large file**
**exception** to 4 blocks in a group before moving on to the next one.
What do you think the file system allocation will look like? Then
run with `-c` enabled to see the actual layout.

```
(I think..)
group inodes    data
    0 /--------- ------------------------------
    1 a--------- aaaaaaaa----------------------
    2 a--------- aaaa--------------------------
    3 a--------- aaaa--------------------------
    4 a--------- aaaa--------------------------
    5 a--------- aaaa--------------------------
    6 a--------- aaaa--------------------------
    7 a--------- aaaa--------------------------
    8 a--------- aaaa--------------------------
    9 a--------- aaaa--------------------------
```

```
(The correct answer)
num_groups:       10
inodes_per_group: 10
blocks_per_group: 30

free data blocks: 259 (of 300)
free inodes:      98 (of 100)

spread inodes?    False
spread data?      False
contig alloc:     1

     00000000000000000000 1111111111 2222222222
     01234567890123456789 0123456789 0123456789

group inodes    data
    0 /a-------- /aaaa----- ---------- ----------
    1 ---------- aaaa------ ---------- ----------
    2 ---------- aaaa------ ---------- ----------
    3 ---------- aaaa------ ---------- ----------
    4 ---------- aaaa------ ---------- ----------
    5 ---------- aaaa------ ---------- ----------
    6 ---------- aaaa------ ---------- ----------
    7 ---------- aaaa------ ---------- ----------
    8 ---------- aaaa------ ---------- ----------
    9 ---------- aaaa------ ---------- ----------
```

> I forgot to use the group 0. I also forgot to put the root on the data section.

2, Now run with `-L 30`. What do you expect to see? Once again, turn
on -c to see if you were right. You can also use -S to see exactly
which blocks were allocated to the file /a.

```
(my answer is here)
group inodes    data
    0 /--------- /-----------------------------
    1 a--------- aaaaaaaaaaaaaaaaaaaaaaaaaaaaaa
    2 ---------- aaaaaaaaaa--------------------
    3 ---------- ------------------------------
    4 ---------- ------------------------------
    5 ---------- ------------------------------
    6 ---------- ------------------------------
    7 ---------- ------------------------------
    8 ---------- ------------------------------
    9 ---------- ------------------------------

```

```
(The correct answer)
num_groups:       10
inodes_per_group: 10
blocks_per_group: 30

free data blocks: 259 (of 300)
free inodes:      98 (of 100)

spread inodes?    False
spread data?      False
contig alloc:     1

     00000000000000000000 1111111111 2222222222
     01234567890123456789 0123456789 0123456789

group inodes    data
    0 /a-------- /aaaaaaaaa aaaaaaaaaa aaaaaaaaaa
    1 ---------- aaaaaaaaaa a--------- ----------
    2 ---------- ---------- ---------- ----------
    3 ---------- ---------- ---------- ----------
    4 ---------- ---------- ---------- ----------
    5 ---------- ---------- ---------- ----------
    6 ---------- ---------- ---------- ----------
    7 ---------- ---------- ---------- ----------
    8 ---------- ---------- ---------- ----------
    9 ---------- ---------- ---------- ----------
```

> I didn't understand the file 'a' reside in the root directory. So I should've put 'a' and root together.

Now we will compute some statistics about the file. The first is
something we call **filespan**, which is the max distance between any
two data blocks of the file or between the inode and any data block.
Calculate the filespan of /a. Run ffs.py -f `in.largefile` -L 4 -T -c to see what it is. 

```
$ python3 ffs.py -f in.largefile -L 4 -T -c

num_groups:       10
inodes_per_group: 10
blocks_per_group: 30

free data blocks: 259 (of 300)
free inodes:      98 (of 100)

spread inodes?    False
spread data?      False
contig alloc:     1

     00000000000000000000 1111111111 2222222222
     01234567890123456789 0123456789 0123456789

group inodes    data
    0 /a-------- /aaaa----- ---------- ----------
    1 ---------- aaaa------ ---------- ----------
    2 ---------- aaaa------ ---------- ----------
    3 ---------- aaaa------ ---------- ----------
    4 ---------- aaaa------ ---------- ----------
    5 ---------- aaaa------ ---------- ----------
    6 ---------- aaaa------ ---------- ----------
    7 ---------- aaaa------ ---------- ----------
    8 ---------- aaaa------ ---------- ----------
    9 ---------- aaaa------ ---------- ----------

span: files
  file:         /a  filespan: 372
               avg  filespan: 372.00
span: directories
  dir:           /  dirspan:  60
               avg  dirspan:  60.00
```

> The distance between a 'a' in inode and the last 'a' in group 9 

Do the same with -L 100. What difference
do you expect in filespan as the large-file exception parameter
changes from low values to high values?

> I expect 59 and the answer is the same 59
>
> If the  -L value is bigger, the filespan is smaller.

Now let’s look at a new input file, `in.manyfiles`. How do you
think the FFS policy will lay these files out across groups? (you can
run with -v to see what files and directories are created, or just cat
`in.manyfiles`). Run the simulator with -c to see if you were
right.

```
$ cat in.manyfiles

file /a 2
file /b 2
file /c 2
file /d 2
file /e 2
file /f 2
file /g 2
file /h 2
file /i 2

dir /j
dir /t

file /t/u 3
file /j/l 1
file /t/v 3
file /j/m 1
file /t/w 3
file /j/n 1
file /t/x 3
file /j/o 1
file /t/y 3
file /j/p 1
file /t/z 3
file /j/q 1
file /t/A 3
file /j/r 1
file /t/B 3
file /j/C 3
```

```
group inodes    data
    0 /abcdefghi /aabbccddeeffgghhii-----------
    1 jlmnopqrC- lmnopqrCCC--------------------
    2 tuvwxyzAB- uuuvvvwwwxxxyyyzzzAAABBB------
    3 ---------- ------------------------------
    4 ---------- ------------------------------
    5 ---------- ------------------------------
    6 ---------- ------------------------------
    7 ---------- ------------------------------
    8 ---------- ------------------------------
    9 ---------- ------------------------------


```

> I was wrong because the file C belongs to the j instead of t. This is not fair.

A new metric we will use to evaluate FFS is called dirspan. This
metric calculates the spread of files within a particular directory,
specifically the max distance between the inodes and data blocks of
all the files in the directory as well as the inode and data block of
the directory itself. Run with in.manyfiles and the -T flag, and
see if you can figure out the dirspan of the three directories. Run
with -c to see if you were right. How good of a job does FFS do in
minimizing dirspan?

```
(-f in.manyfiles -T)
dirspan of...
	/ is 28
	j is 20
	t is 34

```

> Correct.

Now change the size of the inode table per group to 5 (-i 5). How
do you think this will change the layout of the files? Run with -c
to see if you were right. How does it affect the dirspan?



```
$ cat in.manyfiles

file /a 2
file /b 2
file /c 2
file /d 2
file /e 2
file /f 2
file /g 2
file /h 2
file /i 2

dir /j
dir /t

file /t/u 3
file /j/l 1
file /t/v 3
file /j/m 1
file /t/w 3
file /j/n 1
file /t/x 3
file /j/o 1
file /t/y 3
file /j/p 1
file /t/z 3
file /j/q 1
file /t/A 3
file /j/r 1
file /t/B 3
file /j/C 3
```

```
group inodes    data
    0 /abcd /aabbccdd---------------------
    1 efghi eeffgghhii--------------------
    2 jlmno jlmno-------------------------
    3 pqrC- pqrCCC------------------------
    4 tuvwx tuuuvvvwwwxxx-----------------
    5 yzAB- yyyzzzAAABBB------------------
    6 ----- ------------------------------
    7 ----- ------------------------------
    8 ----- ------------------------------
    9 ----- ------------------------------

(The correct answer)
group inodedata
    0 /abcd /aabbccdd- ---------- ----------
    1 efghi eeffgghhii ---------- ----------
    2 jlmno jlmno----- ---------- ----------
    3 tuvwx tuuuvvvwww xxx------- ----------
    4 ypzqA yyypzzzqAA A--------- ----------
    5 rBC-- rBBBCCC--- ---------- ----------
    6 ----- ---------- ---------- ----------
    7 ----- ---------- ---------- ----------
    8 ----- ---------- ---------- ----------
    9 ----- ---------- ---------- ----------
```

```
dirspan of...
	/ is 49
	j is 116
	t is 78
	average is 81
```

> This result of dirspan is bigger than that of the bigger inode table.

One policy that can affect FFS effectiveness is which group to place
the inode of a new directory in. The default policy (in the simulator)
simply looks for the group with the most free inodes. A slightly
different policy, specified with `-A`, looks for a group of groups with
the most free inodes. For example, if you run with `-A 2`, when allocating
a new directory, the simulator will look at groups in pairs and pick the best pair for the allocation. Now you should run `./ffs.py -f in.manyfiles -i 5 -A 2 -c` to see how allocation changes with this strategy. 

```
$ python3 ffs.py -f in.manyfiles -i 5 -A 2 -c

group inodedata
    0 /abcd /aabbccdd- ---------- ----------
    1 efghi eeffgghhii ---------- ----------
    2 jlmno jlmno----- ---------- ----------
    3 pqrC- pqrCCC---- ---------- ----------
    4 tuvwx tuuuvvvwww xxx------- ----------
    5 yzAB- yyyzzzAAAB BB-------- ----------
    6 ----- ---------- ---------- ----------
    7 ----- ---------- ---------- ----------
    8 ----- ---------- ---------- ----------
    9 ----- ---------- ---------- ----------
```

How does it affect dirspan? 

```
span: directories
  dir:           /  dirspan:  49
  dir:          /j  dirspan:  45
  dir:          /t  dirspan:  51
               avg  dirspan:  48.33
```

> The average is smaller than that with no option.

Why might this policy be a good idea?

> This is because the files which belongs to the same directory is put into contiguous groups.

One last policy change we will explore relates to file fragmentation.
Run `./ffs.py -f in.fragmented -v` and see if you can predict
how the files that remain are allocated. 

```
$ cat in.fragmented
file /a 1
file /b 1
file /c 1
file /d 1
file /e 1
file /f 1
file /g 1
file /h 1
delete /a
delete /c
delete /e
delete /g
file /i 8
```

Run with -c to confirm
your answer. 

```
group inodes    data
    0 /ib-d-f-h- /ibidifihiiii-----------------
    1 ---------- ------------------------------
    2 ---------- ------------------------------
    3 ---------- ------------------------------
    4 ---------- ------------------------------
    5 ---------- ------------------------------
    6 ---------- ------------------------------
    7 ---------- ------------------------------
    8 ---------- ------------------------------
    9 ---------- ------------------------------

```

What is interesting about the data layout of file /i?
Why is it problematic?

> The file i is fragmented. So the file 'i' takes more time to access than that is not fragmented.

A new policy, which we call contiguous allocation and enabled with
the -C flag, tries to ensure that each file is allocated contiguously.
Specifically, with -C n, the file system tries to ensure that n contiguous
blocks are free within a group before allocating a block.
Run `./ffs.py -f in.fragmented -v -C 2 -c` to see the difference
in layout. 

```
group inodes    data
    0 /ib-d-f-h- /-b-d-f-hi iiiiiii--- ----------
    1 ---------- ---------- ---------- ----------
    2 ---------- ---------- ---------- ----------
    3 ---------- ---------- ---------- ----------
    4 ---------- ---------- ---------- ----------
    5 ---------- ---------- ---------- ----------
    6 ---------- ---------- ---------- ----------
    7 ---------- ---------- ---------- ----------
    8 ---------- ---------- ---------- ----------
    9 ---------- ---------- ---------- ----------
```

How does layout change as the parameter passed
to -C increases? 

> As -C increases, each fragmented pieces gets bigger.

Finally, how does -C affect filespan and dirspan?

> The filespan gets smaller as the -C increases.
>
> The dirspan gets bigger as the -C increases.

