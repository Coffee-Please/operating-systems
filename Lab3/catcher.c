//A program that catches a number of predefined signals, and prints status information on stdout.

#include <stdio.h>
#include <signal.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
//
//#define HUP 1
//#define INT 2
//#define QUIT 3
//#define ILL 4
//#define TRAP 5
//#define ABRT
//#define EMT 7
// 8 -> SIGFPE 8
// 9 -> SIGKILL 9
//10 -> SIGBUS 10
//11 -> SIGSEGV 11
//12 -> SIGSYS 12
//13 -> SIGPIPE 13
//#define ALRM 14
//#define TERM 15
//#define URG 16
//17 -> SIGSTOP
//18 -> SIGTSTP
//19 -> SIGCONT
//20 -> SIGCHLD
//21 -> SIGTTIN 21
//22 -> SIGTTOU 22
//23 -> SIGIO 23
//24 -> SIGXCPU 24
//25 -> SIGXFSZ 25
//26 -> SIGVTALRM 26
//27 -> SIGPROF 27
//28 -> SIGWINCH 28
//29 -> SIGINFO 29
//30 -> SIGUSR1 30
//31 -> SIGUSR2 31

void handle_signal(int signal)
{
//	char* sig_name[31] = {"SIGHUP", "SIGINT", "SIGQUIT", "SIGILL", "SIGTRAP", "SIGABRT",
//		"SIGEMT", "SIGFPE", "SIGKILL", "SIGBUS", "SIGSEGV", "SIGSYS", "SIGPIPE",
// 		"SIGALARM", "SIGTERM", "SIGURG", "SIGSTOP", "SIGTSTP", "SIGCONT", "SIGCHLD",
//		"SIGTTIN", "SIGTTOU", "SIGIO", "SIGXCPU", "SIGXFSZ", "SIGVTALRM", "SIGPROF",
//		"SIGWINCH", "SIGINFO", "SIGUSR1", "SIGUSR2"};

//The handler emits a line to stdout that indicates
//the signal caught, and
//the time it was caught                         (see time(2))
	printf("%s caught at %ld\n", strsignal(signal), time(NULL));

}//end handle_signal

int main(int argc, char** argv)
{
//Local Variables
	char** signals[argc - 1];//make dynamic w/ malloc
	int sigterm = 0, count = 0;

//The program emits a status line that includes its PID to stderr
	fprintf(stderr, "%s $$: %d\n", argv[0], getpid());

//The program processes the command line arguments
	for(int i = 1; i < argc; i++)
	{
	//The arguments indicate which signals to catch
		signals[i - 1] = argv[i];

	}//end for

	while(sigterm < 3)
	{
	//The program gracefully terminates after
	//receiving three successive SIGTERM signals       (hint: static int count)

	//The program registers a handler for each argument                      (see signal(2))
		for(int i = 0; i < argc; i++)
		{
		//The handler registers itself again            (read about unreliable signals)
			if(signal(signals[i], handle_signal) != SIGERR)
			{
				count++;

			//if sigterm
				if(SIGTERM)
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

		}//end for
	}//end while

//The program emits a final status message to stderr that indicates
//the number of signals caught
	fprintf(stderr, "%s: Total signals count = %d\n", argv[0], count);

	return 0;
}//end main
