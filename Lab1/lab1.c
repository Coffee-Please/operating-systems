//Created 2/15/2020 by Priya Singh
//COMP 322/L Lab 1: Time and Forking Children

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/times.h>
#include <unistd.h>

void report_info(int cpid, int wpid, int status);

void report_info(int cpid, int wpid, int status)
{
	struct tms clock_tms;

//The program and its child reports on the information
//The process ID of its parent              (see getppid(2))
//Its own process ID                    (see getpid(2))
//The program and its child reports on the information
//The process ID of its parent              (see getppid(2))
//Its own process ID                    (see getpid(2))
//The process ID of its child (if applicable)        (see fork(2))
//The return status of its child (if applicable)        (see exit(3), waitpid(2))

//if in the child process
	if(cpid == 0)
	{
		printf("PPID: %d, PID: %d\n", getppid(), getpid());
	}//end if
//if in the parent process
	else if(cpid > 0)
	{
		printf("PPID: %d, PID: %d, CPID: %d, RETVAL: %d\n", getppid(), getpid(), wpid, status);

	//The program will report the following time information    (see times(2))
		times(&clock_tms);

	//user time, system time
		printf("USER: %ld, SYS: %ld\n", clock_tms.tms_utime, clock_tms.tms_stime);

	// user time of child, system time of child
		printf("CUSER: %ld, CSYS: %ld\n", clock_tms.tms_cutime, clock_tms.tms_cstime);

	}//end else
//else, fork failure
	else
	{
		printf("FORK FAILED\n");//fork failed
	}//end else
}//end report_info


int main()
{
//Local variables
	time_t start, stop;
	pid_t cpid, wpid;
	int status;

//Get start time
	time(&start);

//The program prints the number of seconds since..         (see time(2))
	printf("START: %ld\n", start);

//The program creates a child process             (see fork(2))
	cpid = fork();
//	cpid = -3;//check for fork failure

//if cpid == 0 -> in child
	if(cpid == 0)
	{
	//report information
		report_info(cpid, 0, 0);

		exit(EXIT_SUCCESS);
	}//end if

//if cpid > 0 -> in parent
	else if(cpid > 0)
	{
	//The program will wait for the child to finish            (see waitpid(2))
		wpid = waitpid(cpid, &status, WUNTRACED);

	//report information
		report_info(cpid, wpid, status);
	}//end else if

//else fork fail
	else
	{
	//report information
		report_info(cpid, 0, 0);

	//The program prints the number of seconds since..    (see time(2))
		time(&stop);
		printf("STOP: %ld\n", stop);

		exit(EXIT_FAILURE);
	}//end else

//The program prints the number of seconds since..    (see time(2))
	time(&stop);

	printf("STOP: %ld\n", stop);

	exit(EXIT_SUCCESS);
}//end main
