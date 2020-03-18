//A program that catches a number of predefined signals, and prints status information on stdout.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>

void handle_signal(int signal)
{
//	char* sig_name[8] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT",
//		"SIGUSR1", "SIGUSR2"};

//The handler emits a line to stdout that indicates
//the signal caught, and
//the time it was caught                         (see time(2))
	printf("%d caught at %ld\n", signal, time(NULL));

}//end handle_signal

int main(int argc, char** argv)
{
//Local Variables
	char** signals[argc];//make dynamic w/ malloc
	int sigterm = 0, count = 0;

//The program emits a status line that includes its PID to stderr
	fprintf(stderr, "%s $$: %d\n", argv[0], getpid());

//The program processes the command line arguments
	for(int i = 1; i < argc; i++)
	{
	//The arguments indicate which signals to catch

	}//end for


//The program registers a handler for each argument                      (see signal(2))
	signal(SIGINT, handle_signal);
	count++;

//The program pauses itself continually                   (see pause(2))
	pause();

	while(sigterm < 3)
	{
	//The program gracefully terminates after
	//receiving three successive SIGTERM signals       (hint: static int count)
		if(sigterm == 3)
		{
			break;
		}//end if

	//The handler registers itself again            (read about unreliable signals)
		signal(SIGINT, handle_signal);
		count++;

	//The program pauses itself continually                   (see pause(2))
		pause();

		sigterm++;

	}//end while

//The program emits a final status message to stderr that indicates
//the number of signals caught
	fprintf(stderr, "%s: Total signals count = %d\n", argv[0], count);

	return 0;
}//end main
