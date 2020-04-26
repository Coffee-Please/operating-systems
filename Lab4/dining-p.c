#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
#include <semaphore.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <errno.h>

static int stop;
static unsigned int next;


//create rand()
int rand()
{
	next = (((next * 1103515245 + 12345) /6553) % 32768) * 10;
	return((unsigned)next);
}//end rand

//get seed for rand()
void srand(unsigned int seed)
{
	next = seed;
}//end srand

//the philosophers are eating
void eat(int position)
{
	printf("Philosopher #%d is eating...\n", position);
	usleep(rand());

	return;
}//end eat

//the philosophers are thinking
void think(int position)
{
	printf("Philosopher #%d is thinking...\n", position);
	usleep(rand());

	return;
}//end think

//The philosophers are dining
int dine(sem_t* chopstick[], int position)
{
//to keep a count of the number of full eat-think cycles
	int eat_think_cycle = 0;
	int sval_1;
	int sval_2;

	do
	{
	//Philosopher is thinking
		think(position);

		sem_getvalue(chopstick[1], &sval_2);
		sem_getvalue(chopstick[0], &sval_1);

		//check L/R chopsticks if they are free
		if(sval_1 == 1 && sval_2 == 1)
		{
		//Philosopher has their chopsticks so they eat
			eat(position);

		//is finished eating
		//release L/R chopsticks and let others know
			sem_post(chopstick[1]);
			sem_post(chopstick[0]);

			eat_think_cycle++;
		}//end if

		//else, wait for free chopsticks
		else
		{
			sem_wait(chopstick[0]);
			sem_wait(chopstick[1]);
		}//end else
	}while(!stop);

	return eat_think_cycle;
}//end dine

//the philosophers are dying
void kill_cycle(sem_t* chopstick[], char sem_name_1[], char sem_name_2[])
{
//When your program receives this signal, it needs to
//effectively remove the philosopher from the eat-think cycle
//release any system resources
	sem_close(chopstick[0]);
	sem_close(chopstick[1]);

	sem_unlink(sem_name_1);
	sem_unlink(sem_name_2);

	sem_destroy(chopstick[0]);
	sem_destroy(chopstick[1]);
}//end kill

//signal handler for SIGTERM
void sig_handler(int signum)
{
//reregister signal handler
	signal(SIGTERM, sig_handler);

//Messages
	printf("SIGTERM (%d) received...\n", signum);

//stop philosophers dining
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
	int completed_cycles = 0;
	sem_t* chopstick[2];
	sem_t* rtnVal_1;
	sem_t* rtnVal_2;

//If the position # is more than the number of seats, error
	if(!(position <= seats))//N for part 2
	{
		printf("Error: No seat. Philosopher %d rejected\n", position);
		exit(EXIT_FAILURE);
	}//end if

//Set the names of the semaphores
	char name_holder[50];

//if there is only one philosopher
	if(seats == 1)
	{
		sprintf(name_holder, "%d", (position + 1));
	}//end if

	else
	{
		sprintf(name_holder, "%d", (position % seats));
	}//end else

//name the philosophers
	char sem_name_1[50];
	char sem_name_2[50];

	strcpy(sem_name_1, "/");
	strcat(sem_name_1, argv[2]);

	strcpy(sem_name_2, "/");
	strcat(sem_name_2, name_holder);

//seed rand
	srand(RAND_MAX);

//Develop a signal handler for SIGTERM.
	signal(SIGTERM, sig_handler);

//initialize semaphore 1 - left chopstick
	rtnVal_1 = sem_open(sem_name_1, O_CREAT | O_EXCL, 0666, 1);
	if(rtnVal_1 == SEM_FAILED)
	{
		rtnVal_1 = sem_open(sem_name_1, 0);
	}//end if
	chopstick[0] = rtnVal_1;

//initialize semaphore 2 - right chopstick
	rtnVal_2 = sem_open(sem_name_2, O_CREAT | O_EXCL, 0666, 1);
	if(rtnVal_2 == SEM_FAILED)
	{
		rtnVal_2 = sem_open(sem_name_2, 0);
	}//end if
	chopstick[1] = rtnVal_2;

//set the group id
	if(setpgid(getpid(), getppid()) != 0)
	{
		printf("Error: setpgid fail\n");
		exit(EXIT_SUCCESS);
	}//end if

//start dining
	completed_cycles = dine(chopstick, position);

//kill the philosophers
	kill_cycle(chopstick, sem_name_1, sem_name_2);

//Philosopher #n completed m cycles
	fprintf(stderr, "Philosopher #%d completed %d cycles.\n", position, completed_cycles);

//return success from the process
	exit(EXIT_SUCCESS);
}//end main
