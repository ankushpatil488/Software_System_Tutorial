/*
============================================================================
Name : 9.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write a program to print the following information about a given file.
 a. inode
 b. number of hard links
 c. uid
 d. gid
 e. size
 f. block size
 g. number of blocks
 h. time of last access
 i. time of last modification
 j. time of last change

Date: 27th Aug, 2023.

============================================================================
*/
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <time.h>

void print_details(char *file_path) {
    struct stat file_stat;
    
    if (stat(file_path, &file_stat) == -1) {
        perror("Error");
        return;
    }
    
    printf("Inode No: %lu\n", file_stat.st_ino);
    printf("Number of Hard Links: %lu\n", file_stat.st_nlink);
    printf("UID: %d\n", file_stat.st_uid);
    printf("GID: %d\n", file_stat.st_gid);
    printf("Size: %ld bytes\n", file_stat.st_size);
    printf("Block Size: %ld bytes\n", file_stat.st_blksize);
    printf("Number of Blocks: %ld\n", file_stat.st_blocks);
    printf("Time of Last Access: %s", ctime(&file_stat.st_atime));
    printf("Time of Last Modification: %s", ctime(&file_stat.st_mtime));
    printf("Time of Last Change: %s", ctime(&file_stat.st_ctime));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Enter file name as well after %s\n", argv[0]);
        return 1;
    }
    
    char *file_path = argv[1];
    print_details(file_path);
    
    return 0;
}
