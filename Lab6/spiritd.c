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

//void sigterm_handler(int signum)
//{
//
//}//end sigterm_handler
//
//void sigusr1_handler(int signum)
//{
//
//}//end sigusr1_handler
//
//void sigusr2_handler(int signum)
//{
//
//}//end sigusr2_handler

void create_daemon()
{
//Local Variables
	int fd_0, fd_1, fd_2;
	pid_t child;
	struct rlimit cur;

//Set the file creation mask to 0                 (see umask(2))
	umask(0);

//Get all file descriptors possibly inherited from parent or otherwise (see getrlimit(2))
	getrlimit(RLIMIT_NOFILE, &cur);

//Fork
	if((child = fork()) < 0)
	{
	//Fork Error
		printf("Error: Fork Fail\n");
		exit(EXIT_FAILURE);
	}//end else

//Parent Process, have the parent terminate
	else if(child != 0)
	{
		exit(0);
	}//end if

//Child Process continues to run

//Create a new session                     (see setsid(2))
	setsid();

//create a new process group
	setpgid(getpid(), getsid(getpid()));

//Fork again
	if((child = fork()) < 0)
	{
	//Fork Error
		printf("Error: Fork Fail\n");
		exit(EXIT_FAILURE);
	}//end else

//Parent Process, have the parent terminate
	else if(child != 0)
	{
		exit(0);
	}//end if

//Change the current working directory to be the root directory “~/”         (see chdir(2))
	chdir("~/");

	if(cur.rlim_max == RLIM_INFINITY)
	{
		cur.rlim_max = 1024;
	}//end if

//Close all file descriptors
	for(unsigned int i = 0; i < cur.rlim_max; i++)
	{
		close(i);
	}//end for

//Reopen the standard file descriptors to map to /dev/null (see dup(2))
	fd_0 = open("/dev/null", O_RDWR);
	fd_1 = dup(0);
	fd_2 = dup(0);

//Error reopening descriptors
	if(fd_0 != 0 || fd_1 != 1 || fd_2 != 2)
	{
		printf("Error: fd %d %d %d\n", fd_0, fd_1, fd_2);
	}//end if

}//end create_daemon

int main()
{
//Create daemon process
	create_daemon();

//Keep the daemon running
	while(1){}//end while

	return 0;
}//end main
