#include <stdio.h>
#include <signal.h>
#include <semaphore.h>
#include <fcntl.h>           /* For O_* constants */
#include <sys/stat.h>        /* For mode constants */
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>

static int stop;
static int next;


int rand()
{
	next = next * 1103515245 + 12345;
	return(((unsigned)(next/6553) % 32768) * 10);
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

int dine(sem_t* chopstick[], int i, int seats)
{
	int eat_think_cycle = 0;

	do
	{
		sem_wait(chopstick[i]);
		sem_wait(chopstick[(i + 1) % seats]);

		eat(i);

		sem_post(chopstick[i]);
		sem_post(chopstick[(i + 1) % seats]);

		think(i);

		eat_think_cycle++;
	}while(!stop);

	return eat_think_cycle;

}//end dine


void kill_cycle(sem_t* chopstick[], int position)
{
//When your program receives this signal, it needs to
//effectively remove the philosopher from the eat-think cycle
//release any system resources
	sem_close(chopstick[position]);
	sem_unlink(SEM_1);
	sem_destroy(chopstick[position]);
}//end kill

//to keep a count of the number of full eat-think cycles

void sig_handler(int signum)
{
	signal(SIGTERM, sig_handler);

	printf("SIGTERM (%d) recieved.\n", signum);

	stop = 1;
}//end sig_handler


int main(int argc, char** argv)
{
//if there are not 2 args
	if(argc != 3)
	{
		printf("Error: There should be 2 args.\n");
		exit(EXIT_FAILURE);
	}//end if

//local variables
	int position = atoi(argv[2]);
	int seats = atoi(argv[1]);
	sem_t* chopstick[seats + 1];
	sem_t* rtnVal;

//If the position # is more than the number of seats, error
	if(!(position < seats - 1))//N-1 for part 1
	{
		printf("Error: Full Table. Philosopher %d rejected\n", position);
		exit(EXIT_FAILURE);
	}//end if

//Create a new process group
//for N seats, create N-1 processes

//seed rand
	srand(RAND_MAX);

//Develop a signal handler for SIGTERM.
	signal(SIGTERM, sig_handler);

//Add semaphores to the program                    (see sem_overview(7))
	init(&chopstick[position], 1, 1);

//allocate a semaphore for each chopstick         (see sem_open(3))
	rtnVal = shm_open(SEM_1, O_CREAT|O_EXCL, 0666, 1);

//the semaphore already exists
	if (rtnVal == SEM_FAILED )
	{
		perror(NULL);
		rtnVal = shm_open(SEM_1, 0);
	}

	chopstick[position] = rtnVal;

//start dining
	int completed_cycles = dine(chopstick, position, seats);

//kill the philosophers
	kill_cycle(chopstick, position);

//Philosopher #n completed m cycles
	fprintf(stderr, "Philosopher #%d completed %d cycles.\n", position, completed_cycles);

//return success from the process
	exit(EXIT_SUCCESS);
}//end main
