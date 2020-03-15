//Launch file: a program that allows one to set in motion another program, while also report some basic information.
//launch or launch.c?

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

//PROTOTYPES
void child_proc(int argc, char** argv);

int main(int argc, char** argv)
{
	pid_t child;
	int status;

//Error
	if (argc <= 1) {
		fprintf(stderr, "Error: Usage: %s Not enough args\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

//The program forks a child process                (see fork(2)
	child = fork();

//Parent
	if(child > 0)
	{
	//The parent process prints the PID of the child on stderr
		fprintf(stderr, "%s: $$ = %d\n", argv[1], getpid());

	//The parent prints the return value of the child on stderr    (see waitpid(2))
		waitpid(child, &status, WUNTRACED);
		fprintf(stderr, "%s: $? = %d\n", argv[1], status);
	}//end if

//The child process executes the supplied command     (see execve(2))
	else if(child == 0){
		child_proc(argc, argv);
	}//end if

//Else, fork failed
	else
	{
		printf("Fork Failed\n");
	}//end else

	return 0;
}//end main

void child_proc(int argc, char** argv)
{
	char *newargv[argc];

//the child needs to prepare the new argv structure
	for(int i = 1; i - 1 < argc; i++)
	{
		newargv[i - 1] = argv[i];
	}//end for

	execve(argv[1], newargv, NULL);

//Error
	perror("execve");   /* execve() returns only on error */
       	exit(EXIT_FAILURE);
}//end child_proc
