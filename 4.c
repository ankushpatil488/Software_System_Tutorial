#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	 int fd1=open("tempfile.txt",O_RDWR);
	 if(fd1 == -1)
	 {
		perror("Error");
		return 1;
	 }
	 else
	 {
	 	printf("File open for read write with file descriptor value = %d\n",fd1);

		int fd2=open("tempfile.txt",O_RDWR | O_EXCL);
		if(fd2 == -1){
			perror("Error while opening the file with O_EXCL flag");	
		}
		else{
			printf("Successfully open the file with O_EXCL flag and file desciptor valueis = %d\n",fd2);
			close(fd2);
		}
	 }
	 close(fd1);
}
