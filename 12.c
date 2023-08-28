#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>
int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <file_path>\n", argv[0]);
        return 1;
    }

    const char *file_path = argv[1];
    int fd = open(file_path, O_RDONLY);
    
    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    // Retrieve the file access mode flags using fcntl
    int flag = fcntl(fd, F_GETFL);
    if (flag == -1) {
        perror("Error getting file access mode");
        close(fd);
        return 1;
    }

    // Check the file access mode flags
    if ((O_ACCMODE & flag)==O_RDONLY) {
        printf("File is opened in read-only mode\n");
    } else if ((O_ACCMODE & flag)==O_WRONLY) {
        printf("File is opened in write-only mode\n");
    } else if ((O_ACCMODE & flag)==O_RDWR) {
        printf("File is opened in read-write mode\n");
    } else {
        printf("Unable to determine file access mode\n");
    }

    close(fd);

    return 0;
}

