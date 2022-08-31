/*
Task 3: Deadline-based scheduling
Zaid
Below is the implementation of the Earliest Deadline First 
scheduling algorithm. When a new process enters the system, 
it will be compared with other processes in queue, and if 
they have the same deadline, First come first served will be used.
*/

#include "setup.h"

/* self defined funciton that takes a filename pointer as input parameter
and returns the number of processes found (number of lines).
*/
int get_num_of_processes(char *filename){
	// initialize variables to zero
	int num_of_processes = 0;
	int character = 0;
	// open file in read mode and assign to fp
	FILE *fp = fopen(filename,"r");
	// if fp is NULL then the file is empty and hence returns 0
	if (fp == NULL)
		return 0;
		// loops until EOF (end of file) is found
	while (!feof(fp)){
		// use fgetc to obtain the next character in position
		character = fgetc(fp);
		// if that character is \n it indicates the end of the current line and advancement to new line
		if (character == '\n')
			num_of_processes ++; // increment by 1
	}
	fclose(fp); //closes the file
	// returns the final number of processes
	return num_of_processes;
}

/* self defined function that takes no. of processes, process struct and filename pointer as input
where it reads the information in file and stores it in a queue of pcb_t structs.
*/
void store_process_info(int num_of_processes, pcb_t *process_queue, char *filename){
	FILE *fp = fopen(filename,"r"); // opens file in read mode and assigns to pointer fp
	for (int i = 0; i < num_of_processes; i++){ // loops until the no. of processes
		// scans the line in file and reads according to the format given in our spec, assigns the info to
		// the corresponding data holder in the pcb_t struct.
		fscanf(fp, "%s %d %d %d", process_queue[i].process_name, &process_queue[i].arrivalTime, &process_queue[i].serviceTime, &process_queue[i].deadline);
		// sets initial remainingTime as the service time
		process_queue[i].remainingTime = process_queue[i].serviceTime;
		// sets the state to Ready
		process_queue[i].state = Ready;
	}
	fclose(fp); // close the file
	// No return
}

/* self defined function that takes no. of processes and queue of process struct as input
where it sorts the processes in queue according to which process came first (acending arrival time).
*/
void sort_processes(int num_of_processes, pcb_t *process_queue){
	// initialize variables
	int i;
	int j;
	
	pcb_t temporary; // intialize temp pcb_t struct
	
	for (int i = 0; i < num_of_processes; i++){
		for (int j = (i + 1); j < num_of_processes; j++){
			// if the current process entry time is greater than tht of the next...
			if (process_queue[i].arrivalTime > process_queue[j].arrivalTime){
				// assigns the temp pcb_t to the current process
				temporary = process_queue[i];
				// assigns the next process to the current one
				process_queue[i] = process_queue[j];
				// then assigns the next process to the temp process
				process_queue[j] = temporary;
			}
		}
	}
}

/* self defined function that takes no. of processes and queue of process struct as input
where it sorts the processes in queue according to which process has an earlier dealine s(acending deadline time).
*/
void sort_processes_deadline(int start, int num_of_processes, pcb_t *process_queue, int current_time){
	// initialize variables
	int i;
	int j;
	
	pcb_t temporary; // intialize temp pcb_t struct
	
	for (int i = start; i < num_of_processes; i++){
		for (int j = (i + 1); j < num_of_processes; j++){
			// if the current process entry time is greater than tht of the next...
			if (process_queue[i].deadline > process_queue[j].deadline){
				// if the current running process will have to pause for a new process..
				if (i == start){
					// save the current time and change the state to paused
					process_queue[i].lastTimeInRun = current_time;
					process_queue[i].state = Paused;
				}
				// assigns the temp pcb_t to the current process
				temporary = process_queue[i];
				// assigns the next process to the current one
				process_queue[i] = process_queue[j];
				// then assigns the next process to the temp process
				process_queue[j] = temporary;
			}
		}
	}
}


/* self defined function that takes a filename pointer as input and does all the 
processing to prepare the processes queue and then returns it.
*/
pcb_t * get_queue_of_processes(char *filename){
	pcb_t *process_queue; // intialize a pointer pcb_t
	// uses function defined earlier to find no. of processes and assigns to variable
	int num_of_processes = get_num_of_processes(filename); 
	// creates a queue by assignning space according to the no. of processes
	process_queue = (pcb_t *) malloc(num_of_processes*sizeof(pcb_t));
	// calls the function to loop through file and store processing information in our queue
	store_process_info(num_of_processes, process_queue, filename);
	// sorts the queue in ascending order of arrivalTimes
	sort_processes(num_of_processes, process_queue);
	//returns the process queue.
	return process_queue;
}


/* self defined function that applies first come first serve to implement the functionality
for task 1 of this assignment. This function only take the filename pointer as input, has no return.
*/
void FCFS(char *filename){

	pcb_t *running_queue; // intialize a pointer pcb_t
	// intialize variable
	int num_of_processes;
	// get no. of processes
	num_of_processes = get_num_of_processes(filename);
	// create and process process_queue
	pcb_t *process_queue = get_queue_of_processes(filename);
	// creates a queue by assignning space according to the no. of processes
	running_queue = (pcb_t *) malloc(num_of_processes*sizeof(pcb_t));
	int running_queue_len = 0;
	//sets time now to 0
	int timeNow = 0;
	// counter for which process is currently running set to 0
	int current_process = 0;
	// counter for the number of jobs done set to 0
	int jobsdone = 0;
	// sets the wait time for first process to the time of its entry into the system
	process_queue[0].waitTime = process_queue[0].arrivalTime;
	// loops through the processes until the last one has state of Exit, indicating all processes are done.
	
	// if the entry time for the earliest process is not zero..
	if (process_queue[0].arrivalTime > 0){
		// we loop until the entry time
		for (int i = 0; i < process_queue[0].arrivalTime; i++){
			// print the time and that the process queue is empty
			printf("Time: %d: Empty process queue.\n",timeNow);
			timeNow ++;
		}
	}
	// prints that the process has entered the system
	printf("Time: %d: %s has entered the system.\n", timeNow, process_queue[0].process_name);
	running_queue[running_queue_len] = process_queue[0];
	running_queue_len ++;
	while(jobsdone != num_of_processes){
			// loops through all the processes in queue
		for (int j = 1; j < num_of_processes; j++){
			if (process_queue[j].arrivalTime == timeNow){ // if a process has entry time corresponding to current time
				// prints that the process has entered the system
				printf("Time: %d: %s has entered the system.\n", timeNow, process_queue[j].process_name);
				running_queue[running_queue_len] = process_queue[j];
				running_queue_len ++;
				int i = current_process;
				sort_processes_deadline(i, running_queue_len, running_queue, timeNow);
				}
			}
		// if current process has entry time greater than current time, it means the queue is empty
		if(running_queue[current_process].arrivalTime > timeNow || current_process == running_queue_len){
			printf("%s",running_queue[current_process].process_name);
			// prints that the queue is empty
			printf("Time: %d: Empty process queue.\n", timeNow);
			// sleeps for one second and iterates current time then jumps to next loop
			timeNow++;
			continue;
		}
		// first checks if the current process has no remaining time left (has finished running)
		if (running_queue[current_process].remainingTime == 0){
			// if so, prints that its has finished executing
			printf("Time: %d: %s has finished execution.\n", timeNow, running_queue[current_process].process_name);
			// sets the done time to the current time and puts the state in Exit
			running_queue[current_process].doneTime = timeNow;
			running_queue[current_process].state = Exit;
			// loops through the no. of processes
			for (int i = 0; i < num_of_processes; i++){
				// finds the corresponding process to transfer the data to the actaul process struct
				if (strcmp(running_queue[current_process].process_name,process_queue[i].process_name)==0){
					process_queue[i].waitTime = running_queue[current_process].waitTime;
					process_queue[i].doneTime = running_queue[current_process].doneTime;
					process_queue[i].state = Exit;
				}
			}
			// iterates the current_process counter to move on to nect counter
			jobsdone++;
			current_process ++;
			// skips to next loop
			continue;
		}

		// checks if a process has an entry time less than current time, and that the remaining time for process is not 0
		if (running_queue[current_process].arrivalTime <= timeNow && running_queue[current_process].remainingTime != 0){
			// if the remaining time is equal to service time, then the process hasnt started yet, this will only be the case
			// until the process starts... which allows us to easily record the wait time
			if (running_queue[current_process].remainingTime == running_queue[current_process].serviceTime){
				// updates the waitTime
				running_queue[current_process].waitTime = timeNow - running_queue[current_process].arrivalTime;
			}
			if (running_queue[current_process].state == Paused){
				running_queue[current_process].waitTime += (timeNow - running_queue[current_process].lastTimeInRun);
			}
			running_queue[current_process].state = Running; // sets the state to Running.
			// prints that the process is in running state
			printf("Time: %d: %s is in the running state.\n", timeNow, running_queue[current_process].process_name);
		}
		// else sleeps for one second to replicate process running, iterates current time and decrements the
		// remaining time for the current process by one.
		timeNow++;
		running_queue[current_process].remainingTime --;
	
	}
	// intializes file pointer
	FILE *fptr;
	// opens file in write mode, overrides if file has content
	fptr = fopen("results-task3.txt", "w");
	// loops over process queue
	for (int i = 0; i < num_of_processes; i++){
		// if the process has done time less than or equal to deadline then it has met the deadline
		if (process_queue[i].doneTime <= process_queue[i].deadline){
			// sets deadline to 1
			process_queue[i].deadlinebool = 1;
			}
		else{
			// otherwise sets it to 0
			process_queue[i].deadlinebool = 0;
		}
		// writes to file the name, last recorded waitTime before process started running, turnaround time and whether deadline was met or not
		fprintf(fptr, "%s %d %d %d\n", process_queue[i].process_name, process_queue[i].waitTime, process_queue[i].doneTime - process_queue[i].arrivalTime, process_queue[i].deadlinebool);
	}
	// close the file
	fclose(fptr);
	// no return
}

int main(int argc, char *argv[]){
	// This is the main section where the function is called!
	// if only the call to the file is given, the FCFS function is called with default file "process-data.txt"
	if (argc == 1){
		FCFS("processes.txt");
		return 0;
	}
	// if a file is given alongside the function call, it will call the FCFS with that file
	FCFS(argv[1]);
	return 0;
}


