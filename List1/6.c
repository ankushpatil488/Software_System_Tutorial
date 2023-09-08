/*
============================================================================
Name : 6.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to take input from STDIN and display on STDOUT. Use only read/write system call 


Date: 24th Aug, 2023.
============================================================================
*/
#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	char msg[20];
	read(0,msg,20);
	write(1,msg,20);
}
