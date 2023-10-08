/*
============================================================================
Name : 20_write.c
Author : Ankush Kiran Patil
Roll No : MT2023101
Description : Write two programs so that both can communicate by FIFO - Use one way communication.

Date: 2nd Oct, 2023.
Output : run this files as 
gcc 20_write.c -o write
gcc 20_read.c -o read
./write & ./read
It will run write process run in the background and then the read process execute 
If we try to run process separatly if got blocked due to unavailability the other process when we run other process as well on other terminal then we get the output(this is because FIFO worked in BLOCKING MODE)
============================================================================
*/
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main() {
    int fd;

    if (mkfifo("myfifo", 0666) == -1) {
        perror("Error in mkfifo");
        return 0;
    }

    fd = open("myfifo", O_WRONLY);
    if (fd == -1) {
        perror("Error in opening the fifo file");
        return 0;
    }

    char buff[100] = "Hello, How are You!!!";
    write(fd, buff, sizeof(buff));
    printf("Data sent to the FIFO Now Reader can read the data\n");
    close(fd);

    return 0;
}



