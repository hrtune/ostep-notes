# Homework 22

This simulator, paging-policy.py, allows you to play around with different page-replacement policies. See the README for details. 

Questions 

1.. Generate random addresses with the following arguments: -s 0 -n 10, -s 1 -n 10, and -s 2 -n 10. Change the policy from FIFO, to LRU, to OPT. Compute whether each access in said address traces are hits or misses. 

```
$ python3 paging-policy.py -s 0 -n 10
ARG addresses -1
ARG addressfile
ARG numaddrs 10
ARG policy FIFO
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 0
ARG notrace False

Assuming a replacement policy of FIFO, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

"""
Access: 8  Miss [8, , ]
Access: 7  Miss [8,7, ]  
Access: 4  Miss [8,7,4]  
Access: 2  Miss [7,4,2]  
Access: 5  Miss [4,2,5]
Access: 7  Miss [2,5,7]
Access: 3  Miss [5,7,3]
Access: 4  Miss [7,3,4]
Access: 5  Miss [3,4,5]
"""

-----------------------------------------------
$ python3 python3 paging-policy.py -s 1 -n 10 -p LRU
ARG addresses -1
ARG addressfile 
ARG numaddrs 10
ARG policy LRU
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 1
ARG notrace False

Assuming a replacement policy of LRU, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 1  Miss [1, , ]
Access: 8  Miss [1,8, ]
Access: 7  Miss [1,8,7]
Access: 2  Miss [8,7,2]
Access: 4  Miss [7,2,4]
Access: 4  Hit  [7,2,4]
Access: 6  Miss [2,4,6]
Access: 7  Miss [4,6,7]
Access: 0  Miss [6,7,0]
Access: 0  Hit  [6,7,0]
------------------------------------------
$ python3 paging-policy.py -s 2 -n 10 -p OPT
ARG addresses -1
ARG addressfile 
ARG numaddrs 10
ARG policy OPT
ARG clockbits 2
ARG cachesize 3
ARG maxpage 10
ARG seed 2
ARG notrace False

Assuming a replacement policy of OPT, and a cache of size 3 pages,
figure out whether each of the following page references hit or miss
in the page cache.

Access: 9  Miss [9, , ]
Access: 9  Hit  [9, , ]
Access: 0  Miss [9,0, ]
Access: 0  Hit  [9,0, ]
Access: 8  Miss [9,0,8]
Access: 7  Miss [0,8,7]
Access: 6  Miss [8,7,6]
Access: 3  Miss [7,6,3]
Access: 6  Hit  [7,6,3]
Access: 6  Hit  [7,6,3]

```

2.. For a cache of size 5, generate worst-case address reference streams for each of the following policies: FIFO, LRU, and MRU (worst-case reference streams cause the most misses possible. For the worst case reference streams, how much bigger of a cache is needed to improve performance dramatically and approach OPT? 

> Just use a unique address for each access.

3.. Generate a random trace (use python or perl). How would you **expect** the different policies to perform on such a trace?

> 

4.. Now generate a trace with some locality. How can you generate such a trace? How does LRU perform on it? How much better than RAND is LRU? How does CLOCK do? How about CLOCK with different numbers of clock bits? 

5.. Use a program like valgrind to instrument a real application and generate a virtual page reference stream. For example, running valgrind --tool=lackey --trace-mem=yes ls will output a nearly-complete reference trace of every instruction and data reference made by the program ls. To make this useful for the simulator above, you’ll have to first transform each virtual memory reference into a virtual page-number reference (done by masking off the offset and shifting the resulting bits downward). How big of a cache is needed for your application trace in order to satisfy a large fraction of requests? Plot a graph of its working set as the size of the cache increases.

