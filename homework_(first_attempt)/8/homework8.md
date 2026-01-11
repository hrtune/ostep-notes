# Homework 8

This program, **mlfq.py**, allows you to see how the MLFQ scheduler presented in this chapter behaves. See the README for details. 

### Questions 

(1) Run a few randomly-generated problems with just two jobs and two queues; compute the MLFQ execution trace for each. Make your life easier by limiting the length of each job and turning off I/Os.

How to limit the length and the I/Os:

```
prompt> python3 mlfq.py -i 0 -m 10 -j 2 -n 2 -M 0 -s 100
```

```
Here is the list of inputs:
OPTIONS jobs 2
OPTIONS queues 2
OPTIONS allotments for queue  1 is   1
OPTIONS quantum length for queue  1 is  10
OPTIONS allotments for queue  0 is   1
OPTIONS quantum length for queue  0 is  10
OPTIONS boost 0
OPTIONS ioTime 0
OPTIONS stayAfterIO False
OPTIONS iobump False


For each job, three defining characteristics are given:
  startTime : at what time does the job enter the system
  runTime   : the total CPU time needed by the job to finish
  ioFreq    : every ioFreq time units, the job issues an I/O
              (the I/O takes ioTime units to complete)

Job List:
  Job  0: startTime   0 - runTime   2 - ioFreq   0
  Job  1: startTime   0 - runTime   7 - ioFreq   0
```



(2) How would you run the scheduler to reproduce each of the examples in the chapter? 

Example 1:

```
 python3 mlfq.py -l 0,200,0 -q 10 -n 3
```

Example 2:

```
python3 mlfq.py -l 0,200,0:100,20,0 -q 10 -n 3
```

Example 3:

```
python3 mlfq.py -l 0,202,0:2,20,1 -i 9 -n 3 -q 2 -S
```



(3) How would you configure the scheduler parameters to behave just like a round-robin scheduler? 

```
python3 mlfq.py -l 0,20,0:0,20,0 -q 1 -n 1
```



(4) Craft a workload with two jobs and scheduler parameters so that one job takes advantage of the older Rules 4a and 4b (turned on with the -S flag) to game the scheduler and obtain 99% of the CPU over a particular time interval. 

- Rule 4a: If a job uses up an entire time slice while running, its priority is reduced (i.e., it moves down one queue).
- Rule 4b: If a job gives up the CPU before the time slice is up, it stays at the same priority level.

```
python3 mlfq.py -l 0,200,0:50,100,9 -i 1 -q 10 -n 3 -S
```

// This command does 90% percent instead of 99%

(5) Given a system with a quantum length of 10 ms in its highest queue, how often would you have to boost jobs back to the highest priority level (with the -B flag) in order to guarantee that a single long-running (and potentially-starving) job gets at least 5% of the CPU? 

(6) One question that arises in scheduling is which end of a queue to add a job that just finished I/O; the -I flag changes this behavior for this scheduling simulator. Play around with some workloads and see if you can see the effect of this flag.