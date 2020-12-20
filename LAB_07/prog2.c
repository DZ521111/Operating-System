// Author : Dhruv B Kakadiya
#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<string.h>

void main()
{
	int pid, pret, pipefd[2], status, filehand, rd;
	char filedata[1000];
	char filenm[100];
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
			printf("\nEntered in Parent process\n\n");
			dup2(pipefd[0], 0);
			execl("/bin/sort", "sort", (char*)NULL);
		}
		else{
			close(pipefd[0]);
			printf("Entered in Child process\n");
			printf("Enter File name to sort : \n");
			bzero(filenm, sizeof(filenm));
			rd = read(0, filenm, sizeof(filenm));
			filenm[strlen(filenm) - 1] = '\0';
			filehand = open(filenm, O_RDONLY);
			bzero(filedata, sizeof(filedata));
			rd = read(filehand, filedata, sizeof(filedata));
			write(pipefd[1], filedata, rd);
		}
	}
}
