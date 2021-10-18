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

7 What kind of specific requests can you make to generate a highly-fragmented free space? Use the -A flag to create fragmented free lists, and see how different policies and options change the organization of the free list.