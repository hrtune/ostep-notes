# Homework (Measurement) 

In this homework, you are to measure the size and cost of accessing a TLB. The idea is based on work by Saavedra-Barrera [SB92], who developed a simple but beautiful method to measure numerous aspects of cache hierarchies, all with a very simple user-level program. Read his work for more details. 

The basic idea is to access some number of pages within a large data structure (e.g., an array) and to time those accesses. For example, let’s say the TLB size of a machine happens to be 4 (which would be very small, but useful for the purposes of this discussion). If you write a program that touches 4 or fewer pages, each access should be a TLB hit, and thus relatively fast. However, once you touch 5 pages or more, repeatedly in a loop, each access will suddenly jump in cost, to that of a TLB miss. The basic code to loop through an array once should look like this: 

```c
int jump = PAGESIZE / sizeof(int); 

for (i = 0; i < NUMPAGES * jump; i += jump) { 

a[i] += 1; 

} 
```

In this loop, <u>one integer per page of the array a is updated</u>, up to the number of pages specified by NUMPAGES. By timing such a loop repeatedly (say, a few hundred million times in another loop around this one, or however many loops are needed to run for a few seconds), you can time how long each access takes (on average). By looking for jumps in cost as NUMPAGES increases, you can roughly determine how big the first-level TLB is, determine whether a second-level TLB exists (and how big it is if it does), and in general get a good sense of how TLB hits and misses can affect performance. 

![](\F19_5.jpg)

Figure 19.5 (above) shows the average time per access as the number of pages accessed in the loop is increased. As you can see in the graph, when just a few pages are accessed (8 or fewer), the average access time is roughly 5 nanoseconds. When 16 or more pages are accessed, there is a sudden jump to about 20 nanoseconds per access. A final jump in cost occurs at around 1024 pages, at which point each access takes around 70 nanoseconds. From this data, we can conclude that there is a two-level TLB hierarchy; the first is quite small (probably holding between 8 and 16 entries); the second is larger but slower (holding roughly 512 entries). The overall difference between hits in the first-level TLB and misses is quite large, roughly a factor of fourteen. TLB performance matters!



## Questions

1: For timing, you’ll need to use a timer such as that made available by gettimeofday(). How precise is such a timer? <u>How long does an operation have to take in order for you to time it precisely?</u> (this will help determine how many times, in a loop, you’ll have to repeat a page access in order to time it successfully) 

2: Write the program, called tlb.c, that can roughly measure the cost of accessing each page. Inputs to the program should be: the number of pages to touch and the number of trials. 

3: Now write a script in your favorite scripting language (csh, python, etc.) to run this program, while varying the number of pages accessed from 1 up to a few thousand, perhaps incrementing by a factor of two per iteration. Run the script on different machines and gather some data. How many trials are needed to get reliable measurements? 

4: Next, graph the results, making a graph that looks similar to the one above. Use a good tool like ploticus or even zplot. Visualization usually makes the data much easier to digest; why do you think that is? 

5: One thing to watch out for is compiler optimzation. Compilers do all sorts of clever things, including removing loops which increment values that no other part of the program subsequently uses. How can you ensure the compiler does not remove the main loop above from your TLB size estimator? 

6: Another thing to watch out for is the fact that most systems today ship with multiple CPUs, and each CPU, of course, has its own TLB