//a program that performs matrix addition on a given matrix,
//and emits the amount of time to perform the operation on standard error.

#include <stdio.h>
#include <time.h>

unsigned int next

int rand()
{
	next = ((next * 1234382) / 62235) % 12345;
	return next;
}//end rand

void srand(unsigned int seed)
{
	next = seed;
}//end srand

void matrix_add(int block, int size, int scalar)
{
	for(int i = 0; i < size; i++)
	{
		for(int j = 0; j < size; j++)
		{
			block[i][j] += scalar;
		}//end for
	}//end for
}//end matrix_add


int main(int argc, char** argv)
{
//Variables
	int size, blocks;

	int start_time = time(NULL);
	int scalar = rand();
	int block_size = size / blocks;

//for x = 1 .. blocks
	for(int i = 0; i < blocks; i++)
	{
		for(int j = 0; j < blocks; j++)
		{
		//async read request matrix[x, y]

		//block = async read return matrix[x, y]

		//matrix_add(block, block_size, scaler)

		//async write request block

		//async write return block

		}//end for
	}//end for

	int end_time = time(NULL);
	printf("%d\n", (end_time - start_time));

	return 0;
}//end main
