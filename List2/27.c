/*
============================================================================
Name : 27.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to receive messages from the message queue.
 a. with 0 as a flag
 b. with IPC_NOWAIT as a flag
Date: 9th Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <errno.h>
#define MAX_MESSAGE_SIZE 100

struct msg_buffer {
    long msg_type;
    char msg_text[MAX_MESSAGE_SIZE];
};

int main() {
    int msgid;
    key_t key;
    struct msg_buffer message;

    key = ftok(".", 'a');
    msgid = msgget(key, 0666);
    if (msgid == -1) {
        perror("error msgget in function");
        return 0;
    }


    if (msgrcv(msgid, &message, sizeof(message), 30, 0) == -1) {
        perror("error msgrcv in function");
        return 0;
    }
    printf("Received message without flags: %s\n", message.msg_text);
    
    
    
    int receive_flags = IPC_NOWAIT;
    if (msgrcv(msgid, &message, sizeof(message), 40, receive_flags) == -1) {
        perror("error msgrcv in function");
        if (errno == ENOMSG) {
            printf("No message available (IPC_NOWAIT flag).\n");
        } 
        else {
            return 0;
        }
    } 
    else {
        printf("Received message with IPC_NOWAIT flag: %s\n", message.msg_text);
    }

    return 0;
}



