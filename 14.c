#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		perror("wrong input\n");
		return 0;
	}
	struct stat filestat;
	if(stat(argv[1],&filestat)==-1)
	{
		perror("error in getting info\n");
		return 0;
	}
	if(S_ISREG(filestat.st_mode)){
	 	printf("Regular file\n");
	}
	else if(S_ISBLK(filestat.st_mode))
	{
		printf("Block device\n");
	}
	else if(S_ISCHR(filestat.st_mode))
	{
		printf("Character device\n");
	}
	else if(S_ISDIR(filestat.st_mode)){
		printf("Directory\n");
	}
	else if(S_ISFIFO(filestat.st_mode)){
		printf("FIFO (named file)\n");
	}
	else if(S_ISLNK(filestat.st_mode)){
		printf("Symbolic link\n");
	}
	else if(S_ISSOCK(filestat.st_mode)){
		printf("Socket\n");
	}
	else
	{
		printf("unknown type\n");
	}
	return 0;
}
