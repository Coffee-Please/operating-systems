//Lab 0 for COMP 322/L
//Created by Priya Singh on 1/29/2020

//open file -> read 8bits; pad if necessary -> convert -> repeat while !EOF

#include <stdio.h>

int main(int num_of_args, char **args)
{
//Local Variables
	char infile[20];
	FILE *fp;

//If filename not provided, get filename
	if(num_of_args == 1)
	{
		printf("Enter File Name: ");
		scanf("%s", &infile);
		printf("%s\n", infile);

	//Open file
		fp = fopen(infile, "r");

	//Does the file exist?
		if(fp == NULL)
		{
			printf("Error: File not found.\n");
			printf("Exiting....\n");

		}//end if

	//Read file

	}//end if

//else, arg[1] is the file name
	else
	{
	//Open file
		fp = fopen(args[1], "r");

	//Does the file exist?
		if(fp == NULL)
		{
			printf("Error: File not found.\n");
			printf("Exiting....\n");

		}//end if

	//Read file

	}//end else



//Format
	printf("Original\tASCII\tDecimal\tParity\tT.Error\n");
	printf("--------\t-----\t-------\t------\t-------\n");

//Conversions
//bin_to_dec();

//bin_to_ascii();

//calc_parity()

//check_true_false();

//Close file
	fclose(fp);

	return 0;

}//end main

//Read file

	//Pad missing length

//Convert to ASCII
//Check isascii()
//else -> man isascii

//Convert to Decimal

//Parity Bit

//Determine True/False
