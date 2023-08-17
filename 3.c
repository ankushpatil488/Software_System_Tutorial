#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	 int fd1=creat("tempfile.txt",O_RDONLY);
	 if(fd1==-1)
	 {
		perror("Error");
	 }
	 else
	 {
	 	printf("File open for read write with file descriptor value = %d\n",fd1);
	 }
}
