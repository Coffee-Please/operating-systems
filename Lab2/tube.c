//Tube file: a program that sets to programs into motion that are connected via a tube that transports
//inter-process communication, while also report some basic information.
//tube.c or tube??

#include <stdio.h>
#include <unistd.h>

int main(int argc, char** argv){
	pid_t child_1, child_2;

//The program allocates a pipe                     (see pipe(2))
	pipe();

//The program forks two children
	child_1 = fork();
	child_2 = fork();

//The parent process prints the PID of both children on stderr     (see fprintf(3))
	if(child_1 == 0 && child_2 == 0)
	{
		fprint(stderr, "%s: $$ = %d", child_1);
		fprint(stderr, "%s: $$ = %d", child_2);
	}//end if


//The parent process closes access to the pipe and the child processes wires the pipe to allow for inter-process communication            (see dup2(2))
//via the standard stdout-stdin approach            (see close(2))

//The first process executes the first command, and the second process executes the second command                          (see execve(2))
//for the first iteration keep it simple — i.e., the child has no command line args
//enhance your program to allow for an arbitrary number of command line args

//The program prints the return value of the first child and then the second child on stderr

	return 0;
}//end main

void func(){

}//end func
