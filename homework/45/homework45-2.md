# Homework (Code)

In this part of the homework, you’ll write some of your own code to
implement various checksums.

### Questions

Write a short C program (called `check-xor.c`) that computes an
XOR-based checksum over an input file, and prints the checksum as
output. Use a 8-bit unsigned char to store the (one byte) checksum.
Make some test files to see if it works as expected.

> `./check-xor.c`

Now write a short C program (called check-fletcher.c) that
computes the Fletcher checksum over an input file. Once again,
test your program to see if it works.

> `./check-fletcher.c`

Now compare the performance of both: is one faster than the other?
How does performance change as the size of the input file changes?
Use internal calls to `gettimeofday()` to time the programs. Which
should you use if you care about performance? About checking
ability?

```
$ ./measure-time test1
11.611 (nano seconds) <- xor
38.494 (nano seconds) <- fletcher
```

```
$ ./measure-time test2
14.600
44.024
```

> So, the xor calculation is much faster than the fletcher calculation

Read about the 16-bit CRC and then implement it. Test it on a number
of different inputs to ensure that it works. How is its performance
as compared to the simple XOR and Fletcher? How about
its checking ability?

> Obviously it is worse than XOR or Fletcher.

Now build a tool (`create-csum.c`) that computes a **single-byte**
**checksum** for every 4KB block of a file, and records the results in
an output file (specified on the command line). Build a related tool
(`check-csum.c`) that reads a file, computes the checksums over
each block, and compares the results to the stored checksums stored
in another file. If there is a problem, the program should print that
the file has been corrupted. Test the program by manually corrupting
the file.

!!!