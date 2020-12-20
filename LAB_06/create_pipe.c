// Author : Dhruv B Kakadiya
#include<stdio.h>
#include<unistd.h>

int main()
{
	int pipefd[2];
	pipe(pipefd);
	printf("\n1st pipe :  %d %d\n", pipefd[0], pipefd[1]);
	pipe(pipefd);	// 2nd pipe
	printf("2nd pipe : %d %d\n", pipefd[0], pipefd[1]);
	pipe(pipefd);	// 3rd pipe
	printf("3rd pipe : %d %d\n", pipefd[0], pipefd[1]);
}
