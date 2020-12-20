/*Author : Dhruv B Kakadiya
 * Implementation of Basic ps command using c language
 */

#include<unistd.h>
#include<dirent.h>
#include<stdio.h>
#include<sys/types.h>
#include<string.h>
#include<stdlib.h>
#include<sys/stat.h>
#include<ctype.h>
#define FORMAT "%5d\t %30s\t %c\n"

void execution_of_ps(char *main_dir, DIR *dir, struct dirent *dirp);
void execution_of_ps(char *main_dir, DIR *dir, struct dirent *dirp)
{
	char main_path[100000];
	char process_name[100000];
	int pid;
	char status;
	if((dir = opendir(main_dir)) == NULL)
	{
		fprintf(stderr, "cannot open directory : %s\n", main_dir);
		return;
	}
	while(dirp = readdir(dir))
	{
		if(strcmp(dirp->d_name, ".") != 0 && strcmp(dirp->d_name, "..") != 0)
		{
			if(dirp->d_type == DT_DIR && atoi(dirp->d_name) > 0)
			{
				strcpy(main_path, main_dir);
				strcat(strcat(main_path, dirp->d_name), "/stat");
				FILE *fp;
				if (fp = fopen(main_path, "r"))
				{
					fscanf(fp, "%d %s %c", &pid, process_name, &status);
					printf(FORMAT, pid, process_name, status);
					
				}
				else
					continue;
			}
		}
	}
	closedir(dir);
	return;
}

int main()
{
	DIR *dir;
	struct dirent *dirp;
	execution_of_ps("/proc/", dir, dirp);
	printf("\n\n");
	exit(0);
}

