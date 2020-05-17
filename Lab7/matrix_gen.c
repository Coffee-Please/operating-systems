//a program that creates a file of integers that represents a NxN matrix.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

unsigned int next;

//Generates random number
int rand()
{
	next = (((next * 1234022) / 12345) % 37842);
	return next;
}//end rand

//Seeds srand
void srand(unsigned int seed)
{
	next = seed;
}//end srand


int main(int argc, char** argv)
{
//Variables
	int num, size;

//Check the number of args
	if(argc != 2)
	{
		printf("Error: Argc != 2\n");
		exit(EXIT_SUCCESS);
	}//end if

//Converts args into ints
	size = atoi(argv[1]);

//Seed srand
	srand(time(NULL));

//For size x size integers
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size - 1; j++)
		{
		//Generate random numbers from -100 to 100
			num = ((rand() % 200) + 1) - 100;

		//Write to file
			printf("%d ", num);
		}//end for

		printf("%d\n", num);
	}//end for
	return 0;
}//end main
