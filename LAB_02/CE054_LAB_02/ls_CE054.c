#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
void recursion(char path[], char name[], int mode);
void recursion(char path[], char name[], int mode)
{
	struct dirent *dirp;
	DIR *dir;
	char path_in[1000];
	strcpy(path_in, path);
	strcat(path_in, "/");
	strcat(path_in, name);
	if((dir = opendir(path_in)) == 0)
	{
		printf("Error");
		exit(0);
	}
	while(dirp = readdir(dir))
	{
		if(strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
		{
			for(int i=0 ; i < mode ; i++)
			{
				printf("	");
			}
			printf("%s\n", dirp->d_name);
			if(dirp->d_type == DT_DIR)
			{
				mode += 1;
				recurse(path_in, dirp->d_name, mode);
				mode -= 1; 
			}
		}
	}
	closedir(dir);
	return;
}

int main()
{
	struct dirent *dirp;
	DIR *dir;
	char path[1000];
	scanf("%s", path);
	if((dir = opendir(path)) == 0)
	{
		printf("Error: open dir");
		exit(0);
	}
	while(dirp = readdir(dir))
	{
		if(strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
		{
			printf("%s\n", dirp->d_name);
			if(dirp->d_type == DT_DIR)
			{
				recursion(path, dirp->d_name, 1);
			}
		}
	}
	closedir(dir);
}