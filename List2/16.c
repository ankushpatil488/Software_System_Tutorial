/*
============================================================================
Name : 16.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to send and receive data from parent to child vice versa. Use two way
communication.

Date: 28th Sept, 2023.

============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

int main()
{
	int fd_pipe1[2];
	int fd_pipe2[2];
	char buff1[80],buff2[80];
	if(pipe(fd_pipe1)==-1)
	{
		perror("Error");
		return 1;
	}
	if(pipe(fd_pipe2)==-1)
	{
		perror("Error");
		return 1;
	}
	int pid=fork();
	if (pid == -1) {
		perror("fork");
		return 0;
    	}
	if (pid==0) {
		close(fd_pipe1[0]); 
		close(fd_pipe2[1]);
		printf("Enter message to parent from child: ");
		scanf(" %[^\n]", buff1);
		write(fd_pipe1[1], buff1, sizeof(buff1));
		read(fd_pipe2[0], buff2, sizeof(buff2));
		printf("Message from parent to child: %s\n", buff2);
	}
	else {
		close(fd_pipe1[1]);
		close(fd_pipe2[0]); 
		read(fd_pipe1[0], buff1, sizeof(buff1));
		printf("Message from child to parent: %s\n", buff1);
		printf("Enter message to child from parent: ");
		scanf(" %[^\n]", buff2);
		write(fd_pipe2[1], buff1, sizeof(buff1));
	}
	wait(0);
	return 1;
}
