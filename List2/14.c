/*
============================================================================
Name : 14.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a simple program to create a pipe, write to the pipe, read from pipe and display on
the monitor.

Date: 28th Sept, 2023.

============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
int main()
{
	int fd_pipe[2];
	if(pipe(fd_pipe)==-1)
	{
		perror("Error");
		return 1;
	}
	char msg[30]="Hello How are you";
	write(fd_pipe[1],msg,sizeof(msg));
	
	char buff[1024];
	read(fd_pipe[0],buff,sizeof(buff));
	
	printf("%s\n",buff);
	
	close(fd_pipe[0]);
	close(fd_pipe[1]);
	
}
