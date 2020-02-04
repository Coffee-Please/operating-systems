//Lab 0 for COMP 322/L
//Created by Priya Singh on 1/29/2020

//read 8bits; pad if necessary -> convert -> repeat while !EOF

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main(int num_of_args, char **args)
{
//Local Variables
	char infile[10];
	char buffer[10];
	int fp;
	int rd;

//If filename not provided, get filename
	if(num_of_args == 1)
	{
		printf("Enter File Name: ");
		scanf("%s", &infile);
		printf("%s\n", infile);

	//Open file
		fp = open(infile, O_RDONLY);
		printf("fp :%d\n", fp);

	//Does the file exist?
		if(fp == -1)
		{
			printf("Error: File not found.\n");
			printf("Exiting....\n");

		}//end if
	}//end if

//else, arg[1] is the file name
	else
	{
	//Open file
		fp = open(args[1], O_RDONLY);

	//Does the file exist?
		if(fp == -1)
		{
			printf("Error: File not found.\n");
			printf("Exiting....\n");

		}//end if
	}//end else

//Format
	printf("Original\tASCII\tDecimal\tParity\n");
	printf("--------\t-----\t-------\t-------\n");

//While, !EOF, read and convert
	while(rd != 0)
	{
	//Read file
		rd = read(fp, buffer, 9);

		if(rd < 9)
		{
//		//Pad to size---------------------------------------------------------
//			for(int i = rd + 1; i < 9; i++)
//			{
//				buffer[i] = '0';
//			}//end for

			buffer[rd] = '\0';
			printf("%s\n", buffer);

			break;
		}//end if

		buffer[9] = '\0';

		printf("%s\n", buffer);
	}//end while

	//Conversions
	//bin_to_dec();

	//bin_to_ascii();

	//calc_parity()

	//check_true_false();

//Close file
//	close(fp);

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
