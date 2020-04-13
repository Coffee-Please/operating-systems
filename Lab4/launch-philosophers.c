// a program that simulates a solution to the dining philosopher problem.

#include <stdio.h>

int main(int argc, char** argv)
{
//There must be 1 arg
	if(argc != 2)
	{
		printf("Error: Incorrect number of args. Try ./launch-philosophers #seats");
	}//end if

//create a new process group            (see setpgid(2))

//allocate the semaphores
//You might want to use unnamed semaphores in this part
//Note the caveat in NOTES section of the sem_open man page

//create <seats> processes
//each child models a particular philosopher

//wait for the SIGTERM to parent

//send signal to all of your children (i.e., send it to the process group)

//wait for all your children

//perform any final cleanup                (see sem_unlink(2))

//return success from the parent process

	return 0;
}//end main
