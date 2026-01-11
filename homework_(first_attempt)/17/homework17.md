Homework

The program, malloc.py, lets you explore the behavior of a simple free-space allocator as described in the chapter. See the README for details of its basic operation. 

Questions 

1 First run with the flags -n 10 -H 0 -p BEST -s 0 to generate a few random allocations and frees. Can you predict what alloc()/free() will return? Can you guess the state of the free list after each request? What do you notice about the free list over time? 

```
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1 (no align)
policy BEST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList
compute False

ptr[0] = Alloc(3) returned 1000
List[1003, 97]

Free(ptr[0])
returned 0
List [1000, 3],[1003, 97]

ptr[1] = Alloc(5) returned 1003
List [1000,3],[1008, 92]

Free(ptr[1])
returned 0
List[1000,3],[1003, 5],[1008, 92]

ptr[2] = Alloc(8) returned 1008
List[1000,3],[1003, 5],[1016, 84]

Free(ptr[2])
returned 0
List[1000,3],[1003, 5],[1008, 8],[1016, 84]

ptr[3] = Alloc(8) returned 1008
List[1000,3],[1003, 5],[1016, 84]

Free(ptr[3])
returned 0
List[1000,3],[1003, 5],[1008, 8],[1016, 84]

ptr[4] = Alloc(2) returned 1000
List[1002,1],[1003, 5],[1008, 8],[1016, 84]

ptr[5] = Alloc(7) returned 1008
List[1002,1],[1003, 5],[1015,1],[1016, 84]
```

> Entries of the free list is getting bigger as the alloc() and the free() invoked.

2 How are the results different when using a WORST fit policy to search the free list (-p WORST)? What changes? 

```
$ python3 malloc.py -n 10 -H 0 -p WORST -s 0 -c
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy WORST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList
compute True

ptr[0] = Alloc(3) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1003 sz:97 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003 (searched 2 elements)
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1016 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1024 sz:76 ]

Free(ptr[3])
returned 0
Free List [ Size 5 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1024 sz:76 ]

ptr[4] = Alloc(2) returned 1024 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1026 sz:74 ]

ptr[5] = Alloc(7) returned 1026 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:8 ][ addr:1033 sz:67 ]
```

> The free list size is bigger however it seems the size of each entry is bigger except for the last segment.

3 What about when using FIRST fit (-p FIRST)? What speeds up when you use first fit? 

```
$ python3 malloc.py -n 10 -H 0 -p FIRST -s 0 -c
s 0 -c
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy FIRST
listOrder ADDRSORT
coalesce False
numOps 10
range 10
percentAlloc 50
allocList
compute True

ptr[0] = Alloc(3) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1003 sz:97 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003 (searched 2 elements)
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[3])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1000 (searched 1 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[5] = Alloc(7) returned 1008 (searched 3 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]
```

> The WORST HIT algorithm searched 20 elements as a whole.
>
> The FIRST HIT algorithm searched 13 elements as a whole.
>
> I conclude the FIRST HIT is faster almost 50% than the WORST HIT.

4 For the above questions, how the list is kept ordered can affect the time it takes to find a free location for some of the policies. Use the different free list orderings (-l ADDRSORT, -l SIZESORT+, -l SIZESORT-) to see how the policies and the list orderings interact. 

|           | ADDRSORT | SIZESORT+ | SIZESORT- |
| --------- | -------- | --------- | --------- |
| FIRST HIT | 13       | 13        | 6         |
| BEST HIT  | 18       | 18        | 18        |
| WORST HIT | 20       | 20        | 20        |

> The orderings do not affect number of the searched elements if you choose the BEST HIT and the WORST HIT.
>
> However, if you choose the FIRST HIT, the SIZESORT- is the best ordering of the free list.

5 Coalescing of a free list can be quite important. Increase the number of random allocations (say to -n 1000). What happens to larger allocation requests over time? Run with and without coalescing (i.e., without and with the -C flag). What differences in outcome do you see? How big is the free list over time in each case? Does the ordering of the list matter in this case? 

|                | ADDRSORT | SIZESORT+ | SIZESORT- |
| -------------- | -------- | --------- | --------- |
| FIRST HIT      | 4        | 4         | 5         |
| FIRST HIT (-C) | 1        | 1         | 4         |
| BEST HIT       | 4        | 4         | 4         |
| BEST HIT (-C)  | 1        | 1         | 4         |
| WORST HIT      | 5        | 5         | 5         |
| WORST HIT (-C) | 1        | 1         | 4         |

> It seems SIZESORT- is the worst ordering for all hit algorithm.

6 What happens when you change the percent allocated fraction -P to higher than 50? What happens to allocations as it nears 100? What about as it nears 0? 

```
(-P 50)
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 20
range 10
percentAlloc 50
allocList
compute True

ptr[0] = Alloc(3) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1003 sz:97 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003 (searched 2 elements)
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:92 ]

ptr[2] = Alloc(8) returned 1008 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[3] = Alloc(8) returned 1008 (searched 4 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1016 sz:84 ]

Free(ptr[3])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[4] = Alloc(2) returned 1000 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[5] = Alloc(7) returned 1008 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

Free(ptr[5])
returned 0
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

ptr[6] = Alloc(9) returned 1016 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1025 sz:75 ]

ptr[7] = Alloc(9) returned 1025 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1034 sz:66 ]

Free(ptr[4])
returned 0
Free List [ Size 6 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1034 sz:66 ]

Free(ptr[6])
returned 0
Free List [ Size 7 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1016 sz:9 ][ addr:1034 sz:66 ]

Free(ptr[7])
returned 0
Free List [ Size 8 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1016 sz:9 ][ addr:1025 sz:9 ][ addr:1034 sz:66 ]

ptr[8] = Alloc(5) returned 1003 (searched 8 elements)
Free List [ Size 7 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1016 sz:9 ][ addr:1025 sz:9 ][ addr:1034 sz:66 ]

Free(ptr[8])
returned 0
Free List [ Size 8 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1016 sz:9 ][ addr:1025 sz:9 ][ addr:1034 sz:66 ]

ptr[9] = Alloc(9) returned 1016 (searched 8 elements)
Free List [ Size 7 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1025 sz:9 ][ addr:1034 sz:66 ]

ptr[10] = Alloc(6) returned 1008 (searched 7 elements)
Free List [ Size 7 ]: [ addr:1000 sz:2 ][ addr:1002 sz:1 ][ addr:1003 sz:5 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1025 sz:9 ][ addr:1034 sz:66 ]

(-P 75)
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 20
range 10
percentAlloc 75
allocList
compute True

ptr[0] = Alloc(3) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1003 sz:97 ]

ptr[1] = Alloc(5) returned 1003 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1008 sz:92 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1008 sz:92 ]

ptr[2] = Alloc(6) returned 1008 (searched 2 elements)
Free List [ Size 2 ]: [ addr:1000 sz:3 ][ addr:1014 sz:86 ]

Free(ptr[2])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:86 ]

ptr[3] = Alloc(8) returned 1014 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1008 sz:6 ][ addr:1022 sz:78 ]

ptr[4] = Alloc(3) returned 1000 (searched 3 elements)
Free List [ Size 2 ]: [ addr:1008 sz:6 ][ addr:1022 sz:78 ]

Free(ptr[4])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1008 sz:6 ][ addr:1022 sz:78 ]

Free(ptr[3])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:8 ][ addr:1022 sz:78 ]

ptr[5] = Alloc(8) returned 1014 (searched 4 elements)
Free List [ Size 3 ]: [ addr:1000 sz:3 ][ addr:1008 sz:6 ][ addr:1022 sz:78 ]

Free(ptr[5])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:8 ][ addr:1022 sz:78 ]

ptr[6] = Alloc(2) returned 1000 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1008 sz:6 ][ addr:1014 sz:8 ][ addr:1022 sz:78 ]

ptr[7] = Alloc(7) returned 1014 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1002 sz:1 ][ addr:1008 sz:6 ][ addr:1021 sz:1 ][ addr:1022 sz:78 ]

Free(ptr[7])
returned 0
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1008 sz:6 ][ addr:1014 sz:7 ][ addr:1021 sz:1 ][ addr:1022 sz:78 ]

ptr[8] = Alloc(9) returned 1022 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1008 sz:6 ][ addr:1014 sz:7 ][ addr:1021 sz:1 ][ addr:1031 sz:69 ]

ptr[9] = Alloc(9) returned 1031 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1008 sz:6 ][ addr:1014 sz:7 ][ addr:1021 sz:1 ][ addr:1040 sz:60 ]

ptr[10] = Alloc(1) returned 1002 (searched 5 elements)
Free List [ Size 4 ]: [ addr:1008 sz:6 ][ addr:1014 sz:7 ][ addr:1021 sz:1 ][ addr:1040 sz:60 ]

ptr[11] = Alloc(4) returned 1008 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1012 sz:2 ][ addr:1014 sz:7 ][ addr:1021 sz:1 ][ addr:1040 sz:60 ]

Free(ptr[10])
returned 0
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1012 sz:2 ][ addr:1014 sz:7 ][ addr:1021 sz:1 ][ addr:1040 sz:60 ]

ptr[12] = Alloc(5) returned 1014 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1002 sz:1 ][ addr:1012 sz:2 ][ addr:1019 sz:2 ][ addr:1021 sz:1 ][ addr:1040 sz:60 ]

(-P 100)
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 20
range 10
percentAlloc 100
allocList
compute True

ptr[0] = Alloc(8) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1008 sz:92 ]

ptr[1] = Alloc(3) returned 1008 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1011 sz:89 ]

ptr[2] = Alloc(5) returned 1011 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1016 sz:84 ]

ptr[3] = Alloc(4) returned 1016 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1020 sz:80 ]

ptr[4] = Alloc(6) returned 1020 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1026 sz:74 ]

ptr[5] = Alloc(6) returned 1026 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1032 sz:68 ]

ptr[6] = Alloc(8) returned 1032 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1040 sz:60 ]

ptr[7] = Alloc(3) returned 1040 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1043 sz:57 ]

ptr[8] = Alloc(10) returned 1043 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1053 sz:47 ]

ptr[9] = Alloc(10) returned 1053 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1063 sz:37 ]

ptr[10] = Alloc(8) returned 1063 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1071 sz:29 ]

ptr[11] = Alloc(7) returned 1071 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1078 sz:22 ]

ptr[12] = Alloc(2) returned 1078 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1080 sz:20 ]

ptr[13] = Alloc(7) returned 1080 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1087 sz:13 ]

ptr[14] = Alloc(10) returned 1087 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1097 sz:3 ]

ptr[15] = Alloc(9) returned -1 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1097 sz:3 ]

ptr[16] = Alloc(9) returned -1 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1097 sz:3 ]

ptr[17] = Alloc(1) returned 1097 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1098 sz:2 ]

ptr[18] = Alloc(4) returned -1 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1098 sz:2 ]

ptr[19] = Alloc(7) returned -1 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1098 sz:2 ]

(-P 10)
seed 0
size 100
baseAddr 1000
headerSize 0
alignment -1
policy BEST
listOrder ADDRSORT
coalesce False
numOps 20
range 10
percentAlloc 10
allocList
compute True

ptr[0] = Alloc(8) returned 1000 (searched 1 elements)
Free List [ Size 1 ]: [ addr:1008 sz:92 ]

Free(ptr[0])
returned 0
Free List [ Size 2 ]: [ addr:1000 sz:8 ][ addr:1008 sz:92 ]

ptr[1] = Alloc(5) returned 1000 (searched 2 elements)
Free List [ Size 2 ]: [ addr:1005 sz:3 ][ addr:1008 sz:92 ]

Free(ptr[1])
returned 0
Free List [ Size 3 ]: [ addr:1000 sz:5 ][ addr:1005 sz:3 ][ addr:1008 sz:92 ]

ptr[2] = Alloc(4) returned 1000 (searched 3 elements)
Free List [ Size 3 ]: [ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:92 ]

Free(ptr[2])
returned 0
Free List [ Size 4 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:92 ]

ptr[3] = Alloc(8) returned 1008 (searched 4 elements)
Free List [ Size 4 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1016 sz:84 ]

Free(ptr[3])
returned 0
Free List [ Size 5 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:8 ][ addr:1016 sz:84 ]

ptr[4] = Alloc(7) returned 1008 (searched 5 elements)
Free List [ Size 5 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

Free(ptr[4])
returned 0
Free List [ Size 6 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:7 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

ptr[5] = Alloc(6) returned 1008 (searched 6 elements)
Free List [ Size 6 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

Free(ptr[5])
returned 0
Free List [ Size 7 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:84 ]

ptr[6] = Alloc(7) returned 1016 (searched 7 elements)
Free List [ Size 7 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1023 sz:77 ]

Free(ptr[6])
returned 0
Free List [ Size 8 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]

ptr[7] = Alloc(1) returned 1004 (searched 8 elements)
Free List [ Size 7 ]: [ addr:1000 sz:4 ][ addr:1005 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]

Free(ptr[7])
returned 0
Free List [ Size 8 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:6 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]

ptr[8] = Alloc(5) returned 1008 (searched 8 elements)
Free List [ Size 8 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1013 sz:1 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]

Free(ptr[8])
returned 0
Free List [ Size 9 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:3 ][ addr:1008 sz:5 ][ addr:1013 sz:1 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]

ptr[9] = Alloc(2) returned 1005 (searched 9 elements)
Free List [ Size 9 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1007 sz:1 ][ addr:1008 sz:5 ][ addr:1013 sz:1 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]

Free(ptr[9])
returned 0
Free List [ Size 10 ]: [ addr:1000 sz:4 ][ addr:1004 sz:1 ][ addr:1005 sz:2 ][ addr:1007 sz:1 ][ addr:1008 sz:5 ][ addr:1013 sz:1 ][ addr:1014 sz:1 ][ addr:1015 sz:1 ][ addr:1016 sz:7 ][ addr:1023 sz:77 ]
```

> The smaller -P value, the bigger fragmentation of the free list.

7 What kind of specific requests can you make to generate a highly-fragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.

```sh
$ python3 malloc.py -H 0 -p BEST -c -A +10,-0,+9,-1,+8,-2,+7,-3,+6,-4,+5,-5,+4,-6...
```

