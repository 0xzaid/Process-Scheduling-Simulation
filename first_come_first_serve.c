/* 
Task 1: Non-preemptive scheduling (First come first served)
Zaid 
Below is the implementation for process scheduling 
on a First Come First Serve (FCFS) Basis,Where 
the processes are serviced in order of their arrival time.
*/

#include "setup.h"

/*
 A function that takes a filename as input and returns the number of processes
 found (number of lines)
 @param char pointer filename
 @return number of processes
*/
int get_no_of_processes(char *filename){
	// initialize to 0
	int no_of_processes = 0;
	int character = 0;

	// open file in erad mode and assign to fp
	FILE *fp = fopen(filename, "r");

	// if fp is NULL then file is empty and return 0
	if(fp == NULL)
		return 0;

	// loop until EOF
	while(!feof(fp)) {
		// fgetc to ovtain next character in position
		character = fgetc(fp);
		// if that characteris a newline, go to the next line
		if(character == '\n')
			no_of_processes++;
	}
	// close the file
	fclose(fp);

	// return number of processes
	return no_of_processes;
}

/*
 A function that takes the number of processes, process struct and filename as input
 and reads the information in the file and stores it in a queue of pcb_t structs
 @param number of processes
 @param process struct
 @param filename
 @return void
*/
void store_process_info(int no_of_processes, pcb_t *process_queue, char *filename) {
	// open file in read mode and assign pointer fp
	FILE *fp = fopen(filename, "r");

	// loop over all number of processes
	for(int i = 0; i < no_of_processes; i++) {

		// scans the line in file and reads according to the given format, assigns the info the data holder in pcb_t struct
		fscanf(fp, "%s %d %d %d", process_queue[i].process_name, &process_queue[i].arrivalTime, &process_queue[i].serviceTime, &process_queue[i].deadline);
		// set initial remaining time as the service time
		process_queue[i].remainingTime = process_queue[i].serviceTime;

		// set state to ready
		process_queue[i].state = Ready;
	}
	// close the file
	fclose(fp);

	//returns void
}

/*
 A function that takes the number of processes and queue of process struct as input
 and sorts the processes in a queue according to which process came first (increasing arrival time)
 @param number of processes
 @param queue of process truct
 @return void
*/
void sort_processes(int no_of_processes, pcb_t *process_queue){
	// intialize variables to 0
	int i = 0;
	int j = 0;

	// initialize temp pcb_t struct
	pcb_t temp;

	// loop over all the number of processes and the next process
	for(int i = 0; i < no_of_processes; i++) {
		for(int j = (i+1); j < no_of_processes; j++){

			// if current process arrival time is greater than the next
			if(process_queue[i].arrivalTime > process_queue[j].arrivalTime) {

				// assigns the temp pcb_t to current process
				temp = process_queue[i];

				// assign the next process to current
				process_queue[i] = process_queue[j];

				// assign the next process to temp process
				process_queue[j] = temp;
			}
		}
	}
}

/*
A function that takes a filename as input and processes it to preapre the process queue and then returns it
@param filename
@returns pcbt_t 
*/
pcb_t * get_queue_of_processes(char *filename){
	// initialize a pointer pcb_t
	pcb_t *process_queue;

	// call function get_no_of_processes and assign the result to no_of_processes
	int no_of_processes = get_no_of_processes(filename);

	// creates a queue by assigning space according to the no. of processes
	process_queue = (pcb_t *) malloc(no_of_processes*sizeof(pcb_t));

	// call function to loop through file and stores processing info in queue
	store_process_info(no_of_processes, process_queue, filename);

	// sort the queue in increasing order of arrival time
	sort_processes(no_of_processes, process_queue);

	//returns process queue
	return process_queue;
}

/*
A function that applies first come first serve (FCFS) for the functionality requested in task1
takes the filename as input and has no return
@param filename
@return void
*/
void first_come_first_served(char *filename){
	// initialize variables
	int no_of_processes = 0;

	// get number of processes
	no_of_processes = get_no_of_processes(filename);

	// create and process the process queue
	pcb_t *process_queue = get_queue_of_processes(filename);

	// start at time 0
	int time = 0;

	// current running process
	int current_process = 0;

	// sets the wait time for first process to the time of its arrival to the system
	process_queue[0].waitTime = process_queue[0].arrivalTime;

	// loop through the proceses till the last process has state of exit
	while(process_queue[no_of_processes-1].state != Exit) {
		// check if current process has finished running
		if(process_queue[current_process].remainingTime == 0){
			// if so, prints that its has finished
			printf("Time %d: %s  has finished execution.\n", time, process_queue[current_process].process_name);

			// sets the done time to the current time and puts the state in Exit
			process_queue[current_process].doneTime = time;
			process_queue[current_process].state = Exit;

			// iterate the current process counter to move to the next counter
			current_process++;

			// skips to next loop
			continue;
		}
		// loop through all processes in queue
		for(int j = 0; j < no_of_processes; j++){
			// if a process has arrival time that corresponds to the current time
			if(process_queue[j].arrivalTime == time)
				// print the process entered the system
				printf("Time %d: %s  has entered the system.\n", time, process_queue[j].process_name);
		}

		// check if a process has an arrival time less than current time, and that the remaining time for process is not 0
		if(process_queue[current_process].arrivalTime <= time && process_queue[current_process].remainingTime != 0) {
			// if remaining time is equal to service time, process hasnt started yet, this will be the case 
			// till the process starts. Which allows us to easily record the wait time
			if(process_queue[current_process].remainingTime == process_queue[current_process].serviceTime){
				// update wait time
				process_queue[current_process].waitTime = time - process_queue[current_process].arrivalTime;
			}
			// set state to running
			process_queue[current_process].state = Running;
			// print that process is in running state
			printf("Time %d: %s  is in the running state.\n", time, process_queue[current_process].process_name);
		}
		// if current process has arrival time greater than current time, queue is empty
		if(process_queue[current_process].arrivalTime > time){
			// print queue is empty
			printf("Time %d: Empty process queue.\n", time);
			time++;
			continue;
		}
		// else sleep 1 to replicate a process running, increment time and decrement remaining time
		// for thecurrent process by 1
		time++;
		process_queue[current_process].remainingTime--;
	}
	// initialize file pointer
	FILE *fptr;
	// opens file in write mode, overrides if file already exists
	fptr = fopen("results-task1.txt", "w");
	// loop over process queue
	for(int i = 0; i < no_of_processes; i++){
		// if process has done time less than or equal to deadline then it has met the deadline
		if(process_queue[i].doneTime <= process_queue[i].deadline){
			// set deadline to 1
			process_queue[i].deadlinebool = 1;
		} else {
			// else set deadline to 0
			process_queue[i].deadlinebool = 0;
		}
		fprintf(fptr, "%s %d %d %d\n", process_queue[i].process_name, process_queue[i].waitTime, process_queue[i].doneTime - process_queue[i].arrivalTime, process_queue[i].deadlinebool);
	}
	// close the file
	fclose(fptr);
	// returns void
}

int main(int argc, char *argv[]){
	// if only the call to the file is given, FCFS function is called with default file of "processes.txt"
	if(argc == 1){
		first_come_first_served("processes.txt");
		return 0;
	}
	// a file is given as an argument, call FCFS function with the input file
	first_come_first_served(argv[1]);
	return 0;
}	