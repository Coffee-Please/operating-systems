// a program that simulates a solution to the dining philosopher problem.

#include <stdio.h>
#include <signal.h>

//send signal to all of your children (i.e., send it to the process group)
void sig_handler(int signum)
{
	signal(SIGTERM, sig_handler);

//send signal to all your children
//wait for all your children

//perform any final cleanup                (see sem_unlink(2))
	sem_unlink();

}


int main(int argc, char** argv)
{
//There must be 1 arg
	if(argc != 2)
	{
		printf("Error: Incorrect number of args. Try ./launch-philosophers #seats");
	}//end if

//create a new process group            (see setpgid(2))
	setpgid();

//parent process

//allocate the semaphores
//You might want to use unnamed semaphores in this part
//??Note the caveat in NOTES section of the sem_open man page
	sem_init();

	shm_open();

//create <seats> processes
//each child models a particular philosopher
	seats = atoi(arg[1]);

//wait for the SIGTERM to parent
	signal(SIGTERM, sig_handler);

//return success from the parent process
	exit(EXIT_SUCCESS);

}//end main
