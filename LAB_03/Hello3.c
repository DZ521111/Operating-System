#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
	fork();
	fork();
	fork();
	printf("Hello\n");
	return 0;
}