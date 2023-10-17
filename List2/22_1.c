/*
============================================================================
Name : 22_1.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.

Date: 3rd Oct, 2023.
Output : ./read on other terminal
============================================================================
*/
// Question : Write a program to wait for data to be written into FIFO within 10 seconds, use `select` system call with FIFO.

#include <sys/types.h> 
#include <sys/stat.h>  
#include <fcntl.h>     
#include <sys/time.h>  
#include <unistd.h>    
#include <stdio.h>     

int main()
{
    int fd, readBytes;
    char data[100];

    fd_set readFDSet;
    struct timeval timer;
    int selectStatus;


    fd = open("myfifo", O_NONBLOCK | O_RDONLY|O_CREAT);

    if (fd == -1)
    {
        perror("Error while opening FIFO file!");
        return 0;
    }

    FD_ZERO(&readFDSet);
    FD_SET(fd, &readFDSet); // Adding FIFO file's descriptor to the set of file descriptors to read from

    // Setting the time to wait to 10s
    timer.tv_sec = 10;
    timer.tv_usec = 0;

    selectStatus = select(fd + 1, &readFDSet, NULL, NULL, &timer);

    if (selectStatus == -1)
        perror("Error while calling for select!");
    else if (selectStatus)
    {
        readBytes = read(fd, &data, 100);

        if (readBytes == -1)
            perror("Error while reading from FIFO!");
        else
            printf("Data received : %s\n", data);
    }
    else
        printf("You didn't send any data for 10 seconds! :(\n");

    close(fd);
}




