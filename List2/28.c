/*
============================================================================
Name : 28.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to change the exiting message queue permission. (use msqid_ds structure)

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
    struct msqid_ds message_info;

    key = ftok(".", 'a');
    msgid = msgget(key, 0666);

    if (msgid == -1) {
        perror("error msgget in function");
        exit(1);
    }

    if (msgctl(msgid, IPC_STAT, &message_info) == -1) {
        perror("Error in msgctl (IPC_STAT) function");
        exit(1);
    }
    printf("Current message queue has permission: 0%o\n", message_info.msg_perm.mode);
    message_info.msg_perm.mode = 0646;

    if (msgctl(msgid, IPC_SET, &message_info) == -1) {
        perror("Error in msgctl (IPC_SET) function");
        return 0;
    }

    printf("Now message queue has permission: 0%o\n", message_info.msg_perm.mode);

    return 0;
}




