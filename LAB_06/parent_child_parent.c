#include<stdio.h>
#include<unistd.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<string.h>
#include<fcntl.h>
int main()
{
	int pipefd[2], pipefd2[2],p, pid, p2, status;
	char file_name[20], content[100], last_content[100];
	p = pipe(pipefd);
	p2 = pipe(pipefd2);

	if (p == -1)
	{
		printf("Error in creation in pipe!\n\n");
	}
	else
	{
		pid = fork();
		if (pid == -1)
		{
			printf("Errro in creation of process!\n\n");
		}
		else if (pid > 0)
		{
			close(pipefd[0]);
			bzero(file_name, sizeof(file_name));
			int n = read(0, file_name, sizeof(file_name));
			file_name[strlen(file_name) - 1] = '\0';
			printf("Parent pid : %d ---> sending file_name : %s ---> to Child pid : %d\n\n\n", getpid(), file_name, pid);
			write(pipefd[1], file_name, n);
			
			wait(&status);
		
			close(pipefd2[1]);
			bzero(last_content, sizeof(last_content));
			read(pipefd2[0], last_content, sizeof(last_content));
			file_name[strlen(last_content)] = '\0';
			printf("parent pid : %d ---> received data : \n%s ---> from Child pid : %d\n\n\n", getpid(), last_content, pid);
		}	
		else
		{
			close(pipefd[1]);
			bzero(file_name, sizeof(file_name));
			read(pipefd[0], file_name, sizeof(file_name));
			last_content[strlen(file_name)] = '\0';
			int fd = open(file_name, O_RDONLY);
			bzero(content, sizeof(content));
			int n = read(fd, content, sizeof(content));
			printf("Child pid : %d ---> received data : \n%s\n ---> from Parent pid : %d\n\n\n", getpid(), content, getppid());
			
		
			if (p2 == -1)
			{
				printf("Error in creation of Process!\n");
			}
			else
			{
				close(pipefd2[0]);
				printf("Child pid : %d ---> sending data : \n%s\n ---> to parent pid : %d\n\n", getpid(), content, getppid());
				write(pipefd2[1], content, n);
			}
		}
	}
	return 0;
}




			
			



