//a program that performs matrix addition on a given matrix,
//and emits the amount of time to perform the operation on standard error.

#include <stdio.h>
#include <time.h>
#include <aio.h>

unsigned int next;

void matrix_add(int block[][size], int size, int scalar);


int rand()
{
	next = ((next * 1234382) / 62235) % 12345;
	return next;
}//end rand

void srand(unsigned int seed)
{
	next = seed;
}//end srand


void matrix_add(int block[][], int size, int scalar)
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
	int blocks = atoi(argv[2]);

	int[][] read_buf;
	int[][] write_buf;

	time_t start, stop;
	int scalar = rand();
	int block_size = size / blocks;

//Get start time
	time(&start);

	for(int x = 1; x < blocks; x++)
	{
		for(int y = 1; y < blocks; y++)
		{
		//async read request matrix[x, y]
			aio_read();

		//Read to block
			int block[x][y] = read(fp_1, read_buf, "a");

			matrix_add(block, block_size, scalar);

		//Async write request block
			aio_write(fp_2, write_buf, "a");

		//Async write return block

		}//end for
	}//end for

//Get end time
	time(&stop);

//Output the total amount of time for the process
	fprintf(stderr, "Total time: %ld\n", (stop - start));

	return 0;
}//end main
