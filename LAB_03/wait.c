#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>

int main()
{
	int pid,status;
	pid = fork();
	if(pid == -1)
		printf("Error!\n");
	else if(pid > 0){
		wait(&status);
		printf(" Parent :\t Parent : %d\t Child : %d \n", getpid(),pid);
	}
	else
		printf(" Child :\t Child : %d\t Parent : %d\t \n",getpid(),getppid());
	return 0;
}
