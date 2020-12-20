#include <stdio.h>
#include <pthread.h>
#include <semaphore.h>
#include <unistd.h>

#define RCNT 3
#define WCNT 1

sem_t rdrCntSema,wrtSema;
int rdrFunCnt=0;
int content=0;


void* rdrFun(void *args){
	int *rdrArg=(int *)args;
	while(1){
		sem_wait(&rdrCntSema);
		rdrFunCnt++;
		if(rdrFunCnt==1)
			sem_wait(&wrtSema);
		sem_post(&rdrCntSema);
		printf("Reader %d is reading number %d\n",*rdrArg,content);
		sem_wait(&rdrCntSema);
		rdrFunCnt--;
		if(rdrFunCnt==0)
			sem_post(&wrtSema);
		sem_post(&rdrCntSema);
		sleep(2);
	}
}
void* wrtFun(void *args){
	int *wrtArg=(int *)args;
	int i=0;
	while(1){
		sem_wait(&wrtSema);
		content++;
		printf("  Writer number %d is writing number %d\n",*wrtArg,content);
		sem_post(&wrtSema);
		sleep(1);
	}
}

void main(){

	int i=0;
	int rdrArr[RCNT],wrtArr[WCNT];
	pthread_t rdrThrdArr[RCNT],wrtThrdArr[WCNT];

	sem_init(&rdrCntSema,0,1);
	sem_init(&wrtSema,0,1);

	for(i=0;i<RCNT;i++){
		rdrArr[i]=i+1;
		pthread_create(&rdrThrdArr[i],NULL,rdrFun,(void*)&rdrArr[i]);
	}
	for(i=0;i<WCNT;i++){
		wrtArr[i]=i+1;
		pthread_create(&wrtThrdArr[i],NULL,wrtFun,(void*)&wrtArr[i]);
	}

	for(i=0;i<RCNT;i++)
		pthread_join(rdrThrdArr[i],NULL);
	for(i=0;i<WCNT;i++)
		pthread_join(wrtThrdArr[i],NULL);
}

