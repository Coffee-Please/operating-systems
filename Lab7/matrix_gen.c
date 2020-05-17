//a program that creates a file of integers that represents a NxN matrix.

#include <stdio.h>

int next;

//Generates random number
int rand()
{
	next = (((next * 1234022) / 12345) % 37842);
	return next;
}//end rand

//Seeds srand
void srand(int seed)
{
	next = seed;
}//end srand


int main(int argc, char** argv)
{
//Variables
	FILE* fp;
	int num, size_1, size_2;

//Converts args into ints

//Seed srand
	srand(time(NULL));

//Open file
	fp = fopen("file.txt", "a");

//For size x size integers
	for(int i = 0; i < (size_1 * size_2); i++)
	{
	//Generate random numbers from -100 to 100
		num = ((rand() % 200) + 1) - 100;

	//Write to file
		fputs(fp, num, "a");
	}//end for

//close file
	fclose(fp);

	return 0;
}//end main
