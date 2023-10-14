/*
============================================================================
Name : 31_binary.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to create a semaphore and initialize value to the semaphore.
 a. create a binary semaphore

Date: 10th Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>



int main() {
    key_t key;
    int semid;
    struct sembuf sb;
    key = ftok(".", 'a');

    semid = semget(key, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("Error in semget fuction");
        return 0;
    }

    sb.sem_num = 0;
    sb.sem_op = 1; //Initialize binary semaphore to 1 (unlocked)
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) == -1) {
        perror("Error in semop fuction");
        return 0;
    }
    printf("Binary semaphore created and initialized successfully.\n");

     

    return 0;
}





