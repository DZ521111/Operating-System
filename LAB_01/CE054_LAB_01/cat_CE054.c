// Implementation of CAT command 
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>

void main(int argc, char *argv[])
{
	
    	char buffer[10000];
    	int fd, n;
	// implementation of simple cat command without any cmd line argument
    	if(argc == 1)
    	{
        	while (n = read(0, buffer, sizeof(buffer)))
        	{
            		write(1, buffer, n);
        	}
    	}
    	// implementation of cat command with cmd line argument
    	if(argc >= 2)
    	{
        	for(int i = 1 ; i < argc ; i++)
		{
            		fd = open(argv[i], O_RDONLY);
            		n = read(fd, buffer, 10000); 
            		write(1, buffer, n);
            		write(1, "\n", 1);
        	}
    	}
}