// Implementatio of CP command
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
int main(int argc,char* argv[])
{
	char buffer[10000];
	// open src file
	int src = open(argv[1], O_RDONLY);
	// open destination file
	int dest = open(argv[2],O_WRONLY | O_CREAT);
	int n = read(src, buffer, sizeof(buffer));
	// write operation on destination file
	write(dest, buffer, n);
	
	// closing files
	close(src);
	close(dest);
}