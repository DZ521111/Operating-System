// Author : Dhruv B kakadiya
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define ph_counter 5
sem_t sem_fork[ph_counter], sem_room;

void *Philosopher(void *arg)
{
	int *ph_id = (int *)arg;
	while(1)
	{
		sem_wait(&sem_room);
		printf("P :- %d thinking\n", *ph_id);
		sem_wait(&sem_fork[*ph_id - 1]);
		printf("\t\tP :- %d : grabed fork left\n", *ph_id);
		sem_wait(&sem_fork[(*ph_id)%ph_counter]);
		printf("\tP :- %d : grabed both fork and ready to eat\n", *ph_id);
		sem_post(&sem_fork[(*ph_id)%ph_counter]);
		printf("\t\tP :- %d : relesed right\n", *ph_id);
		sem_post(&sem_fork[*ph_id - 1]);
		printf("\t\tP :- %d : relesed fork both\n", *ph_id);
		sem_post(&sem_room);
		sleep(1);
	}
}

void main()
{
	pthread_t phi_thread[ph_counter];
	int loop, ph_id[ph_counter];
	sem_init(&sem_room,0, ph_counter-1);
	for(loop = 0 ; loop < ph_counter ; loop++)
	{
		sem_init(&sem_fork[loop], 0, 1);
	}
	for(loop = 0 ; loop < ph_counter ; loop++)
	{
		ph_id[loop] = loop + 1;
		pthread_create(&phi_thread[loop], NULL, Philosopher, (void*)&ph_id[loop]);
	}
	for(loop = 0 ; loop < ph_counter ; loop++)
	{
		pthread_join(phi_thread[loop], NULL);
	}
}
