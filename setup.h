#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#define True 1
#define False 0

/* Special enumerated data type for process state */
typedef enum{
	Ready,Running,Exit,Paused
} process_state_t;

/* data structure used as process control block, schedueler should 
create one instance per running process in system.
*/
typedef struct{
	// string that identifies process
	char process_name[11]; 

	// time process entered system
	int arrivalTime;

	// total CPU time required by system
	int serviceTime; 

	// remaining service time until completion
	int remainingTime;

	// time the process needs to finish before
	int deadline; 

	// how long the process waited before being in RUNNING state
	int waitTime; 

	// records the last time the process was running
	int lastTimeInRun; 

	// time at which the process finished executing
	int doneTime; 

	// stores whether the deadline has been met or not
	int deadlinebool; 

	//current process state (ex/ READY)
	process_state_t state; 

} pcb_t;

typedef struct{
	// front of the queue
	int front;

	// back of the queue
	int back; 

	// number of processes in queue
	int len; 

	// max size of queue
	int size; 

	// array to store process structs
	pcb_t* array; 
} Queue;