/*
============================================================================
Name : 15.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a simple program to send some data from parent to the child process.

Date: 28th Sept, 2023.

============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include <sys/wait.h>

int main()
{
	int fd_pipe[2];
	char buff[1024];
	if(pipe(fd_pipe)==-1)
	{
		perror("Error");
		return 0;
	}
	int pid=fork();
	if (pid == -1) {
		perror("fork");
		return 0;
    	}
	if (pid==0) {
		close(fd_pipe[0]);
		printf("Enter message to the child from parent: ");
		scanf(" %[^\n]", buff);
		write(fd_pipe[1], buff, sizeof(buff));
	}
	else {
		close(fd_pipe[1]);
		read(fd_pipe[0], buff, sizeof(buff));
		printf("Message from parent to the child: %s\n", buff);
	}
	wait(0);

	close(fd_pipe[0]);
	close(fd_pipe[1]);
	
}
