/*
============================================================================
Name : 26.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to send messages to the message queue. Check $ipcs -q

Date: 9th Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>

#define MAX_MESSAGE_SIZE 100

struct msg_buffer {
    long int msg_type;
    char msg_text[MAX_MESSAGE_SIZE];
};

int main() {
    int msgid;
    key_t key;
    struct msg_buffer message;

    key = ftok(".", 'a');
    msgid = msgget(key, 0666 | IPC_CREAT);
    if (msgid == -1) {
        perror("error in msgget function");
        return 0;
    }

    printf("Enter message type (msg id): ");
    scanf("%ld", &message.msg_type);
    printf("Enter a message to send to the queue: ");
    scanf(" %[^\n]", message.msg_text);
   
    //while (getchar() != '\n');

    if (msgsnd(msgid, &message, sizeof(message), 0) == -1) {
        perror("error in msgsnd function");
        return 0;
    }

    printf("Message sent to the queue: %s\n", message.msg_text);
    return 0;
}




