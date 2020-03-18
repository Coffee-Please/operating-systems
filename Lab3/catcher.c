//A program that catches a number of predefined signals, and prints status information on stdout.

#include <stdio.h>

int main(int argc, char** argv)
{

//The program processes the command line arguments

//The arguments indicate which signals to catch

//The program emits a status line that includes its PID to stderr

//The program registers a handler for each argument                      (see signal(2))

//The program pauses itself continually                   (see pause(2))

//The handler registers itself again            (read about unreliable signals)

//The handler emits a line to stdout that indicates

//the signal caught, and

//the time it was caught                         (see time(2))

//The program gracefully terminates after

//receiving three successive SIGTERM signals       (hint: static int count)

//The program emits a final status message to stderr that indicates

//the number of signals caught

	return 0;
}//end main
