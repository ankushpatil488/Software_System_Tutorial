/*
============================================================================
Name : 22_2.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.

Date: 3rd Oct, 2023.

============================================================================
*/
#include <sys/types.h>
#include <sys/stat.h>  
#include <fcntl.h>     
#include <sys/time.h>  
#include <unistd.h>    
#include <stdio.h>     
#include <string.h>
int main()
{
    int fd, writeBytes;
    char data[100];

    fd = open("myfifo", O_NONBLOCK | O_WRONLY|O_CREAT);

    if (fd == -1)
    {
        perror("Error while opening FIFO file!");
        return  0;
    }

    writeBytes = write(fd, "Hello How are you!", strlen("Hello How are you!"));

    if (writeBytes == -1)
        perror("Error while writing to FIFO!");

    close(fd);
}


