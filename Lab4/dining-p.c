#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <unistd.h>
#include <errno.h>

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


int dine(sem_t chopstick[], int i, int seats)
{
//to keep a count of the number of full eat-think cycles
	int eat_think_cycle = 0;

	do
	{
		sem_wait(&chopstick[i]);
		sem_wait(&chopstick[(i + 1) % seats]);

		eat(i);

		sem_post(&chopstick[i]);
		sem_post(&chopstick[(i + 1) % seats]);

		think(i);

		eat_think_cycle++;
	}while(!stop);

	return eat_think_cycle;

}//end dine


void kill_cycle(sem_t chopstick[], int position, char* sem_name)
{
//When your program receives this signal, it needs to
//effectively remove the philosopher from the eat-think cycle
//release any system resources
	sem_close(&chopstick[position]);
	shm_unlink(sem_name);
	sem_destroy(&chopstick[position]);
}//end kill


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
	const int SIZE = seats * 32;
	sem_t chopstick[seats + 1];
	int shm_fd;
	char* sem_name = argv[2];

//If the position # is more than the number of seats, error
	if(!(position <= seats))//N for part 2
	{
		printf("Error: Full Table. Philosopher %d rejected\n", position);
		exit(EXIT_FAILURE);
	}//end if

//Create a new process group
	setpgid();

//for N seats, create N-1 processes
//	int child = fork();
//error, fork


//seed rand
	srand(RAND_MAX);

//Develop a signal handler for SIGTERM.
	signal(SIGTERM, sig_handler);

//allocate a semaphore for each chopstick         (see sem_open(3))
	for(int i = 0; i < seats; i++)
	{
	//initialize semaphore
		if(sem_init(&chopstick[i], 1, 1) < 0)
		{
			printf("Error: sem_init\n");//semaphore initialization failed
			exit(EXIT_FAILURE);
		}//end if
	}//end for

//open semaphores
	shm_fd = shm_open(argv[2], O_CREAT | O_EXCL, 0666);

	if(shm_fd < 0)
	{
		printf("Error: shm_open\n");//semaphore initialization failed
		exit(EXIT_FAILURE);
	}//end if

//allocate to memory map
	mmap(0, SIZE, PROT_READ, MAP_SHARED, shm_fd, 0);

//start dining
	int completed_cycles = dine(chopstick, position, seats);

//kill the philosophers
	kill_cycle(chopstick, position, sem_name);

//Philosopher #n completed m cycles
	fprintf(stderr, "Philosopher #%d completed %d cycles.\n", position, completed_cycles);

//return success from the process
	exit(EXIT_SUCCESS);
}//end main
