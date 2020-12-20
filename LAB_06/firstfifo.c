#include<stdio.h>
#include<string.h>
#include<fcntl.h>
#include<sys/stat.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	mkfifo("filefifo", 0777);
	char str2[100];
	while(1)
	{
		int fd = open("filefifo", O_WRONLY);
		fgets(str2, 100, stdin);
		write(fd, str2, strlen(str2)+1);
		close(fd);
	}
	return 0;
}
