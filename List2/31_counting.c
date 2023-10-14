/*
============================================================================
Name : 31_counting.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description :  Write a program to create a semaphore and initialize value to the semaphore.
b. create a counting semaphore

Date: 10th Oct, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <sys/sem.h>

// Function to perform semaphore operations
void semaphoreOperation(int semid, int operation, int semnum) {
    
}

int main() {
    key_t key;
    int semid;

    key = ftok(".", 'a');

    semid = semget(100, 1, IPC_CREAT | 0666);

    if (semid == -1) {
        perror("Error in semget function");
        return 0;
    }

    
    struct sembuf sb;
    sb.sem_num = 0;
    sb.sem_op = 3;// Initialize the counting semaphore to 3
    sb.sem_flg = 0;

    if (semop(semid, &sb, 1) == -1) {
        perror("Error in semop function");
        return 0;
    }
    printf("Counting semaphore created and initialized successfully.\n");
    /*
    // Remove the semaphore (clean up) - optional
    if (semctl(semid, 0, IPC_RMID, 0) == -1) {
        perror("Error in semctl function");
        exit(1);
    }
    */

    return 0;
}






