# Homework

This section introduces `raid.py`, a simple RAID simulator you can
use to shore up your knowledge of how RAID systems work. See the
README for details.



## Questions

```
(Template for answers)
read  [disk ?, offset ?]
write  [disk ?, offset ?]
```

Template for Mapping

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             |      |      |      |      |
| 1             |      |      |      |      |
| 2             |      |      |      |      |
| 3             |      |      |      |      |

1, Use the simulator to perform some basic RAID mapping tests. Run
with different levels (0, 1, 4, 5) and see if you can figure out the
mappings of a set of requests. For RAID-5, see if you can figure out
the difference between **left-symmetric** and **left-asymmetric** layouts.
Use some different random seeds to generate different problems
than above.

```
> python3 raid.py -L 0 -s 0 -n 5 -R 20

16 1
LOGICAL READ from addr:16 size:4096
  read  [disk 0, offset 4]

8 1
LOGICAL READ from addr:8 size:4096
  read  [disk 0, offset 2]

10 1
LOGICAL READ from addr:10 size:4096
  read  [disk 2, offset 2]

15 1
LOGICAL READ from addr:15 size:4096
  read  [disk 3, offset 3]

9 1
LOGICAL READ from addr:9 size:4096
  read  [disk 1, offset 2]
```

###### Raid 0 Mapping

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             | 0    | 1    | 2    | 3    |
| 1             | 4    | 5    | 6    | 7    |
| 2             | 8    | 9    | 10   | 11   |
| 3             | 12   | 13   | 14   | 15   |

###### Raid 1 Mapping

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             | 0    | 0    | 1    | 1    |
| 1             | 2    | 2    | 3    | 3    |
| 2             | 4    | 4    | 5    | 5    |
| 3             | 6    | 6    | 7    | 7    |

###### Raid 4 Mapping

| Offset \ Disk | 0    | 1    | 2    | 3    | P    |
| ------------- | ---- | ---- | ---- | ---- | ---- |
| 0             | 0    | 1    | 2    | 3    | P0   |
| 1             | 4    | 5    | 6    | 7    | P1   |
| 2             | 8    | 9    | 10   | 11   | P2   |
| 3             | 12   | 13   | 14   | 15   | P3   |

###### Raid 5 LS Mapping

| Offset \ Disk | 0    | 1    | 2    | 3    | 4    |
| ------------- | ---- | ---- | ---- | ---- | ---- |
| 0             | 0    | 1    | 2    | 3    | P0   |
| 1             | 5    | 6    | 7    | P1   | 4    |
| 2             | 10   | 11   | P2   | 8    | 9    |
| 3             | 15   | P3   | 12   | 13   | 14   |
| 4             | P4   | 16   | 17   | 18   | 19   |

###### Raid 5 LA Mapping

| Offset \ Disk | 0    | 1    | 2    | 3    | 4    |
| ------------- | ---- | ---- | ---- | ---- | ---- |
| 0             | 0    | 1    | 2    | 3    | P0   |
| 1             | 4    | 5    | 6    | P1   | 7    |
| 2             | 8    | 9    | P2   | 10   | 11   |
| 3             | 12   | P3   | 13   | 14   | 15   |
| 4             | P4   | 16   | 17   | 18   | 19   |

2, Do the same as the first problem, but this time vary the chunk size
with -C. How does chunk size change the mappings?

###### Raid 0 (-C 8192)

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             | 0    | 2    | 4    | 6    |
| 1             | 1    | 3    | 5    | 7    |
| 2             | 8    | 10   | 12   | 14   |
| 3             | 9    | 11   | 13   | 15   |
| 4             | 16   | 18   | 20   | 22   |

###### Raid 1 (-C 8192)

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             | 0    | 0    | 2    | 2    |
| 1             | 1    | 1    | 3    | 3    |
| 2             | 4    | 4    | 6    | 6    |
| 3             | 5    | 5    | 7    | 7    |
| 4             | 8    | 8    | 10   | 10   |

###### Raid 4 (-C 8192)

| Offset \ Disk | 0    | 1    | 2    | 3    | P    |
| ------------- | ---- | ---- | ---- | ---- | ---- |
| 0             | 0    | 2    | 4    | 6    | P0   |
| 1             | 1    | 3    | 5    | 7    | P1   |
| 2             | 8    | 10   | 12   | 14   | P2   |
| 3             | 9    | 11   | 13   | 15   | P3   |
| 4             | 16   | 18   | 20   | 22   | P4   |

###### Raid 5 LS (-C 8192)

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             | 0    | 2    | 4    | P0   |
| 1             | 1    | 3    | 5    | P1   |
| 2             | 8    | 10   | P2   | 6    |
| 3             | 9    | 11   | P3   | 7    |
| 4             | 16   | P4   | 12   | 14   |

###### Raid 5 LA (-C 8192)

| Offset \ Disk | 0    | 1    | 2    | 3    |
| ------------- | ---- | ---- | ---- | ---- |
| 0             | 0    | 2    | 4    | P0   |
| 1             | 1    | 3    | 5    | P1   |
| 2             | 6    | 8    | P2   | 10   |
| 3             | 7    | 9    | P3   | 11   |
| 4             | 12   | P4   | 14   | 16   |
| 5             | 13   | P5   | 15   | 17   |
| 6             | P6   | 18   | 20   | 22   |
| 7             | P7   | 19   | 21   | 23   |

3, Do the same as above, but use the -r flag to reverse the nature of
each problem.

> I mapped so this is easy.

4, Now use the reverse flag but increase the size of each request with
the -S flag. Try specifying sizes of 8k, 12k, and 16k, while varying
the RAID level. What happens to the underlying I/O pattern when
the size of the request increases? Make sure to try this with the
sequential workload too (-W sequential); for what request sizes
are RAID-4 and RAID-5 much more I/O efficient?

5, Use the timing mode of the simulator (-t) to estimate the performance
of 100 random reads to the RAID, while varying the RAID
levels, using 4 disks.

6, Do the same as above, but increase the number of disks. How does
the performance of each RAID level scale as the number of disks
increases?

| RAID \ Disks | 4     | 8     | 16    | 32   |
| ------------ | ----- | ----- | ----- | ---- |
| 0            | 275.7 | 156.5 | 86.8  | 58.6 |
| 1            | 278.7 | 167.8 | 92.8  | 76.7 |
| 4            | 386.1 | 165.0 | 115.4 | 71.5 |
| 5            | 276.7 | 158.6 | 87.2  | 59.7 |

> Raid 5 looks pretty good.

7, Do the same as above, but use all writes (-w 100) instead of reads.
How does the performance of each RAID level scale now? Can you
do a rough estimate of the time itwill take to complete theworkload
of 100 random writes?

| RAID \ Disks | 4     | 8     | 16    | 32    |
| ------------ | ----- | ----- | ----- | ----- |
| 0            | 275.7 | 156.5 | 86.8  | 58.6  |
| 1            | 509.8 | 275.7 | 156.5 | 86.8  |
| 4            | 982.5 | 937.8 | 854.9 | 706.9 |
| 5            | 497.4 | 290.9 | 165.7 | 84.9  |

> Raid 0 do the best on write performance.
>
> On the other hand, the terrible performance is achieved by Raid 4.
>
> With increasing disks, the Raid 5 do better performance.

8, Run the timing mode one last time, but this time with a sequential
workload (-W seq). How does the performance vary
with RAID level, and when doing reads versus writes? How about
when varying the size of each request? What size should you write
to a RAID when using RAID-4 or RAID-5?

| Raid \ Requests | 10 (Read) | 10 (Write) | 100 (Read) | 100 (Write) | 1000 (Read) | 1000 (Write) |
| --------------- | --------- | ---------- | ---------- | ----------- | ----------- | ------------ |
| 0 (4 disks)     | 10.3      | 10.3       | 12.5       | 12.5        | 35          | 35           |
| 0 (32 disks)    | 10.1      | 10.1       | 10.4       | 10.4        | 13.2        | 13.2         |
| 1 (4 disks)     | 10.5      | 10.5       | 14.9       | 15.0        | 59.9        | 60.0         |
| 1 (32 disks)    | 10.1      | 10.1       | 10.7       | 10.7        | 16.3        | 16.3         |
| 4 (4 disks)     | 10.4      | 10.4       | 13.4       | 13.4        | 43.4        | 43.4         |
| 4 (32 disks)    | 10.1      | 10.1       | 10.4       | 10.4        | 13.3        | 13.3         |
| 5 (4 disks)     | 10.4      | 10.4       | 13.3       | 13.4        | 43.3        | 43.4         |
| 5 (32 disks)    | 10.1      | 10.1       | 10.4       | 10.4        | 13.3        | 13.3         |

