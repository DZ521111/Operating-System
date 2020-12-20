// Author : Dhruv B Kakadiya
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define rdr 3
#define wtr 1

sem_t rdrsema, wrtsema;
int rdrcnt = 0;
int content = 0;


void* rdrFun(void *args)
{
	int *rdrArg = (int *)args;
	while(1)
	{
		sem_wait(&rdrsema);
		rdrcnt++;
		if(rdrcnt == 1)
		{
			sem_wait(&wrtsema);
		}
		sem_post(&rdrsema);
		printf("Reader %d is reading number %d\n", *rdrArg, content);
		sem_wait(&rdrsema);
		rdrcnt--;
		if(rdrcnt==0)
		{
			sem_post(&wrtsema);
		}
		sem_post(&rdrsema);
		sleep(2);
	}
}
void* wrtFun(void *args)
{
	int *wrtArg=(int *)args;
	int i = 0;
	while(1)
	{
		sem_wait(&wrtsema);
		content++;
		printf("Writer number %d is writing number %d\n", *wrtArg, content);
		sem_post(&wrtsema);
		sleep(1);
	}
}

void main()
{
	int i=0;
	int rdrArr[rdr], wrtArr[wtr];
	pthread_t rdr_thread_array[rdr], wtr_thread_array[wtr];

	sem_init(&rdrsema, 0, 1);
	sem_init(&wrtsema, 0, 1);

	for(i = 0 ; i < rdr ; i++)
	{
		rdrArr[i] = i + 1;
		pthread_create(&rdr_thread_array[i], NULL, rdrFun, (void*)&rdrArr[i]);
	}
	for(i = 0 ; i < wtr ; i++)
	{
		wrtArr[i] = i + 1;
		pthread_create(&wtr_thread_array[i], NULL, wrtFun, (void*)&wrtArr[i]);
	}
	for(i = 0 ; i < rdr ; i++)
	{
		pthread_join(rdr_thread_array[i], NULL);
	}
	for(i = 0 ; i < wtr ; i++)
	{

	}
}

