//A program that catches a number of predefined signals, and prints status information on stdout.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>


void handle_signal(int signal)
{
	char* sig_name[31] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT",
		"SIGEMT", "SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV", "SIGSYS", "SIGPIPE",
 		"SIGALARM", "SIGTERM", "SIGURG", "SIGSTOP", "SIGTSTP", "SIGCONT", "SIGCHLD",
		"SIGTTIN", "SIGTTOU", "SIGIO", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF",
		"SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2"};

//The handler emits a line to stdout that indicates
//the signal caught, and
//the time it was caught                         (see time(2))
	printf("%s caught at %ld\n", sig_name[signal], time(NULL));

}//end handle_signal

int main(int argc, char** argv)
{
//Local Variables
	int sigterm = 0, count = 0;

	enum sig_arr{HUP, INT, QUIT, ILL, TRAP, ABRT,
		EMT, FPE, KILL, BUS, SEGV, SYS, PIPE,
		ALARM, TERM, URG, STOP, TSTP, CONT, CHLD,
		TTIN, TTOU, IO, XCPU, XFSZ, VTALRM, PROF,
		WINCH, INFO, USR1, USR2};

	enum sig_arr sig;

	char* str_arr[] = {"HUP", "INT", "QUIT", "ILL", "TRAP", "ABRT",
		"EMT", "FPE", "KILL", "BUS", "SEGV", "SYS", "PIPE",
 		"ALARM", "TERM", "URG", "STOP", "TSTP", "CONT", "CHLD",
		"TTIN", "TTOU", "IO", "XCPU", "XFSZ", "VTALRM", "PROF",
		"WINCH", "INFO", "USR1", "USR2"};

	int catch_arr[argc - 1];

//The program processes the command line arguments
	for(int i = 1; i < argc; i++)
	{
	//The arguments indicate which signals to catch
		for(int j = 0; j < 31; j++)//search through str_arr for string
		{
			if(strcmp(str_arr[j], argv[i]) == 0)
			{
				catch_arr[i - 1] = j;//store int in catch_arr

				break;
			}//end if
		}//end for
	}//end for



//The program emits a status line that includes its PID to stderr
	fprintf(stderr, "%s $$: %d\n", argv[0], getpid());

	while(sigterm < 3)
	{
	//The program gracefully terminates after
	//receiving three successive SIGTERM signals       (hint: static int count)

	//The program registers a handler for each argument                      (see signal(2))
	//The handler registers itself again            (read about unreliable signals)
		if(signal(sig, handle_signal) != SIG_ERR)
		{
			count++;

		//if sigterm
			if(sig == SIGTERM)
			{
				sigterm++;

			}//end if

			if(sigterm == 3)
			{
				break;

			}//end if
		}//end if

	//The program pauses itself continually                   (see pause(2))
		pause();

	}//end while

//The program emits a final status message to stderr that indicates
//the number of signals caught
	fprintf(stderr, "%s: Total signals count = %d\n", argv[0], count);

	return 0;
}//end main
