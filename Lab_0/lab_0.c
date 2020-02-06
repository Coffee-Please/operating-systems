//Created by Priya Singh on 1/29/2020

#include <stdio.h>
#include <stdbool.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
//test argc argv to understand furthe -> binary vs file input.

//PROTOTYPES
bool error_1(int fp);
void format_and_print(char buffer[], int file_len);
void convert_ascii(char buffer[]);
void convert_dec(char buffer[]);
void calc_parity(char buffer[]);


int main(int num_of_args, char **args)
{
//Local Variables
	char infile[20];
	char buffer[100];
	int fp;
	int rd;
	int bytes = 100;

//If filename not provided, get filename using stdin
	if(num_of_args == 1)
	{
		printf("Enter File Name: ");

		fgets(infile, sizeof(infile), stdin);

		if(infile[strlen(infile) - 1] == '\n')
		{
			infile[strlen(infile) - 1] = '\0';
		}//end if

	//Open file
		fp = open(infile, O_RDONLY);

		//Does the file exist?
		if(error_1(fp))
		{
			printf("Error: File not found.\n");
			printf("Exiting....\n");

			return 0;
		}//end if

		//Get file size
			rd = read(fp, buffer, bytes);

			format_and_print(buffer, rd);
	}//end if

//else, arg[1] is the file name, or given binarys, or file name is - or not given
	else
	{
	//Open file
		fp = open(args[1], O_RDONLY);

		//if args[1] is a file
		if(!error_1(fp))
		{
		//Get file size
			rd = read(fp, buffer, bytes);

			format_and_print(buffer, rd);
		}//end if

		else
		{
		//binary
			int counter = 0;

			for(int i = 1; i < num_of_args; i++)
			{
				for(int j = 0; j < (int)strlen(args[i]); j++)
				{
					buffer[counter] = args[i][j];

					//Something other than binary  is in the string
					if(buffer[counter] != 49 && buffer[counter] != 48)
					{
						return 0;
					}//end if

					counter++;
				}//end for

				buffer[counter] = ' ';
				counter++;

			}//end for

			buffer[counter] = '\0';

			format_and_print(buffer, counter);
		}//end else
	}//end else

//Close file
	close(fp);

	return 0;
}//end main


//ERROR: File not found
bool error_1(int fp)
{
	if(fp == -1)
	{
		return true;
	}//end if

	return false;
}//end error_1


//FORMAT
void format()
{
	printf("Original\tASCII\tDecimal\tParity\n");
	printf("--------\t-----\t-------\t-------\n");
}//end format


//PRINT
void format_and_print(char buffer[], int file_len)
{
//Local Variables
	int cursor = 0;
	int reader;

	format();
//While it is not the end of the file

	while(buffer[cursor] != '\0' && buffer[cursor] != EOF && cursor != file_len)
	{
		int string_len = 0;
		int padding = 0;
		char binary[8];

	//Get the size of the possible sub array
		while(buffer[cursor] != ' ' && buffer[cursor] != '\n' && buffer[cursor] != '\0' && buffer[cursor] != EOF && cursor != file_len)
		{
			string_len++;
			cursor++;
		}//end for

		reader = cursor - 1;

	//if less than 8 bytes, pad
		if(string_len < 8)
		{
			while(string_len < 8)
			{
				binary[string_len] = '0';

				string_len++;
				padding++;
			}//end while
		}//end if

	//insert binary backwards
		for(int i = 7 - padding; i >= 0; i--)
		{
			binary[i] = buffer[reader--];

		}//end for

		printf("%s\t", binary);

	//Conversions
		convert_ascii(binary);
		convert_dec(binary);
		calc_parity(binary);

	//Reset
		string_len = 0;
		cursor++;

	}//end while
}//end print


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
	if(isascii(hex) && hex > 0x1F)
	{
	//Print
		printf("%c\t", hex);

	}//end if

	else
	{
	//Print all manually :(
	//hex = 0x1
		if(hex == 0x0)
		{
			printf("NUL\t");

		}//end if

	//hex = 0x1
		if(hex == 0x1)
		{
			printf("SOH\t");

		}//end if

	//hex = 0x2
		if(hex == 0x2)
		{
			printf("STX\t");

		}//end if

	//hex = 0x3
		if(hex == 0x3)
		{
			printf("ETX\t");

		}//end if

	//hex = 0x4
		if(hex == 0x4)
		{
			printf("EOT\t");

		}//end if

	//hex = 0x5
		if(hex == 0x5)
		{
			printf("ENQ\t");

		}//end if


	//hex = 0x6
		if(hex == 0x6)
		{
			printf("ACK\t");

		}//end if


	//hex = 0x7
		if(hex == 0x7)
		{
			printf("BEL\t");

		}//end if

	//hex = 0x8
		if(hex == 0x8)
		{
			printf("BS\t");

		}//end if

	//hex = 0x9
		if(hex == 0x9)
		{
			printf("HT\t");

		}//end if

	//hex = 0xA
		if(hex == 0xA)
		{
			printf("LF\t");

		}//end if

	//hex = 0xB
		if(hex == 0xB)
		{
			printf("VT\t");

		}//end if

	//hex = 0xC
		if(hex == 0xC)
		{
			printf("FF\t");

		}//end if

	//hex = 0xD
		if(hex == 0xD)
		{
			printf("CR\t");

		}//end if

	//hex = 0xE
		if(hex == 0xE)
		{
			printf("SO\t");

		}//end if

	//hex = 0xF
		if(hex == 0xF)
		{
			printf("SI\t");

		}//end if

	//hex = 0x10
		if(hex == 0x10)
		{
			printf("DLE\t");

		}//end if

	//hex = 0x11
		if(hex == 0X11)
		{
			printf("DC1\t");

		}//end if

	//hex = 0X12
		if(hex == 0X12)
		{
			printf("DC2\t");

		}//end if

	//hex = 0X13
		if(hex == 0X13)
		{
			printf("DC3\t");

		}//end if

	//hex = 0X14
		if(hex == 0X14)
		{
			printf("DC4\t");

		}//end if

	//hex = 0X15
		if(hex == 0X15)
		{
			printf("NAK\t");

		}//end if

	//hex = 0X16
		if(hex == 0X16)
		{
			printf("SYN\t");

		}//end if

	//hex = 0X17
		if(hex == 0X17)
		{
			printf("ETB\t");

		}//end if

	//hex = 0X18
		if(hex == 0X18)
		{
			printf("CAN\t");

		}//end if

	//hex = 0X19
		if(hex ==0X19)
		{
			printf("EM\t");

		}//end if

	//hex = 0X1A
		if(hex == 0X1A)
		{
			printf("SUB\t");

		}//end if

	//hex = 0X1B
		if(hex == 0X1B)
		{
			printf("ESC\t");

		}//end if

	//hex = 0X1C
		if(hex == 0X1C)
		{
			printf("FS\t");

		}//end if

	//hex = 0X1D
		if(hex == 0X1D)
		{
			printf("GS\t");

		}//end if

	//hex = 0X1E
		if(hex == 0X1E)
		{
			printf("RS\t");

		}//end if

	//hex = 0X1F
		if(hex == 0X1F)
		{
			printf("US\t");

		}//end if

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
	printf("%d\t", dec);

}//end bin_to dec


//CALCULATE PARITY BITS
void calc_parity(char buffer[])
{
//Local Variables
	int p_bit_1 = 0;
	int p_bit_2 = 0;
	int p_bit_4 = 0;
	int p_bit_8 = 0;
	int result = 0;

//Convert
//P1
	for(int i = 0; i < 8; i += 2)
	{
		p_bit_1 += (buffer[i] - 48);

	}//end for

//P2
	for(int i = 1; i < 8; i += 4)
	{
		for(int j = i; j <= 2; j++)
		{
			p_bit_2 += (buffer[j] - 48);

		}//end for

	}//end for

//P4
	for(int i = 3; i < 8; i += 4)
	{
		for(int j = i; j <= 4; j++)
		{
			p_bit_4 += (buffer[j] - 48);

		}//end for
	}//end for

//P8
	p_bit_8 += (buffer[7] - 48);

	result = p_bit_1 + p_bit_2 + p_bit_4 + p_bit_8;

//Print
	if(result % 2 == 0)
	{
		printf("EVEN\n");

	}//end if
	else
	{
		printf("ODD\n");

	}//end else
}//end calc_parity
