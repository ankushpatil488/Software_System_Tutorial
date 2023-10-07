/*
============================================================================
Name : 17c.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to find out total number of directories on the pwd.
 execute ls -l | grep ^d | wc ? Use only dup2.

Date: 1st Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<fcntl.h>
int main() {
	int pipe_fd1[2], pipe_fd2[2];
	 
	if (pipe(pipe_fd1) == -1) {
		perror("pipe");
		return 0;
    	}
	if (pipe(pipe_fd2) == -1) {
		perror("pipe");
		return 0;
    	}
    	
    	int pid1 = fork();
    	if (pid1 == -1) {
		perror("fork");
		return 0;
    	}
	
	if (pid1==0) {
		close(pipe_fd1[0]);
		dup2(pipe_fd1[1], 1);
		close(pipe_fd2[0]);
		close(pipe_fd2[1]);
		execlp("ls", "ls", "-l",NULL);
		perror("execlp");
        	return 0;
	}
	else {
		int pid2 = fork();
		if (pid2 == -1) {
			perror("fork");
			return 0;
    		}
		if (pid2==0) {
			dup2(pipe_fd2[1], 1);
			dup2(pipe_fd1[0], 0);
			close(pipe_fd1[1]);
			close(pipe_fd2[0]);
			execlp("grep", "grep", "^d",NULL);
			perror("execlp");
        		return 0;
		}
		else {
			dup2(pipe_fd2[0], 0);
			close(pipe_fd2[1]);
			close(pipe_fd1[0]);
			close(pipe_fd1[1]);
			execlp("wc", "wc",NULL);
			perror("execlp");
        		return 0;
		}
	}
	close(pipe_fd1[0]);
	close(pipe_fd1[1]);
	close(pipe_fd2[0]);
	close(pipe_fd2[1]);
	
	return 0;
}


