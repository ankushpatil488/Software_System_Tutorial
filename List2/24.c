/*
============================================================================
Name : 24.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to create a message queue and print the key and message queue id.

Date: 9th Oct, 2023.
Output: check message queue is created or not using ipcs -q
============================================================================
*/
#include <stdio.h>
#include <unistd.h>
#include<sys/msg.h>
#include<sys/ipc.h>
#include<sys/types.h>
int main(){
	int msgid;
	key_t key;
	
	key = ftok(".",'a');
	msgid = msgget(key,IPC_CREAT|IPC_EXCL|0744);
	if (msgid == -1) {
		perror("error in msgget function ");
		return 0;
    	}
	printf("Key value = %d\n",key);
	printf("Message queue id = %d\n",msgid);
}



