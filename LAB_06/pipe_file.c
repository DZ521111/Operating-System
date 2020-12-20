#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<sys/types.h>
#include<string.h>
int main(int argc, char* argv[])
{
	int pipefd[2], p, pid, n, status;
	char file_name[20];
	char content[100];
	p = pipe(pipefd);

	if (p == -1)
	{
		printf("Error in creation of pipe!\n");
	}
	else
	{
		pid  = fork();
		if (pid == -1)
		{
			printf("Error in creation of process!\n");
		}
		else if (pid > 0)
		{
			close(pipefd[0]);
			bzero(file_name, sizeof(file_name));
			n = read(0, file_name, sizeof(file_name));
			file_name[strlen(file_name) - 1] = '\0';
			printf("parent pid : %d ---> sending file_name : %s ---> to child pid : %d\n\n", getpid(), file_name, pid);
			write(pipefd[1], file_name, n);
		}
		else
		{
			close(pipefd[1]);
			bzero(file_name, sizeof(file_name));
			read(pipefd[0], file_name, sizeof(file_name));
			file_name[strlen(file_name)] = '\0';
			int fd = open(file_name, O_RDONLY);
			bzero(content, sizeof(content));
			read(fd, content, sizeof(content));
			printf("chlid pid : %d ---> received msg : \n\n%s\n ---> from parent pid : %d\n", getpid(), content, getppid());
		}
	}
	wait(&status);
}

