/*
============================================================================
Name : 34b_server.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to create a concurrent server.
 b. use pthread_create
Date: 10th Oct, 2023.

============================================================================
*/
#include <sys/types.h> 
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>    
#include <unistd.h>     
#include <pthread.h>    
#include<string.h>

void handleClient(int *fd)
{
    char buff[100];

    ssize_t writeBytes = write(*fd, "Hello Client,I'm the server!", strlen("Hello Client,I'm the server!"));
    if (writeBytes == -1)
        perror("Error while writing to network via socket!");
        
    else
        printf("Data sent to client!\n");

    ssize_t readBytes = read(*fd, buff, 100);
    if (readBytes == -1)
        perror("Error while reading from network via socket!");
       
    else
        printf("Data from client: %s\n", buff);

    close(*fd);
}

int main()
{
    struct sockaddr_in add, client;

    pthread_t threadID;

    int fd1 = socket(AF_INET, SOCK_STREAM, 0);
    if (fd1 == -1)
    {
        perror("Error while creating socket!");
        return 0;
    }
    printf("Server side socket successfully created!\n");

    add.sin_addr.s_addr = htonl(INADDR_ANY);
    add.sin_family = AF_INET;
    add.sin_port = htons(8080);

    int bindStatus = bind(fd1, (struct sockaddr *)&add, sizeof(add));
    if (bindStatus == -1)
    {
        perror("Error while binding");
        return 0;
    }
    printf("Binding to socket was successful!\n");

    int listenStatus = listen(fd1, 2);
    if (listenStatus == -1)
    {
        perror("Error while trying ");
        return 0;
    }
    printf("Now listening for connections on a socket!\n");

    while (1)
    {
        int clientSize = (int)sizeof(client);
        int fd2 = accept(fd1, (struct sockaddr *)&client, &clientSize);
        if (fd2 == -1){
            perror("Error while accepting");
            return 0;
        }
        else
        {   
            if (pthread_create(&threadID, NULL, (void *)handleClient, &fd2)){
                perror("Error while creating thread");
                return 0;
            }
        }
    }

    close(fd1);
    return 1;
}



