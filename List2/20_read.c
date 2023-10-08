/*
============================================================================
Name : 20_read.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write two programs so that both can communicate by FIFO -Use one way communication.

Date: 2nd Oct, 2023.

Output : run this files as 
gcc 20_write.c -o write
gcc 20_read.c -o read
./write & ./read
It will run write process run in the background and then the read process execute 
If we try to run process separatly if got blocked due to unavailability the other process when we run other process as well on other terminal then we get the output(this is because FIFO worked in BLOCKING MODE)
==============================================================
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;
    char buffer[256];

    fd = open("myfifo", O_RDONLY);
    if (fd == -1) {
        perror("Error in opening the file");
        return 0;
    }
    
    read(fd, buffer, sizeof(buffer));
    printf("Received data from the FIFO : %s\n", buffer);

    close(fd);
    return 0;
}


