/*
============================================================================
Name : 21_write.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write two programs so that both can communicate by FIFO - Using two way communications.

Date: 3rd Oct, 2023.
Output: gcc 21_write.c -o write
	gcc 21_read.c -o read
	./write on one terminal and ./read on other
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd1,fd2;

    if (mkfifo("myfifo1", 0666) == -1) {
        perror("Error in mkfifo");
        return 0;
    }
    if (mkfifo("myfifo2", 0666) == -1) {
        perror("Error in mkfifo");
        return 0;
    }
    fd1 = open("myfifo1", O_WRONLY);
    fd2 = open("myfifo2", O_RDONLY);
    if (fd1 == -1) {
        perror("Error in opening the fifo file 1");
        return 0;
    }
    if (fd2 == -1) {
        perror("Error in opening the fifo file 2");
        return 0;
    }
    char buff1[100],buff2[100];
    
    printf("Enter the data you want to send to program2\n");
    scanf("%[^\n]",buff1);	
    write(fd1, buff1, sizeof(buff1));
    read(fd2,buff2,sizeof(buff2));
    printf("Data from Fifo file myfifo2: %s\n",buff2);
    
    close(fd1);
    close(fd2);

    return 0;
}



