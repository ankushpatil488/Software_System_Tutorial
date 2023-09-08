/*
============================================================================
Name : 23.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to create a Zombie state of the running program.

Date: 2nd Sep, 2023.
============================================================================
*/
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int pid=fork();
	if(pid==0)
	{
		printf("Child Process : %d\n",getpid());
	}
	else{
		sleep(20);
		printf("Parent Process : %d\n",getpid());
	}
}

