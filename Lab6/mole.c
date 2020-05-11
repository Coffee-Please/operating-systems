//a program that emits the following messages to ~/lab6.log
//- fprintf(logfile, “Pop %s\n”, argv[0]);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
//Local variables
	FILE* fp;

//Check the number of args
	if(argc != 1)
	{
		printf("Error: Argc != 1\n");
		exit(EXIT_FAILURE);
	}//end if

//Open file in appending mode
	fp = fopen( "lab6.log", "a");

//Print to file
	fprintf(fp, "Pop %s\n", argv[0]);

//Close file
	fclose(fp);

	return 0;
}//end main
