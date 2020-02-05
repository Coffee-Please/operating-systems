//Lab 0 for COMP 322/L
//Created by Priya Singh on 1/29/2020

//convert

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>

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
		//Pad missing bytes
			while(rd < 9)
			{
				buffer[rd - 1] = '0';
				rd++;
			}//end for

			buffer[rd] = '\0';
			printf("%s\t", buffer);
			convert_ascii(buffer);
			convert_dec(buffer);

			break;
		}//end if

		buffer[rd] = '\0';

		printf("%s\t", buffer);

	//Conversions
		convert_ascii(buffer);

		convert_dec(buffer);

//		calc_parity();

	}//end while

//Close file
	close(fp);

	return 0;

}//end main


//CONVERT BINARY TO ASCII
void convert_ascii(char buffer[])
{

//Local Variables
	int hex = 0;
	int power = 6;

//Convert
	for(int i = 1; i < 8; i++)
	{
		hex += (buffer[i] - 48) * pow(2, power--);

	}//end for

//Check
	if(isascii(hex))
	{
	//Print
		printf("%c\t", hex);

	}//end if

	else
	{
	//Print
		printf("%x\t", hex);
	}//end else

}//end bin_to_ascii


//CONVERT BINARY TO DECIMAL
void convert_dec(char buffer[])
{
//Local Variables
	int dec = 0;
	int power = 6;

//Convert
	for(int i = 1; i < 8; i++)
	{
		dec += (buffer[i] - 48) * pow(2, power--);

	}//end for

//Print
	printf("%d\n", dec);

}//end bin_to dec


////CALCULATE PARITY BITS
//void calc_parity(char buffer[])
//{
////Local Variables
//	int parity_bit = 0;
//	int result = 0;
//
////Convert
//	for(int i = 0; parity_bit < 8; i++)
//	{
//		parity_bit = pow(2, i);
//		printf("parity bit: %d\n", parity_bit);
//
//
//		for(int j = 0; j < parity_bit; j++)
//		{
//			//go for parity bit # byte
//			result += 
//
//		}//end for
//
//		for()
//		{
//			//skip for parity bit # of bytes
//			
//		}//end for
//
//
//
//	}//end for
//
////Print
//
////	printf("ODD\n");
//
////	printf("EVEN\n");
//
//
//}//end calc_parity

//PRINT
