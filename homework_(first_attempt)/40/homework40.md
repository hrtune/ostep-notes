# Homework 40

Use this tool, `vsfs.py`, to study how file system state changes as various
operations take place. The file system begins in an empty state, with
just a root directory. As the simulation takes place, various operations are
performed, thus slowly changing the on-disk state of the file system. See
the README for details.

Questions

1, Run the simulator with some different random seeds (say 17, 18, 19,
20), and see if you can figure out which operations must have taken
place between each state change.

```
Reading README.md works well for understanding it.
```

```sh
$ python3 vsfs.py -s 17

Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

mkdir("/u")

inode bitmap  11000000
inodes       [d a:0 r:3][d a:1 r:2][][][][][][]
data bitmap   11000000
data         [(.,0) (..,0) (u,1)][(.,1) (..,0)][][][][][][]

creat("/a")

inode bitmap  11100000
inodes       [d a:0 r:3][d a:1 r:2][f a:-1 r:1][][][][][]
data bitmap   11000000
data         [(.,0) (..,0) (u,1) (a,2)][(.,1) (..,0)][][][][][][]

unlink("/a")

inode bitmap  11000000
inodes       [d a:0 r:3][d a:1 r:2][][][][][][]
data bitmap   11000000
data         [(.,0) (..,0) (u,1)][(.,1) (..,0)][][][][][][]

mkdir("/z")

inode bitmap  11100000
inodes       [d a:0 r:4][d a:1 r:2][d a:2 r:2][][][][][]
data bitmap   11100000
data         [(.,0) (..,0) (u,1) (z,2)][(.,1) (..,0)][(.,2) (..,0)][][][][][]

mkdir("/s")

inode bitmap  11110000
inodes       [d a:0 r:5][d a:1 r:2][d a:2 r:2][d a:3 r:2][][][][]
data bitmap   11110000
data         [(.,0) (..,0) (u,1) (z,2) (s,3)][(.,1) (..,0)][(.,2) (..,0)][(.,3) (..,0)][][][][]

creat("/z/x")

inode bitmap  11111000
inodes       [d a:0 r:5][d a:1 r:2][d a:2 r:2][d a:3 r:2][f a:-1 r:1][][][]
data bitmap   11110000
data         [(.,0) (..,0) (u,1) (z,2) (s,3)][(.,1) (..,0)][(.,2) (..,0) (x,4)][(.,3) (..,0)][][][][]

link("/z/x", "/u/b")

inode bitmap  11111000
inodes       [d a:0 r:5][d a:1 r:2][d a:2 r:2][d a:3 r:2][f a:-1 r:2][][][]
data bitmap   11110000
data         [(.,0) (..,0) (u,1) (z,2) (s,3)][(.,1) (..,0) (b,4)][(.,2) (..,0) (x,4)][(.,3) (..,0)][][][][]

unlink("/u/b")

inode bitmap  11111000
inodes       [d a:0 r:5][d a:1 r:2][d a:2 r:2][d a:3 r:2][f a:-1 r:1][][][]
data bitmap   11110000
data         [(.,0) (..,0) (u,1) (z,2) (s,3)][(.,1) (..,0)][(.,2) (..,0) (x,4)][(.,3) (..,0)][][][][]

fd=open("/z/x", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd)

inode bitmap  11111000
inodes       [d a:0 r:5][d a:1 r:2][d a:2 r:2][d a:3 r:2][f a:4 r:1][][][]
data bitmap   11111000
data         [(.,0) (..,0) (u,1) (z,2) (s,3)][(.,1) (..,0)][(.,2) (..,0) (x,4)][(.,3) (..,0)][v][][][]

creat("/u/b");

inode bitmap  11111100
inodes       [d a:0 r:5][d a:1 r:2][d a:2 r:2][d a:3 r:2][f a:4 r:1][f a:-1 r:1][][]
data bitmap   11111000
data         [(.,0) (..,0) (u,1) (z,2) (s,3)][(.,1) (..,0) (b,5)][(.,2) (..,0) (x,4)][(.,3) (..,0)][v][][][]
```

2, Now do the same, using different random seeds (say 21, 22, 23,
24), except run with the -r flag, thus making you guess the state
change while being shown the operation. What can you conclude
about the inode and data-block allocation algorithms, in terms of
which blocks they prefer to allocate?

```sh
Initial state

inode bitmap  10000000
inodes       [d a:0 r:2][][][][][][][]
data bitmap   10000000
data         [(.,0) (..,0)][][][][][][][]

mkdir("/o");

inode bitmap  11000000
inodes       [d a:0 r:3][d a:1 r:1][][][][][][]
data bitmap   11000000
data         [(.,0) (..,0) (o,1)][(.,1) (..,0)][][][][][][]

creat("/b");

inode bitmap  11100000
inodes       [d a:0 r:3][d a:1 r:1][f a:-1 r:1][][][][][]
data bitmap   11000000
data         [(.,0) (..,0) (o,1) (b,2)][(.,1) (..,0)][][][][][][]

creat("/o/q");

inode bitmap  11110000
inodes       [d a:0 r:3][d a:1 r:1][f a:-1 r:1][f a:-1 r:1][][][][]
data bitmap   11000000
data         [(.,0) (..,0) (o,1) (b,2)][(.,1) (..,0) (q,3)][][][][][][]

fd=open("/b", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11110000
inodes       [d a:0 r:3][d a:1 r:1][f a:2 r:1][f a:-1 r:1][][][][]
data bitmap   11100000
data         [(.,0) (..,0) (o,1) (b,2)][(.,1) (..,0) (q,3)][u][][][][][]

fd=open("/o/q", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11110000
inodes       [d a:0 r:3][d a:1 r:1][f a:2 r:1][f a:3 r:1][][][][]
data bitmap   11110000
data         [(.,0) (..,0) (o,1) (b,2)][(.,1) (..,0) (q,3)][u][v][][][][]

creat("/o/j");

inode bitmap  11111000
inodes       [d a:0 r:3][d a:1 r:1][f a:2 r:1][f a:3 r:1][f a:-1 r:1][][][]
data bitmap   11110000
data         [(.,0) (..,0) (o,1) (b,2)][(.,1) (..,0) (q,3) (j,4)][u][v][][][][]

unlink("/b");

inode bitmap  11011000
inodes       [d a:0 r:3][d a:1 r:1][][f a:3 r:1][f a:-1 r:1][][][]
data bitmap   11010000
data         [(.,0) (..,0) (o,1)][(.,1) (..,0) (q,3) (j,4)][][v][][][][]

fd=open("/o/j", O_WRONLY|O_APPEND); write(fd, buf, BLOCKSIZE); close(fd);

inode bitmap  11011000
inodes       [d a:0 r:3][d a:1 r:1][][f a:3 r:1][f a:2 r:1][][][]
data bitmap   11110000
data         [(.,0) (..,0) (o,1)][(.,1) (..,0) (q,3) (j,4)][u][v][][][][]


creat("/o/x");

inode bitmap  11111000
inodes       [d a:0 r:3][d a:1 r:1][f a:-1 r:1][f a:3 r:1][f a:2 r:1][][][]
data bitmap   11110000
data         [(.,0) (..,0) (o,1)][(.,1) (..,0) (q,3) (j,4) (x,2)][u][v][][][][]

mkdir("/o/t");

inode bitmap  11111100
inodes       [d a:0 r:3][d a:1 r:3][f a:-1 r:1][f a:3 r:1][f a:2 r:1][d a:4 r:2][][]
data bitmap   11111000
data         [(.,0) (..,0) (o,1)][(.,1) (..,0) (q,3) (j,4) (x,2) (t,5)][u][v][(.,5) (..,1)][][][]
```

3, Now reduce the number of data blocks in the file system, to very
low numbers (say two), and run the simulator for a hundred or so
requests. What types of files end up in the file system in this highly constrained
layout? What types of operations would fail?

> Making directory or writing file would fail.

4, Now do the same, but with inodes. With very few inodes, what
types of operations can succeed? 

> No operations succeed.

- Which will usually fail?

  > Creating file or making directory fails.

- What is the final state of the file system likely to be?

  > It ends up with the initial state.

