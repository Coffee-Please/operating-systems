//a program that is intended to run as a daemon, and based upon signals
//will either create or destroy child processes.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <signal.h>

//void sig_handler(int signum)
//{
//
//}//end sig_handler
//
//void sig_handler(int signum)
//{
//
//}//end sig_handler
//
//void sig_handler(int signum)
//{
//
//}//end sig_handler


int main(int argc, char** argv)
{
//Local Variables
	int child, fd_0, fd_1, fd_2;
	struct rlimit cur;

//Set the file creation mask to 0                 (see umask(2))
	umask(0);

//Fork
	child = fork();

//Fork Error
	if(child < 0)
	{
		printf("Error: Fork Fail\n");
		exit(EXIT_SUCCESS);
	}//end else

//Parent Process, have the parent terminate
	else if(child > 0)
	{
		exit(EXIT_SUCCESS);
	}//end if

//Child Process continues

//Create a new session                     (see setsid(2))
	if(setsid() != 0)
	{
		printf("Error: Setsid Fail\n");
		exit(EXIT_FAILURE);
	}//end if

//create a new process group
	setpgid(0, 0);

//setgpid error

//Change the current working directory to be the root directory “/”         (see chdir(2))
	chdir("~/");

//chdir error


//Close all unneeded file descriptors possibly inherited from parent or otherwise (see getrlimit(2))
	getrlimit(RLIMIT_NPROC, &cur);

//getrlimit error

	if(cur.rlim_max == RLIM_INFINITY)
	{
		cur.rlim_max = 1024;
	}//end if

	for(unsigned int i = 0; i < cur.rlim_max; i++)
	{
		close(i);
	}//end for

//Reopen the standard file descriptors to map to /dev/null (see dup(2))
	fd_0 = open("/dev/null", O_RDWR);
	fd_1 = dup(0);
	fd_2 = dup(0);

	return 0;
}//end main
