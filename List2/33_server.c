/*
============================================================================
Name : 33_server.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to communicate between two machines using socket

Date: 10th Oct, 2023.

============================================================================
*/
#include <sys/types.h>  
#include <sys/socket.h> 
#include <netinet/ip.h> 
#include <stdio.h>      
#include <unistd.h>     
#include <string.h>
int main()
{
    struct sockaddr_in add, client;
    char buffer[100];

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

    if (bind(fd1, (struct sockaddr *)&add, sizeof(add)) == -1)
    {
        perror("Error while binding");
        return 0;
    }
    printf("Binding to socket was successful!\n");

    if (listen(fd1, 2) == -1)
    {
        perror("Error while listen ");
        return 0;
    }
    printf("Now listening for connections on a socket!\n");

    int clientSize = (int)sizeof(client);
    int fd2 = accept(fd1, (struct sockaddr *)&client, &clientSize);
    if (fd2 == -1){
        perror("Error while accepting");
        return 0;
    }
    else
    {
        size_t writeBytes = write(fd2, "Hello client, I'm server!", strlen("Hello client, I'm server!"));
        if (writeBytes == -1)
            perror("Error while writing");
        else
            printf("Data sent to client!\n");

        size_t readBytes = read(fd2, buffer, 100);
        if (readBytes == -1)
            perror("Error while reading ");
        else
            printf("Data from client: %s\n", buffer);
    }
    close(fd2);
    close(fd1);
}



