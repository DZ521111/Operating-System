#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>
int main()
{
	int pipefd[2], p, pid, status;
	char data[100];
	p = pipe(pipefd);

	if (p == -1)
	{
		printf("Error in creation of pipe!\n\n");
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Error in creation of process!\n\n");
		}
		else if (pid > 0)
		{
			close(pipefd[0]);
			bzero(data, sizeof(data));
			int n = read(0, data, sizeof(data));
			data[strlen(data) - 1] = '\0';
			printf("Parent pid : %d ---> sending data : %s ---> to Child pid : %d\n\n", getpid(), data, pid);
			write(pipefd[1], data, n);
		}
		else
		{
			close(pipefd[1]);
			bzero(data, sizeof(data));
			read(pipefd[0], data, sizeof(data));
			data[strlen(data)] = '\0';
			printf("Child pid : %d ---> received data : \n\n%s ---> from Parent pid : %d\n\n", getpid(), data, getppid());
		}
	}
	wait(&status);

}

			
	
