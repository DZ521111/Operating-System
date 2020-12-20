// Author : Dhruv B kakadiya
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

void main()
{
	int pid, pret, pipefd[2], status;
	;
	pret = pipe(pipefd);
	if (pret == -1)
	{
		printf("\n\nCould not create pipe.\n\n");
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			printf("\n\nCould not create pipe.\n\n");
		}
		else if (pid > 0)
		{
			wait(&status);
			close(pipefd[1]);
			printf("Entered in Parent process\n\n");
			dup2(pipefd[0], 0);
			execl("/bin/sort", "sort", (char*)0);
		}
		else{
			close(pipefd[0]);
			printf("---Entered in Child process---\n");
			dup2(pipefd[1], 1 );
			execl("/bin/ls", "ls", "-l", (char*)0);
		}
	}
}
