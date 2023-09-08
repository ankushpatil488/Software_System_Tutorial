/*
============================================================================
Name : 4.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to open an existing file with read write mode. Try O_EXCL flag also. 


Date: 22th Aug, 2023.
Output : File name 4.txt is being opening(create if not exist)
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	 int fd1=open("4.txt",O_CREAT | O_RDWR,0666);
	 if(fd1 == -1)
	 {
		perror("Error while opening the file");
		return 1;
	 }
	 else
	 {
	 	printf("File open for read write with file descriptor value = %d\n",fd1);

		int fd2=open("4.txt",O_RDWR | O_EXCL | O_CREAT ); //Prevent creation of 4.txt if it already exists.
		if(fd2 == -1){
			perror("Error while opening the file with O_EXCL flag");
			return 1;	
		}
		else{
			printf("Successfully open the file with O_EXCL flag and file desciptor value = %d\n",fd2);
			close(fd2);
		}
	 }
	 close(fd1);
	 
}
