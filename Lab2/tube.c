//Tube file: a program that sets to programs into motion that are connected via a tube that transports
//inter-process communication, while also report some basic information.

//draw out what needs to be done.
//pipe -> processes -> parse args -> exec -> fin

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>

int main(int argc, char** argv){
	pid_t child_1, child_2;
	int status_1, status_2;
	int pipefd[2];

//Error
	if (argc <= 1) {
		fprintf(stderr, "Error: Usage: %s Not enough args\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

//The program allocates a pipe                     (see pipe(2))
//Error
	if (pipe(pipefd) == -1) {
		fprintf(stderr, "Error: Usage: %s Pipe failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

//The program forks two children

	child_1 = fork();
	child_2 = fork();

//Parent
	if(child_1 > 0 && child_2 > 0)
	{
	//The parent process prints the PID of both children on stderr     (see fprintf(3))
		fprintf(stderr, "child 1 %s: $$ = %d\n", argv[1], getpid());
		fprintf(stderr, "child 2 %s: $$ = %d\n", argv[2], getpid());

	//The parent process closes access to the pipe and
		close(pipefd[0]);

	//The program prints the return value of the first child and then the second child on stderr
		waitpid(child_1, &status_1, WUNTRACED);
		fprintf(stderr, "child 1 %s: $? = %d\n", argv[1], status_1);

		waitpid(child_2, &status_2, WUNTRACED);
		fprintf(stderr, "child 2 %s: $? = %d\n", argv[2], status_2);

		close(pipefd[1]);
	}//end else if

//The first process executes the first command, and the second process executes the second command                          (see execve(2))
//for the first iteration keep it simple — i.e., the child has no command line args
//enhance your program to allow for an arbitrary number of command line args

//First child
	else if(child_1 == 0 && child_2 > 0)
	{
	//the child processes wires the pipe to allow for inter-process communication (see dup2(2))
	//via the standard stdout-stdin approach (see close(2))
		dup2(pipefd[1], 1);

		char *newargv[argc];

//fix	//the child needs to prepare the new argv structure
		for(int i = 1; i - 1 < argc; i++)
		{
			newargv[i - 1] = argv[i];
		}//end for

		execve(argv[1], newargv, NULL);

	//Error
		fprintf(stderr, "Error: Usage: %s Exec 1 failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end else if

//Second child
	else if(child_1 > 0 && child_2 == 0)
	{
	//the child processes wires the pipe to allow for inter-process communication (see dup2(2))
	//via the standard stdout-stdin approach (see close(2))
		dup2(pipefd[1], 1);

		char *newargv[argc];

//fix	//the child needs to prepare the new argv structure
		for(int i = 1; i - 1 < argc; i++)
		{
			newargv[i - 1] = argv[i];
		}//end for

		execve(argv[2], newargv, NULL);

	//Error
		fprintf(stderr, "Error: Usage: %s Exec 2 failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end else if

//Else fork failed
	else
	{
		fprintf(stderr, "Error: Usage: %s Fork failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end else

	return 0;
}//end main
