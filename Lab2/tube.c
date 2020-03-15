//Tube file: a program that sets to programs into motion that are connected via a tube that transports
//inter-process communication, while also report some basic information.

#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>
#include <string.h>

#define READ_END 0
#define WRITE_END 1

//Prototypes
void make_buffers(char** argv, int argc, char** buff_1, char** buff_2);

int main(int argc, char** argv){
	pid_t child_1, child_2;
	int status_1, status_2;
	int pipefd[2];
	char* buff_1[100];
	char* buff_2[100];

//Error argc invaild
	if (argc <= 3) {
		fprintf(stderr, "Error: Usage: %s Not enough args\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if
//No Error, proceed to create the buffers
	else
	{
		make_buffers(argv, argc, buff_1, buff_2);
	}//end else

//The program allocates a pipe                     (see pipe(2))
	if(pipe(pipefd) == -1)
	{
	//Error pipe failed
		fprintf(stderr, "Error: Usage: %s Pipe failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

//The program forks two child processes
	child_1 = fork();

//Error fork fail
	if(child_1 < 0)
	{
		fprintf(stderr, "Error: Usage: %s fork 1 failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

	child_2 = fork();
//child_2 = -1;

//Error fork fail
	if(child_2 < 0)
	{
		fprintf(stderr, "Error: Usage: %s fork 2 failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

//Parent
	if(child_1 > 0 && child_2 > 0)
	{
	//The parent process prints the PID of both children on stderr     (see fprintf(3))
		fprintf(stderr, "child 1 %s: $$ = %d\n", buff_1[0], child_1);
		fprintf(stderr, "child 2 %s: $$ = %d\n", buff_2[0], child_2);

	//The parent process closes access to the pipe and
		close(pipefd[READ_END]);//close read end

		write(pipefd[WRITE_END], buff_1, sizeof(buff_1));
		write(pipefd[WRITE_END], buff_2, sizeof(buff_2));

		close(pipefd[WRITE_END]);//close write end

		waitpid(child_1, &status_1, WUNTRACED);
		waitpid(child_2, &status_2, WUNTRACED);

	//The program prints the return value of the first child and then the second
	//child on stderr
		fprintf(stderr, "child 1 %s: $? = %d\n", buff_1[0], status_1);
		fprintf(stderr, "child 2 %s: $? = %d\n", buff_2[0], status_2);
	}//end if

//First child
	else if(child_1 == 0 && child_2 > 0)
	{
	//the child processes wires the pipe to allow for inter-process communication (see dup2(2))
	//via the standard stdout-stdin approach (see close(2))

		dup2(pipefd[READ_END], READ_END);//duplicate read end of the pipe

		close(pipefd[WRITE_END]);//close write end

		read(pipefd[READ_END], buff_1, sizeof(buff_1));//read data from parent
		close(pipefd[READ_END]);//close read end

		char *newargv[sizeof(buff_1)];

	//the child needs to prepare the new argv structure
		for(size_t i = 0; i < sizeof(buff_1); i++)
		{
			newargv[i] = buff_1[i];
		}//end for

		execve(buff_1[0], newargv, NULL);

	//Error
		fprintf(stderr, "Error: Usage: %s Exec 1 failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

//Second child
	else if(child_2 == 0 && child_1 > 0)
	{
	//the child processes wires the pipe to ahllow for inter-process communication (see dup2(2))
	//via the standard stdout-stdin approach (see close(2))

		dup2(pipefd[READ_END], READ_END);

		close(pipefd[WRITE_END]);//close write end

		read(pipefd[READ_END], buff_2, sizeof(buff_2));//read data from parent
		close(pipefd[READ_END]);//close read end

		char *newargv[sizeof(buff_2)];

	//the child needs to prepare the new argv structure
		for(size_t i = 0; i < sizeof(buff_2); i++)
		{
			newargv[i] = buff_2[i];
		}//end for

		execve(buff_2[0], newargv, NULL);

	//Error
		fprintf(stderr, "Error: Usage: %s Exec 2 failed\n", argv[0]);
		exit(EXIT_FAILURE);
	}//end if

	return 0;
}//end main


//Creates the buffers to hold the first and second command line args
void make_buffers(char** argv, int argc, char** buff_1, char** buff_2)
{
//Buffer to hold first half of argv
	int i = 0;
	int j = 0;
	int k = 0;
	while(strcmp(argv[i], ",") != 0)
	{
		i++;

		if(strcmp(argv[i], ",") == 0)//is it the ","?
		{
			i++;
			break;
		}//end if
		else//no, store arg in buffer
		{
			buff_1[j] = argv[i];
			j++;
		}//end else
	}//end while

//Buffer to hold second half of argv
	while(i < argc)
	{
		buff_2[k] = argv[i];//store arg in buffer

		i++;
		k++;

		if(i >= argc)//we are at the end of the list
		{
			break;
		}//end if
	}//end while
}//end make_buffers
