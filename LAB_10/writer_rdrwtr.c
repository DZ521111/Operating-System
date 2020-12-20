// Author : Dhruv B Kakadiya
#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define rdr 3
#define wtr 2

sem_t sem_z, rdr_sema_cnt, wrt_sema_cnt, rdrsema, wrtsema;
int rdrCnt = 0, wrtCnt = 0;
int content = 0;

void *rdr_function(void* args)
{
	int *rdrArg = (int *)args;
	while(1)
	{
		sem_wait(&sem_z);
		sem_wait(&rdrsema);
		sem_wait(&rdr_sema_cnt);
		rdrCnt++;
		if(rdrCnt == 1)
		{
			sem_wait(&wrtsema);
		}
		sem_post(&rdr_sema_cnt);
		sem_post(&rdrsema);
		sem_post(&sem_z);
		printf("Reader %d is reading number %d\n", *rdrArg, content);
		sem_wait(&rdr_sema_cnt);
		rdrCnt--;
		if(rdrCnt==0)
		{
			sem_post(&wrtsema);
		}
		sem_post(&rdr_sema_cnt);
		sleep(3);
	}
}
void *wrt_function(void* args)
{
	int *wrtArg = (int *)args;
	while(1)
	{
		sem_wait(&wrt_sema_cnt);
		wrtCnt++;
		if(wrtCnt==1)
		{
			sem_wait(&rdrsema);
		}
		sem_post(&wrt_sema_cnt);
		sem_wait(&wrtsema);
		content++;
		printf("Writer number %d is writing number %d\n",*wrtArg, content);
		sem_post(&wrtsema);
		sem_wait(&wrt_sema_cnt);
		wrtCnt--;
		if(wrtCnt==0)
		{
			sem_post(&rdrsema);
		}
		sem_post(&wrt_sema_cnt);
		sleep(2);
	}
}

void main(){

	int i = 0;
    int rdrArr[rdr], wrtArr[wtr];
	pthread_t rdr_thread_array[rdr], wrt_thread_array[wtr];

	sem_init(&rdr_sema_cnt, 0, 1);
    sem_init(&wrt_sema_cnt, 0, 1);
	sem_init(&rdrsema, 0, 1);
    sem_init(&wrtsema, 0, 1);
	sem_init(&sem_z, 0, 1);

	for(i = 0 ; i < rdr ; i++)
	{
		rdrArr[i] = i + 1;
		pthread_create(&rdr_thread_array[i], NULL, rdr_function, (void*)&rdrArr[i]);
	}
	for(i = 0 ; i < wtr ; i++)
	{
		wrtArr[i] = i + 1;
		pthread_create(&wrt_thread_array[i], NULL, wrt_function, (void*)&wrtArr[i]);
	}

	for(i = 0 ; i < rdr ; i++)
	{
		pthread_join(rdr_thread_array[i], NULL);
	}
	for(i = 0 ; i < wtr ; i++)
	{
		pthread_join(wrt_thread_array[i], NULL);
	}
}
