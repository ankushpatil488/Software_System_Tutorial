/*
============================================================================
Name : 21_read.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write two programs so that both can communicate by FIFO -Use two way communications.

Date: 3rd Oct, 2023.
Output : ./read on other terminal
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd1,fd2;

    fd1 = open("myfifo1", O_RDONLY);
    fd2 = open("myfifo2", O_WRONLY);
    if (fd1 == -1) {
        perror("Error in opening the fifo file 1");
        return 0;
    }
    if (fd2 == -1) {
        perror("Error in opening the fifo file 2");
        return 0;
    }
    char buff1[100],buff2[100];
    
    read(fd1,buff1,sizeof(buff1));
    printf("Data from Fifo file myfifo1 : %s\n",buff1);
    
    printf("Enter the data you want to send to program1\n");
    scanf("%[^\n]",buff2);
    write(fd2, buff2, sizeof(buff2));
    	
    close(fd1);
    close(fd2);

    return 0;
}



