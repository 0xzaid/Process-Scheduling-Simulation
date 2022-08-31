/* 
Zaid
Below is the implementation for process scheduling 
on a shortest remaining time next with a time quantum 
of 3 (SRTN) Basis, Where the processes are serviced in order of 
their arrival time.
*/

#include "setup.h"

/*
 A function that tajes a filename as input and returnsthe number of processes
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
 A function to create a queue to store processes structs to use in scheduling,
 takes queue size as input, and returns queue size
 @param queue_size
 @return queue
*/
Queue* createQueue(int queue_size){
	// initialize queue
	Queue* queue = (Queue*) calloc(1,sizeof(Queue));

	// initialize variables
	queue->front = 0;
	queue->back = queue_size - 1;
	queue->len = 0;
	queue->size = queue_size;
	// allocates space based on number of processes
	queue->array = (pcb_t*) calloc(queue->size, sizeof(pcb_t));

	return queue;
}

/*
 A function that will append a processes to the back of the queue. Takes
 a queue pointer and the prcoess itself, returns nothing
 @param queue
 @param process
 @return void
*/
void append(Queue *queue, pcb_t process){
	// increment value corresponding to the back of the queue
	queue-> back = (queue-> back + 1) % queue->size;
	// append process to the back of the queue
	queue->array[queue->back] = process;
	// increment length
	queue->len = queue->len+1;
}


/*
 A function that returns the first item in the queue. Takes queue pointer and returns nothing
 @param queue
 @return void
*/
pcb_t retrieve(Queue *queue){
	// first process in queue
	pcb_t process = queue->array[queue->front];
	// update queue
	queue->front = (queue->front+1) % queue->size;
	// decrement length
	queue->len = queue->len-1;

	return process;
}


/*
 A function that applies shortest remanining time next scheduling for task 2.
 Takes filename and returns nothing
 @param filename
 @return void
*/
void shortest_remaining_time_next(char *filename) {
	// initialize variable
	int no_of_processes = 0;

	// get number of processes
	no_of_processes = get_no_of_processes(filename);

	// create and process the queue
	pcb_t *process_queue = get_queue_of_processes(filename);
	
	// set time to 0
	int time = 0;

	// sets the wait time for first process to thetime ofits arrival into the system
	process_queue[0].waitTime = process_queue[0].arrivalTime;
	
	// set count to 0
	int count = 0;
	
	// counter for jobs done initialized to 0
	int jobsDone = 0;
	
	// initialize variable to hold the currently running process
	pcb_t running_process;
	
	// initializes the queue to hold processes
	Queue *processes_to_run = createQueue(no_of_processes);
	
	// if arrival time for the earliest process is not zero
	if(process_queue[0].arrivalTime > 0){
		
		// loop till arrival time
		for(int i = 0; i < process_queue[0].arrivalTime; i++) {
			
			// print the time and that the process queue is empty
			printf("Time %d:  Empty process queue.\n", time);
			
			// sleep 1 and increment time by 1
			sleep(1);
			time++;
		}
	}
}

/*
 A function that indicates whether the queue is empty or not,takes queue and returns an int
 1 if empty, 0 if not empty.
 @param queue
 @return integer (0 or 1)
*/
int isEmpty(Queue* queue){
	// if length is 0 then queue is empty and return 1
	if(queue->len == 0){
		return 1;
	} else{
		// else the queue is not empty and return 0
		return 0;
	}
}

int main(int argc, char *argv[]){
	if(argc == 1){
		shortest_remaining_time_next("processes.txt");
		return 0;
	}
	shortest_remaining_time_next(argv[1]);
	return 0;
}