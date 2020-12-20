#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	int fd2;
	mkfifo("filefifo", 0777);
	char array1[100];
	while(1)
	{
		fd2 = open("filefifo", O_RDONLY);
		read(fd2, array1, 100);
		printf("%s\n", array1);
		close(fd2);
	}
	return 0;
}
