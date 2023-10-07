/*
============================================================================
Name : 17c.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to execute ls -l | wc.
 c. use fcntl

Date: 30th Sept, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include<fcntl.h>
int main() {
    int pipe_fd[2];
    if (pipe(pipe_fd) == -1) {
        perror("pipe");
        return 0;
    }

    int pid = fork();

    if (pid == -1) {
        perror("fork");
        return 0;
    }

    if (pid == 0) {  
        // Child process
        close(1);
        close(pipe_fd[0]);  
        fcntl(pipe_fd[1],F_DUPFD, STDOUT_FILENO);  
        close(pipe_fd[1]);  

        execlp("ls", "ls", "-l", NULL);  
        perror("execlp");
        return 0;
    } 
    else {  
        // Parent process
        close(0);
        close(pipe_fd[1]);
        fcntl(pipe_fd[0],F_DUPFD, STDIN_FILENO);    
        close(pipe_fd[0]);  

        execlp("wc", "wc", NULL);  
        perror("execlp");
        return 0;
    }

    return 0;
}

