#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
	int pid,status;
	pid = 0;
	for(int i= 0; i<4; i++)
		if( pid==0 ){
			pid = fork();
			wait(&status);
			if (pid == 0)
				printf("Child %d :\t id : %d\tParent : %d\n",i+1,getpid(),getppid()); 
		}
	return 0;
}
