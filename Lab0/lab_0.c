//Created by Priya Singh on 1/29/2020
//Finished 2/15/2020

#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <ctype.h>
#include <math.h>
#include <string.h>

//PROTOTYPES
void format_and_print(char buffer[], int file_len);
void convert_ascii(int dec);
void convert_dec(char buffer[]);
void calc_parity(char buffer[]);


int main(int num_of_args, char **args)
{
//Local Variables
	char buffer[100];
	int fp;
	int rd;
	int bytes = 100;

//Open file
	fp = open(args[1], O_RDONLY);

//If filename not provided, get filename using stdin
	if(num_of_args <= 1 || (num_of_args == 2 && fp == -1))
	{
		printf("Error: Insufficient Data.\n");
		printf("Exiting....\n");

		return 0;
	}//end if

//else, arg[1] is the file name, or given binarys, or file name is - or not given
	else
	{
		//if args[1] is a file
		if(fp != -1)
		{
		//Get file size
			rd = read(fp, buffer, bytes);
			format_and_print(buffer, rd);
		}//end if

		//binary is inputted
		else
		{
			int counter = 0;
			int i = 1;
		//arg[1] = - or " "
			if(strcmp(args[i], "-") == 0 || strcmp(args[i], " ") == 0)
			{
				i++;
			}//end if

			for(; i < num_of_args; i++)
			{
				for(int j = 0; j < (int)strlen(args[i]); j++)
				{
					buffer[counter] = args[i][j];

					//Something other than binary  is in the string
					if(buffer[counter] != 49 && buffer[counter] != 48)
					{
						printf("Error: Incorrect Data.\n");
						printf("Exiting....\n");

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


//PRINT
void format_and_print(char buffer[], int file_len)
{
//Local Variables
	int cursor = 0;
	int reader;

	printf("Original\tASCII\tDecimal\tParity\n");
	printf("--------\t-----\t-------\t-------\n");

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
		convert_dec(binary);

		calc_parity(binary);

	//Reset
		string_len = 0;
		cursor++;

	}//end while
}//end print


//CONVERT BINARY TO DECIMAL
void convert_dec(char binary[])
{
//Local Variables
	int dec = 0;
	int power = 6;

//Convert
	for(int i = 1; i < 8; i++)
	{
		dec += (binary[i] - 48) * pow(2, power--);
	}//end for

//Print
	printf("%d\t", dec);

	convert_ascii(dec);

}//end bin_to dec


//CONVERT BINARY TO ASCII
void convert_ascii(int hex)
{
	char *mnemonic[33] = {"NUL","SOH", "STX", "ETX","EOT", "ENQ", "ACK", "BEL", "BS", "TAB",
		"LF", "VT", "FF", "CR", "SO", "SI", "DLE", "DC1", "DC2", "DC3", "DC4", "NAK", 
		"SYN", "ETB", "CAN", "EM", "SUB", "ESC", "FS", "GS", "RS", "US", "SPACE"};

//Check
	if(isascii(hex) && hex > 0x20 && hex != 0x7F)
	{
	//Print
		printf("%c\t", hex);
	}//end if

	else if(isascii(hex) && hex == 0x7F)
	{
	//Print
		printf("DEL\t");
	}//end else if

	else
	{
		printf("%s\t", mnemonic[hex]);
	}//end else

}//end bin_to_ascii


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
