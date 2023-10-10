/*
============================================================================
Name : 23.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to print the maximum number of files can be opened within a process and
size of a pipe (circular buffer).

Date: 3rd Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <unistd.h>

int main(){
	long int pipe_buffer_size,max_open_files;
	pipe_buffer_size = pathconf(".",_PC_PIPE_BUF);
	max_open_files = sysconf(_SC_OPEN_MAX);
	printf("Pipe_buf Size is %ld\t Open_Max Size is %ld\n",pipe_buffer_size,max_open_files);
}



