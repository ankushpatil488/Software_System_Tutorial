/*
============================================================================
Name : 19.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Create a FIFO file by
 a. mknod command
 b. mkfifo command
 c. use strace command to find out, which command (mknod or mkfifo) is better.
 c. mknod system call
 d. mkfifo library function


Date: 1st Oct, 2023.

Output :  in the file fifo1_mknod.txt and fifo2_mkfifo.txt we see that mkfifo actually calls mknod() and this
	mkfifo() is just doing some extra steps on top of mknod() because mkfifo() is a library function
	whereas mknod() is the actual system call.
	Therefore, mknod() is always going to be faster than mkfifo().
============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
 

int main() {
    // Create a FIFO file using mknod system call
    if (mknod("fifo1", S_IFIFO | 0666, 0) == -1) {
        perror("mknod Error");
        return 0;
    }

    // Create a FIFO file using mkfifo library function
    if (mkfifo("fifo2", 0666) == -1) {
        perror("mkfifo Error");
        return 0;
    }

    // Use strace to analyze system calls it store the details in mknod_strace.txt and mkfifo_strace.txt files
    system("strace -o fifo1_mknod.txt mknod fifo3 p");
    system("strace -o fifo2_mkfifo.txt mkfifo fifo4");


    return 0;
}



