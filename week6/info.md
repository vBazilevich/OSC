# Explanations
ex1 - first in first served
ex2 - shortest job first
ex3 - round robbin

## Input format
First line - number of processes

Starting from the second line:

First column - arrival time
Second columd - execution time

## Arguments
ex3 supports one argument - quantum size in time units.
It must be a poritive integer number.

## Tests
processes0.list - 5 processes with overlapping arrival times
    
processes1.list - 3 processes with non-overlapping arrival times

processes2.list - 4 overlapping processes

## Comparison
This part of the comparison is based on processes0.list test.

Shortest job first provided minimal turnaround time on this test.
Possible explanation - short tasks don't have to wait for a long time,
so their turnaround time is decreased. As a result, long tasks arrived
later have to wait less time.

This algorithm also shown the shortest average waiting time, because short processes
doesn't have to wait for a long time before they will be chosen. For the long tasks
it doesn't change turnaround time drastically, because execution time of the small process
is much smaller than the execution time of the longer process.

It is also important that if quantum for Round Robin algorithm becomes at least the longest
execution time of all tasks in the system, Round Robin yields the same results as FIFS.

This part of the comparison is based on processes1.list test.

All algorithms show the same result on this test.

This part of the comparison is based on processes1.list test.

SJF wins again

## Conclusion
In my tests SJF shows the better turnaround time and average waiting time.
But SJF and FIFS can't be used in interactive system. Thus, I can't come up with
my personal opinion which algorithm is better in general case. All of them have some
limitations and under some conditions they can show better performance. 
