/*
============================================================================
Name : 7.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to copy from one file to other

Date: 25th Aug, 2023.

============================================================================
*/
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
	
int main(int argc,char *argv[]){
	if(argc != 3){
		printf("Please Enter the filename after ./a.out");
		return 0;
	}

	int fd_read = open(argv[1],O_RDONLY);
	int fd_write = open(argv[2],O_WRONLY | O_CREAT,0666);
	if(fd_read == -1 || fd_write == -1)
	{
		printf("Error");
	}
	while(1){
		char buf;
		int char_read = read(fd_read, &buf, 1);
		if(char_read == 0)
			break;
		char char_written = write(fd_write, &buf , 1);
		
	}
	int fd_read_close = close(fd_read);
	int fd_write_close = close(fd_write);
	if(fd_read_close == -1 || fd_write_close == -1)
		printf("Error");
		
	return 0;
}
