/*
============================================================================
Name : 3.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to create a file and print the file descriptor value. Use creat ( ) system call


Date: 21th Aug, 2023.
Output : File name 3.txt is created and on concole program prints File descriptor value of the file is = 3
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main()
{
	 int fd=creat("3.txt",0666);
	 if(fd==-1)
	 {
		perror("Error whlie creating the file");
	 }
	 else
	 {
	 	printf("File descriptor value of the file is = %d\n",fd);
	 }
	 close(fd);
}
