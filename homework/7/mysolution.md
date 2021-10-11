

## My solution for homework 7



**An example for the commands**

```
prompt> ./scheduler.py -p FIFO -j 3 -l 200,200,200 -s 0
```



**What is turnaround, response, and wait time?:**

```
T(turnaround) = T(completion) - T(arrival)
```

```
T(response) = T(first-run) − T(arrival)
```



1. Compute the response time and turnaround time when running three jobs of length 200 with the SJF and FIFO schedulers. 

**Answer:**

FIFO

```
ARG policy FIFO
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )
```

|         | T(turnaround) | T(response) |
| :------ | ------------- | ----------- |
| Job 0   | 200           | 0           |
| Job 1   | 400           | 200         |
| Job 2   | 600           | 400         |
| average | 400           | 200         |

SJF

```
ARG policy SJF
ARG jlist 200,200,200

Here is the job list, with the run time of each job:
  Job 0 ( length = 200.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 200.0 )
```



|         | T(turnaround) | T(response) |
| ------- | ------------- | ----------- |
| Job 0   | 200           | 0           |
| Job 1   | 400           | 200         |
| Job 2   | 600           | 400         |
| avarage | 400           | 200         |



2. Now do the same but with jobs of different lengths: 100, 200, and 300. 

FIFO

```
ARG policy FIFO
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
```

|         | T(turnaround) | T(response) |
| ------- | ------------- | ----------- |
| Job 0   | 100           | 0           |
| Job 1   | 300           | 100         |
| Job 2   | 600           | 300         |
| average | 333.3         | 133.3       |

SJF

```
ARG policy SJF
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
```

|         | T(turnaround) | T(response) |
| ------- | ------------- | ----------- |
| Job 0   | 100           | 0           |
| Job 1   | 300           | 100         |
| Job 2   | 600           | 300         |
| average | 333.3         | 133.3       |



3: Now do the same, but also with the RR scheduler and a time-slice of 1. 

```
ARG policy RR
ARG jlist 100,200,300

Here is the job list, with the run time of each job:
  Job 0 ( length = 100.0 )
  Job 1 ( length = 200.0 )
  Job 2 ( length = 300.0 )
```

3 * 100 - 2 = 298

300 + 2 * 100 - 1 = 499

500 + 100 = 600

|         | T(turnaround) | T(response) |
| ------- | ------------- | ----------- |
| Job 0   | 298           | 0           |
| Job 1   | 499           | 1           |
| Job 2   | 600           | 2           |
| average | 465.7         | 1           |



4: For the same length of jobs 

5 : For the jobs with the time slice which is same as or bigger than the job with biggest length.

6 : Yes, I could do it with shell scripting.

7: If the time slice is bigger than the job length of biggest, then the RR will be just FIFO.
$$
T(worstresponse) = T(turnaround:(N-1))
$$
