/*
============================================================================
Name : 29.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to remove the message queue

Date: 9th Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

int main() {
    int msgid;
    key_t key;

    key = ftok(".", 'a');

    msgid = msgget(key,IPC_CREAT|0666);
    if (msgid == -1) {
        perror("Error in msgget function");
        return 0;
    }

    if (msgctl(msgid, IPC_RMID, NULL) == -1) {
        perror("Error in msgctl function");
        return 0;
    }

    printf("Message queue of msgid %d removed.\n",msgid);

    return 0;
}





