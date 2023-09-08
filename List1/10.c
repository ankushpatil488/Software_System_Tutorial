/*
============================================================================
Name : 10.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to open a file with read write mode, write 10 bytes, move the file pointer by 10
bytes (use lseek) and write again 10 bytes.
 a. check the return value of lseek
 b. open the file with od and check the empty spaces in between the data. 

Date: 28th Aug, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main(int argc,char *argv[]) {
	if(argc!=2){
		printf("Enter file name as well after %s\n", argv[0]);
        	return 1;
        } 
        
    	int fd = open(argv[1], O_RDWR | O_CREAT);
    	if (fd == -1) {
		perror("Error while opening the file");
		return 1;
    	}

    	char buff[11];

    	printf("Enter 10char to store in the file: ");
    	scanf("%s", buff);
    
    	ssize_t bytes_written = write(fd, buff, 10);
    	
    	off_t seek_result = lseek(fd, 10, SEEK_CUR);
    	printf("lseek returned: %ld\n", (long)seek_result);
    	
    	printf("Enter another 10char to store in the file: ");
    	scanf("%s", buff);
    
    	bytes_written = write(fd, buff, 10);
   
        close(fd);
    	return 0;
}
