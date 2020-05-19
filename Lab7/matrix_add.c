//a program that performs matrix addition on a given matrix,
//and emits the amount of time to perform the operation on standard error.

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <aio.h>

unsigned int next, N;


int rand()
{
	next = ((next * 1234382) / 62235) % 12345;
	return next;
}//end rand

void srand(unsigned int seed)
{
	next = seed;
}//end srand


void matrix_add(int block[][N], int size, int scalar)
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
	int size = atoi(argv[1]);
	N = size;
	int blocks = atoi(argv[2]);

	time_t start, stop;
	int scalar = rand();
	int block_size = size / blocks;
	int block[block_size][block_size];

	struct aiocb* ptr;

//Check number of arguements
	if(argc != 3)
	{
		printf("Error: Args != 3\n");
		exit(EXIT_SUCCESS);
	}//end if


//Get start time
	time(&start);

	for(int x = 1; x < blocks; x++)
	{
		for(int y = 1; y < blocks; y++)
		{
		//Async read request matrix[x, y]

		//Read to block
			block[x][y] = aio_read(ptr);

			matrix_add(block, block_size, scalar);

		//Async write request block

		//Async write return block
			aio_write(ptr);

		}//end for
	}//end for

//Get end time
	time(&stop);

//Output the total amount of time for the process
	fprintf(stderr, "Total time: %ld\n", (stop - start));

	return 0;
}//end main
