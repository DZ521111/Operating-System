#include<sys/types.h>
#include<unistd.h>
#include<stdio.h>

int main()
{
	fork();
	printf("Hello\n");
	return 0;
}
