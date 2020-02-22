//Created 2/15/2020 by Priya Singh
//COMP 322/L Lab 1: Time and Forking Children

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <unistd.h>

int main()
{
	time_t start, end, stop;
	pid_t cpid;
	int status;

//Get start time
	time(&start);

//The program prints the number of seconds since..         (see time(2))
	printf("START: %ld\n", start);

//The program creates a child process             (see fork(2))
	cpid = fork();

//if cpid == 0 -> in child
	if(cpid == 0)
	{
	//The program and its child reports on the information
	//The process ID of its parent              (see getppid(2))
		printf("PPID: %d, ", getppid());

	//Its own process ID                    (see getpid(2))
		printf("PID: %d\n", getpid());
		exit(EXIT_SUCCESS);
	}//end if

//if cpid > 0 -> in parent
	else if(cpid > 0)
	{
	//The program will wait for the child to finish            (see waitpid(2))
		cpid = waitpid(cpid, &status, WUNTRACED);

	//The program and its child reports on the information
	//The process ID of its parent              (see getppid(2))
		printf("PPID: %d, ", getppid());

	//Its own process ID                    (see getpid(2))
		printf("PID: %d, ", getpid());

	//The process ID of its child (if applicable)        (see fork(2))
		printf("CPID: %d, ", cpid);

	//The return status of its child (if applicable)        (see exit(3), waitpid(2))
		printf("RETVAL: %d\n", status);
	}//end if

//else fork fail
	else
	{
		printf("FORK FAILED");//fork failed
		exit(EXIT_FAILURE);
	}//end else

//The program will report the following time information    (see times(2))
//user time, system time

	printf("USER:, SYS: \n");

// user time of child, system time of child
	printf("CUSER: , CSYS: \n");

//The program prints the number of seconds since..    (see time(2))

	sleep(3);

	time(&end);

	stop = end + (end - start);

	printf("STOP: %ld\n", stop);

	return 0;
}//end main
