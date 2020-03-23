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
static char* str_arr[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "IOT",
	"BUS", "FPE", "KILL", "USR1", "SEGV", "USR2", "PIPE",
	"ALRM", "TERM", "STKFLT", "CHLD", "CONT", "STOP",
	"TSTP", "TTIN", "TTOU", "URG", "XCPU", "XFSZ", "VTALRM", "PROF",
	"WINCH", "IO", "PWR", "SYS"};


void handle_signal(int signal)
{
//The handler emits a line to stdout that indicates the signal caught, and
//the time it was caught                         (see time(2))
	printf("SIG%s caught at %ld\n", str_arr[signal - 1], time(NULL));

	count++;

//if the signal is sigterm
	if(signal == SIGTERM)
	{
		sigterm++;

	}//end if
}//end handle_signal


void make_catch_arr(int argc, char** argv, char* str_arr[], int catch_arr[])
{
	for(int i = 1; i < argc; i++)
	{
	//The arguments indicate which signals to catch
		for(int j = 0; j < 31; j++)//search through str_arr for string
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
	while(sigterm < 4)
	{
	//The program registers a handler for each argument                      (see signal(2))
		for(int i = 0; i < argc - 1; i++)
		{
		//The program registers a handler for each argument                      (see signal(2))
			signal(catch_arr[i], handle_signal);

		//The handler registers itself again            (read about unreliable signals)
			for(int j = 0; j < 31 && j != catch_arr[i]; j++)
			{
			//The handler registers itself again            (read about unreliable signals)
				signal(i, SIG_IGN);

			}//end for
		}//end for

	//The program pauses itself continually                   (see pause(2))
		pause();

	}//end while

}//end parse_signals


int main(int argc, char** argv)
{
//Local Variables
	int catch_arr[argc - 1];

//The program processes the command line arguments
	make_catch_arr(argc, argv, str_arr, catch_arr);

//The program emits a status line that includes its PID to stderr
	fprintf(stderr, "%s $$: %d\n", argv[0], getpid());

//The program gracefully terminates after
//receiving three successive SIGTERM signals       (hint: static int count)
	parse_signals(argc, catch_arr);

//The program emits a final status message to stderr that indicates
//the number of signals caught
	fprintf(stderr, "%s: Total signals count = %d\n", argv[0], count);

	return 0;
}//end main
