//a program that is intended to run as a daemon, and based upon signals
//will either create or destroy child processes.

#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <unistd.h>
#include <sys/time.h>
#include <fcntl.h>
#include <sys/resource.h>
#include <stdlib.h>
#include <signal.h>
#include <time.h>

pid_t mole_child;
unsigned int child_alive;
unsigned int next;
int status;

void create_mole();


//Generating rand
int rand()
{
	return next;
}//end rand


//Seeding srand
void srand(unsigned int seed)
{
	next = seed;
}//end srand


//The daemon handles: SIG_TERM
void sigterm_handler(int signum)
{
//Reregister handler
	signal(SIGTERM, sigterm_handler);

	if(mole_child != 0)
	{
	//kills child process
		kill(mole_child, SIGTERM);
	}//end if

//Indicate signal received in log since printf doesn't work
	FILE* fp = fopen("lab6.log", "a");
	fprintf(fp, "SID: %d | Signal SIGTERM (%d) received.\n", getsid(getpid()), signum);
	fclose(fp);

//shutdowns the daemon gracefully.                     (see kill(2))
	exit(EXIT_SUCCESS);
}//end sigterm_handler


//The daemon handles: SIG_USR1
void sigusr1_handler(int signum)
{
//Reregister handler
	signal(SIGUSR1, sigusr1_handler);

//Indicate signal received
	FILE* fp = fopen("lab6.log", "a");
	fprintf(fp, "SID: %d | Signal SIGUSR1 (%d) received.\n", getsid(getpid()), signum);

//kill child process #1 (mole1) if it exists
	if(mole_child != 0)
	{
		kill(mole_child, SIGTERM);
	}//end if

	fclose(fp);

//Create mole
	create_mole();
}//end sigusr1_handler


//The daemon handles: SIG_USR2
void sigusr2_handler(int signum)
{
//Reregister handler
	signal(SIGUSR2, sigusr2_handler);

//Indicate signal received
	FILE* fp = fopen("lab6.log", "a");
	fprintf(fp, "SID: %d | Signal SIGUSR2 (%d) received.\n", getsid(getpid()), signum);

//kill child process #1 (mole1) if it exists
	if(mole_child != 0)
	{
		kill(mole_child, SIGTERM);
	}//end if

	fclose(fp);

//Create mole
	create_mole();
}//end sigusr2_handler


//Create a new mole
void create_mole()
{
//fork a new process                        (see fork(2))
	mole_child = fork();

//Randomly choose if child process number is 1 or 2
	child_alive = (rand() % 2) + 1;

//If the child process is 1
	if(child_alive == 1)
	{
	//Set the argv[0] to mole1
		char* argv[] = {"mole1", NULL};

	//Exec the program mole,
		execv("mole", argv);
	}//end if

//Else, child process is 2
	if(child_alive == 2)
	{
	//Set argv[0] to mole2
		char* argv[] = {"mole2", NULL};

	//Exec the program mole,
		execv("mole", argv);
	}//end else
}//end create mole


//Creates the daemon process
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

//Fork Again so process is not the session leader
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
	fd_1 = dup(fd_0);
	fd_2 = dup(fd_0);

//Error reopening file descriptor
	if(fd_0 != 0 || fd_1 != 1 || fd_2 != 2)
	{
		printf("Error: fd 0|%d 1|%d 2|%d\n", fd_0, fd_1, fd_2);
	}//end if


//Register signal handlers
	signal(SIGTERM, sigterm_handler);
	signal(SIGUSR1, sigusr1_handler);
	signal(SIGUSR2, sigusr2_handler);
}//end create_daemon


int main()
{
//Seed srand
	srand(time(NULL));

//Create daemon process
	create_daemon();

//Keep the daemon running
	while(1)
	{}//end while

	exit(EXIT_SUCCESS);
}//end main
