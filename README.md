# Process-Scheduling-Simulation
 
 Process Scheduling Simulation using C

Algorithms used:
- First come first served
- Shortest remaining time next
- Earliest deadline first

Task 1:

A program for process scheduling on a First Come First Serve (FCFS) Basis, Where the processes are serviced in order of their arrival time. This program Can
take an arguement for a processes file or will use the default "process.txt" file to run the program on, and will output a "results-task1.txt" file
with the correct output.

How to compile:
```
	gcc <source_file> -o <desired_executable_name>
	gcc first_come_first_serve.c -o task1
```
How to run:
```
	./<desired_executable_name>
	e.g. ./task1
	e.g. ./task1 <processes_file_path>
```
Expected output:
	A file called "results-task1.txt" that contains the result of running the program on <process_file_path> if given, otherwise processes.txt is the
	default.



Task 2:

A program for a process scheduling on a Shortest Remaining Time Next basis, where the processes are serviced in order of which process that arrived has the
shortest remaining time to finish. This program cab take an argument for a processes file or will use the default "process.txt" file to run the program on, and
will output a "results-task2.txt" file with the correct output.


How to compile:
```
	gcc <source_file> -o <desired_executable_name>
	e.g. gcc shortest_remaining_time_next.c -o task2
```
How to run:
```
	./<desired_executable_name>
	e.g. ./task2
	e.g. ./task2 <processes_file_path>
 ```
Expected output:
	A file called "results-task2.txt" that contains the result of running the program on <process_file_path> if given, otherwise processes.txt is the
	default.



Task 3:

A program for a process scheduling on a Earliest deadline first bases, where the processes are serviced in order of which process that has arrived has the earliest deadline first. This program can take an argument for a processes file or will use the default "process.txt" file to run the program on, and
will output a "results-task3.txt" file with the correct output.

 
How to compile:
```
	gcc <source_file> -o <desired_executable_name>
	e.g. gcc earliest_deadline_first -o task3
```
How to run:
```
	./<desired_executable_name>
	e.g. ./task3
	e.g. ./task3 <processes_file_path>
```
Expected output:
	A file called "results-task3.txt" that contains the result of running the program on <process_file_path> if given, otherwise processes.txt is the
	default.
