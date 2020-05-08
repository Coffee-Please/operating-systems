//a program that is intended to run as a daemon, and based upon signals
//will either create or destroy child processes.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <signal.h>

void sig_handler(int signum)
{

}//end sig_handler


int main()
{
//Set the file creation mask to 0                 (see umask(2))
	umask(0);

//Fork
	int child = fork();

//Parent Process, have the parent terminate
	if(child > 0)
	{
		exit(EXIT_SUCCESS);
	}//end if

//Child Process continues
	if(child == 0)
	{
	//Create a new session                     (see setsid(2))
		if(setsid() != 0)
		{
			printf("Error: Setsid Fail\n");
			exit(EXIT_FAILURE);
		}//end if

	//create a new process group
		setpgid(0, 0);

	//Change the current working directory to be “/”         (see chdir(2))
		chdir("/");

	//Close all unneeded file descriptors                (see getrlimit(2))
		getrlimit();

	//Reopen the standard file descriptors to map to /dev/null     (see dup(2))
		dup();

	}//end if

//Else, Fork Error
	else
	{
		printf("Error: Fork Fail\n");
		exit(EXIT_SUCCESS);
	}//end else

	return 0;

}//end main
