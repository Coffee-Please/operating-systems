//A program that catches a number of predefined signals, and prints status information on stdout.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>

static int sigterm;
static int count;
char* str_arr[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT",
	"BUS", "FPE", "KILL", "USR1", "SEGV", "USR2", "PIPE",
	"ALRM", "TERM", "STKFLT", "CHLD", "CONT", "STOP",
	"TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF",
	"WINCH", "IO", "PWR", "SYS", "WAITING", "LWP", "RTMIN", "RTMIN+1", "RTMIN+2", "RTMIN+3",
	"RTMIN+4", "RTMIN+5", "RTMIN+6", "RTMIN+7", "RTMIN+8", "RTMIN+9", "RTMIN+10",
	"RTMIN+11", "RTMIN+12", "RTMIN+13", "RTMIN+14", "RTMIN+15", "RTMAX-14", "RTMAX-13",
	"RTMAX-12", "RTMAX-11", "RTMAX-10", "RTMAX-9", "RTMAX-8", "RTMAX-7", "RTMAX-6",
	"RTMAX-5", "RTMAX-4", "RTMAX-3", "RTMAX-2", "RTMAX-1", "RTMAX"};

void parse_signals(int argc, int catch_arr[]);
void make_catch_arr(int argc, char** argv, int catch_arr[]);
void handle_signal(int signal);


int main(int argc, char** argv)
{
//Local Variables
	int catch_arr[argc - 1];

//The program processes the command line arguments
	make_catch_arr(argc, argv, catch_arr);

//The program emits a status line that includes its PID to stderr
	fprintf(stderr, "%s $$: %d\n", argv[0], getpid());

//The program catches signals
	parse_signals(argc, catch_arr);

//The program emits a final status message to stderr that indicates
//the number of signals caught
	fprintf(stderr, "%s: Total signals count = %d\n", argv[0], count);

	return 0;
}//end main

void handle_signal(int sig)
{
//The handler registers itself again            (read about unreliable signals)
	signal(sig, handle_signal);

//The handler emits a line to stdout that indicates the signal caught, and the
//time it was caught		(see time(2))
	printf("SIG%s caught at %ld\n", str_arr[sig - 1], time(NULL));

	count++;//Increment signals caught

//if the signal is sigterm
	if(sig == SIGTERM)
	{
		sigterm++;

	}//end if
}//end handle_signal


void make_catch_arr(int argc, char** argv, int catch_arr[])
{
	for(int i = 1; i < argc; i++)
	{
	//The arguments indicate which signals to catch
		for(int j = 0; j < 64; j++)//search through str_arr for string
		{
			if(strcmp(str_arr[j], argv[i]) == 0)
			{
				catch_arr[i - 1] = j + 1;//store int in catch_arr
				break;
			}//end if
		}//end for
	}//end for
}//end make_char_arr


void parse_signals(int argc, int catch_arr[])
{
//The program gracefully terminates after
//receiving three successive SIGTERM signals       (hint: static int count)
	while(sigterm < 4)
	{
		for(int j = 0; j < 64; j++)
		{
		//Ignore all signals
			signal(j, SIG_IGN);

		}//end for

		for(int i = 0; i < argc - 1; i++)
		{
		//The program registers a handler for each argument   (see signal(2))
			signal(catch_arr[i], handle_signal);

		}//end for

	//The program pauses itself continually                   (see pause(2))
		pause();

	}//end while
}//end parse_signals
