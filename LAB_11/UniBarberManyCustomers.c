// Author : Dhruv B kakadiya
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>
#define NO_CUSTOMERS 1000
#define NO_BARBER 2
#define CAPACITY 5
sem_t sem_wait_count, sem_cust, sem_barb;
int waited_customer = 0;

void *Customer(void *arg)
{
	int * custId=(int *)arg;
	sem_wait(&sem_wait_count);
	if(waited_customer < CAPACITY)
	{
		waited_customer++;
		printf("Customer-%d : entered wait :- \n", *custId);
		sem_post(&sem_cust);
		sem_post(&sem_wait_count);
		sem_wait(&sem_barb);
		printf("Customer-%d : got haircut :-  \n", *custId);
	}
	else
	{
		sem_post(&sem_wait_count);
	}
}


void *Barber(void *arg)
{
	int waitingTemp = 0;
	while(1)
	{
		sem_wait(&sem_cust);
		sem_wait(&sem_wait_count);
		waited_customer--;
		waitingTemp=waited_customer;
		printf("\tBarber :-  started cutting hair \t total number of customers in waiting :- %d \n", waitingTemp);
		sem_post(&sem_barb);
		sem_post(&sem_wait_count);
	}
}

void main()
{
	int loop, cust_id[NO_CUSTOMERS];
	pthread_t barber_arr[NO_BARBER], customer_arr[NO_CUSTOMERS];
	sem_init(&sem_barb, 0, 0);
	sem_init(&sem_cust, 0, 0);
	sem_init(&sem_wait_count, 0, 1);

	for(loop = 0 ; loop < NO_BARBER ; loop++)
	{
		pthread_create(&barber_arr[loop], NULL,Barber, (void*)NULL);
	}
	for(loop = 0 ; loop < NO_CUSTOMERS ; loop++)
	{
		cust_id[loop] = loop + 1;
		pthread_create(&customer_arr[loop], NULL,Customer, (void*)&cust_id[loop]);
	}
	for(loop = 0 ; loop < NO_BARBER ; loop++)
	{
		pthread_join(barber_arr[loop], NULL);
	}
	for(loop = 0 ; loop < NO_CUSTOMERS ; loop++)
	{
		pthread_join(customer_arr[loop], NULL);
	}
}
