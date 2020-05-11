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


void sigterm_handler(int signum)
{
//The daemon handles: SIG_TERM, SIG_USR1, and SIG_USR2  (see signal(2))
//Upon SIG_TERM, the program kills all child processes and
//shutdowns the daemon gracefully.                     (see kill(2))

}//end sigterm_handler


void sigusr1_handler(int signum)
{
//Upon SIG_USR1, the program will
//kill child process #1 (mole1)
//randomly create either mole1 or mole 2 if it does not already exists

//When a new mole is created the following steps are followed:

//fork a new process                        (see fork(2))

//randomly determine the child process number (either 1 or 2)

//exec the program mole,
//with the value of argv[0] set to either            (see execv(2))
//mole1
//mole2

}//end sigusr1_handler


void sigusr2_handler(int signum)
{
//Upon SIG_USER2, the program will
//kill child process #1 (mole2)
//randomly create either mole1 or mole 2 if it does not already exists

//When a new mole is created the following steps are followed:

//fork a new process                        (see fork(2))

//randomly determine the child process number (either 1 or 2)

//exec the program mole,
//with the value of argv[0] set to either            (see execv(2))
//mole1
//mole2

}//end sigusr2_handler


void create_daemon()
{
//Local Variables
	int fd_0, fd_1, fd_2;
	pid_t child;
	struct rlimit cur;

//Set the file creation mask to 0                 (see umask(2))
	umask(0);

//Fork
	child = fork();

//Fork Error
	if(child < 0)
	{
		printf("Error: Fork Fail\n");
		exit(EXIT_FAILURE);
	}//end else

//Parent Process, have the parent terminate
	else if(child != 0)
	{
		exit(EXIT_SUCCESS);
	}//end if

//Child Process continues to run

//Create a new session                     (see setsid(2))
	setsid();

//create a new process group
	setpgid(getpid(), getsid(getpid()));

//Change the current working directory to be the root directory “~/”         (see chdir(2))
	chdir("~/");

//Get all file descriptors possibly inherited from parent or otherwise (see getrlimit(2))
	getrlimit(RLIMIT_NOFILE, &cur);

//Get the maximum amount of file descriptors
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
//Reopen fd 0
	fd_0 = open("/dev/null", O_RDWR);

//Error reopening file descriptors
	if(fd_0 != 0)
	{
		printf("Error: fd_0 %d\n", fd_0);
	}//end if

//Reopen fd 1
	fd_1 = dup(0);

//Error reopening file descriptors
	if(fd_1 != 1)
	{
		printf("Error: fd_1 %d\n", fd_1);
	}//end if

//Reopen fd 2
	fd_2 = dup(0);

//Error reopening file descriptors
	if(fd_2 != 2)
	{
		printf("Error: fd %d\n", fd_2);
	}//end if
}//end create_daemon

int main()
{
//Create daemon process
	create_daemon();

//Keep the daemon running
	while(1)
	{}//end while

	return 0;
}//end main
