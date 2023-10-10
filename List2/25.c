/*
============================================================================
Name : 25.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to print a message queue's (use msqid_ds and ipc_perm structures)
 a. access permission
 b. uid, gid
 c. time of last message sent and received
 d. time of last change in the message queue
 d. size of the queue
 f. number of messages in the queue
 g. maximum number of bytes allowed
 h. pid of the msgsnd and msgrcv

Date: 9th Oct, 2023.

============================================================================
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <sys/stat.h>
#include <time.h>

int main() {
    int msgid;
    key_t key;
    
    struct msqid_ds message_info;
    struct ipc_perm message_perm;

    key = ftok(".", 'a');
    printf("Key is %d\n",key);
    msgid = msgget(key, 0);

    if (msgid == -1) {
        perror("Error in msgget function");
        exit(1);
    }

    msgctl(msgid, IPC_STAT, &message_info);
    message_perm = message_info.msg_perm;

    printf("Access Permission: 0%o\n", message_perm.mode);
    printf("UID of owner: %d\n", message_perm.uid);
    printf("GID of owner: %d\n", message_perm.gid);
    printf("Time of Last Message Sent: %s", ctime(&message_info.msg_stime));
    printf("Time of Last Message Received: %s", ctime(&message_info.msg_rtime));
    printf("Time of Last Change: %s", ctime(&message_info.msg_ctime));
    printf("Size of Queue: %ld bytes\n", message_info.msg_cbytes);
    printf("Number of Messages in Queue: %ld\n", message_info.msg_qnum);
    printf("Maximum Number of Bytes Allowed in Queue: %ld\n", message_info.msg_qbytes);
    printf("PID of Last msgsnd: %d\n", message_info.msg_lspid);
    printf("PID of Last msgrcv: %d\n", message_info.msg_lrpid);

    return 0;
}






