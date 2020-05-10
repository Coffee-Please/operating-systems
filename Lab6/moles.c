//a program that emits the following messages to ~/lab6.log
//- fprintf(logfile, “Pop %s\n”, argv[0]);

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char** argv)
{
//Local variables
	FILE* fp;
	char input[500];

//Check the number of args
	if(argc != 2)
	{
		printf("Error: Argc != 1\n");
		exit(EXIT_FAILURE);
	}//end if

//Open file in appending mode
	fp = fopen( "lab6.log", "a");

//Create file input
	strcpy(input, "Pop ");
	strcat(input, argv[1]);
	strcat(input, "\n");

//Write to file
	fputs(input, fp);

//Close file
	fclose(fp);

	return 0;
}//end main
