#include <stdio.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

#define SEM_1 "/chopstick_1"
#define SEM_2 "/chopstick_2"

static int stop;
static int next;

int rand()
{
	next = next * 1103515245 + 12345;
	return((unsigned)(next/6553) % 32768);
}//end rand


void srand(unsigned int seed)
{
	next = seed;
}//end srand


void eat(int position)
{

	printf("Philosopher #%d is eating...\n", position);
	usleep(rand());

}//end eat


void think(int position)
{

	printf("Philosopher #%d is thinking...\n", position);
	usleep(rand());

}//end think

int dine(sem_t* chopstick[], int i, int position)
{
	int eat_think_cycle = 0;

	do
	{
		sem_wait(chopstick[i]);
		sem_wait(chopstick[i + 1]);

		eat(position);

		sem_post(chopstick[i]);
		sem_post(chopstick[i + 1]);

		think(position);

		eat_think_cycle++;

	}while(!stop);

	return eat_think_cycle;

}//end dine


void kill_cycle(sem_t* chopstick[])
{
//When your program receives this signal, it needs to
//effectively remove the philosopher from the eat-think cycle
//release any system resources

	sem_close(chopstick[1]);
	sem_unlink(SEM_1);
	sem_destroy(chopstick[1]);

}//end kill

//to keep a count of the number of full eat-think cycles

void sig_handler(int signum)
{

	printf("SIGTERM (%d) recieved.\n", signum);

	stop = 1;

}//end sig_handler

int main(int argc, char** argv){

	if(argc != 3)
	{
		printf("Error: There should be 2 args.\n");
		exit(EXIT_FAILURE);

	}//end if

	int position = atoi(argv[2]);
	int seats = atoi(argv[1]);
	sem_t* chopstick[3];
	sem_t* rtnVal;

	if(!(position < seats))
	{
		printf("Error: Full Table.\n");
		exit(EXIT_FAILURE);

	}//end if

//Develop a signal handler for SIGTERM.
	signal(SIGTERM, sig_handler);

	srand(RAND_MAX);

//Add semaphores to the program                    (see sem_overview(7))
//allocate a semaphore for each chopstick         (see sem_open(3))
	rtnVal = sem_open(SEM_1, O_CREAT|O_EXCL, 0666, 1);

	if (rtnVal == SEM_FAILED )
	{
		perror(NULL);
		rtnVal = sem_open(SEM_1, 0);
	}

	chopstick[1] = rtnVal;

	int completed_cycles = dine(chopstick, 1, position);


	kill_cycle(chopstick);

//emits to stderr the following line:
//Philosopher #n completed m cycles
	fprintf(stderr, "Philosopher #%d completed %d cycles.\n", position, completed_cycles);

//return success from the process
	exit(EXIT_SUCCESS);

}//end main
