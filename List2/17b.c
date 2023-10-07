/*
============================================================================
Name : 17b.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to execute ls -l | wc.
 b. use dup2

Date: 30th Sept, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

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
        close(pipe_fd[0]);  
        dup2(pipe_fd[1], STDOUT_FILENO);  
        close(pipe_fd[1]);  

        execlp("ls", "ls", "-l", NULL);  
        perror("execlp");
        return 0;
    } 
    else {  
        // Parent process
        close(pipe_fd[1]);  
        dup2(pipe_fd[0], STDIN_FILENO);  
        close(pipe_fd[0]);  

        execlp("wc", "wc", NULL);  
        perror("execlp");
        return 0;
    }

    return 0;
}

