//Launch file: a program that allows one to set in motion another program, while also report some basic information.
//launch or launch.c?

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//PROTOTYPES


void func()
{


}//end func

int main(int argc, char** argv)
{
	pid_t child, wpid;
	int status;

//The program forks a child process                (see fork(2)
	child = fork();

//The parent process prints the PID of the child on stderr
	if(child < 0)
	{
		printf("Error: CPID: %d\n", getpid());
	}//end if

//The child process executes the supplied command     (see execve(2))
	else
	{
	//Error
		if (argc <= 2) {
			fprintf(stderr, "Usage: %s <file-to-exec>\n", argv[0]);
			exit(EXIT_FAILURE);
		}//end if

		char *newenviron[] = { NULL };
		char *newargv[argc + 1];

	//the child needs to prepare the new argv structure
		for(int i = 0; i < argc; i++)
		{
			newargv[i] = argv[i];
		}//end for

		execve(argv[1], newargv, newenviron);

	//The parent prints the return value of the child on stderr    (see waitpid(2))
		wpid = waitpid(child, &status, WUNTRACED);

		if(wpid < 0)
		{
			printf("Error: %d\n", wpid);
		}//end if

	}//end else


//free pointers

	return 0;
}//end main
