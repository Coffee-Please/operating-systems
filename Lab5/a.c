//Lab 5 | Page/Offset Calculation
//Priya Singh | Spring 2020

#include <stdio.h>
#include <stdlib.h>

//Global Variables
unsigned int addr,
	pg_num,
	offset;

//Print results
void print_results()
{
//Print everythng to console
	printf("The address %d contains:\n", addr);
	printf("page number = %d\n", pg_num);
	printf("offset = %d\n", offset);

}//end print_results


//Calculate page number
void calc_pg_num(unsigned int pg_size)
{
//Page number is the quotient of the address divided by the page size
	pg_num = addr / pg_size;
}//end calc_pg_num


//Calculate offset
void calc_offset(unsigned int pg_size)
{
//Page offset is the remainder of the address divided by the page size
	offset = addr % pg_size;
}//end calc_offset


//Main
int main(int argc, char** argv)
{
//Local Variables
	unsigned int pg_size = 4096;//page size is 4KB

//There should be only 1 arg
	if(argc != 2)
	{
		printf("Error: Too many args\n");
		exit(EXIT_FAILURE);
	}//end if

//Convert argv[1] to int for memory address
	addr = atoi(argv[1]);

//Calculate page number
	calc_pg_num(pg_size);

//Calculate offset
	calc_offset(pg_size);

//Print results
	print_results();

	return 0;
}//end main
