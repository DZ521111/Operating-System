#include<unistd.h>
#include<stdio.h>
void main()
{
	char buf[1024];
	getcwd(buf, sizeof(buf));
	printf("%s",buf);
	print(“\n”);
}
