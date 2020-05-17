//a program that performs matrix addition on a given matrix,
//and emits the amount of time to perform the operation on standard error.

#include <stdio.h>
#include <time.h>
#include <aio.h>

unsigned int next;

//void matrix_add(int block[][size], int size, int scalar);


int rand()
{
	next = ((next * 1234382) / 62235) % 12345;
	return next;
}//end rand

void srand(unsigned int seed)
{
	next = seed;
}//end srand


//void matrix_add(int[][size] block, int size, int scalar)
//{
//	for(int i = 0; i < size; i++)
//	{
//		for(int j = 0; j < size; j++)
//		{
//			block[i][j] += scalar;
//		}//end for
//	}//end for
//}//end matrix_add


int main(int argc, char** argv)
{
//Variables
	time_t start, stop;
	int size, blocks;
	int[][size] block;
	struct aiocb* read_buf;
	struct aiocb* write_buf;

	int scalar = rand();
	int block_size = size / blocks;

//Get start time
	time(&start);

	for(int i = 0; i < blocks; i++)
	{
		for(int j = 0; j < blocks; j++)
		{
		//async read request matrix[x, y]
			block = aio_read(fp_1, read_buf);

//			matrix_add(block, block_size, scalar);

			aio_write(write_buf);

		}//end for
	}//end for

//Get end time
	time(&stop);

//Output the total amount of time for the process
	printf("Total time: %ld\n", (stop - start));

	return 0;
}//end main
