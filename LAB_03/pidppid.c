#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
	int pid;
	pid = fork();
	if(pid == -1)
		printf("Error!\n");
	else if(pid > 0)
		printf(" Parent\t PID : %d\t PPID : %d\n",getpid(),getppid());
	else
		printf(" Child\t PID : %d\t PPID : %d\n",getpid(),getppid());
	return 0;
}
