/*
============================================================================
Name : 8.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to open a file in read only mode, read line by line and display each line as it is read.
Close the file when end of file is reached.

Date: 26th Aug, 2023.

============================================================================
*/
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
	
int main(int argc,char *argv[]){
	if(argc != 2){
		printf("Please Enter the filename after ./a.out");
		return 0;
	}

	int fd_read = open(argv[1],O_RDONLY);
	if(fd_read == -1)
	{
		printf("Error");
		return 1;
	}
	int eof = 0;
	while(!eof){
		char buf;
		while(1){
			int char_read = read(fd_read, &buf, 1);
			if(char_read == 0){
				eof=1;
				break;
			}
			else {
				printf("%c",buf);
				if(buf=='\n')
		        	    break;
			}
		}

		
	}
	int fd_read_close = close(fd_read);
	if(fd_read_close == -1 )
		printf("Error");
		
	return 0;
}
