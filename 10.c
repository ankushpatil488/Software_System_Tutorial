#include <sys/types.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>


int main(){

	int fd=open("10data.txt",O_RDWR|O_CREAT, 0666);
	if(fd==-1)
		printf("file not created");

	char buff[30];

	read(STDIN_FILENO,buff,10);
	write(fd,buff,10);
	fflush(stdin);
	lseek(fd,10,SEEK_CUR);

	int c;
	while ((c = getchar()) != '\n' && c != EOF);

	read(STDIN_FILENO,buff,10);
	write(fd,buff,10);

	lseek(fd, 0, SEEK_SET);

	ssize_t bytesRead = read(fd, buff, 30);
	if (bytesRead > 0) {
		write(STDOUT_FILENO, buff, bytesRead);
	} else {
		printf("Error reading from file.\n");
	}

       close(fd);
       return 0;
}

/*
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int main() {
    const char *file_path = "test_file.txt";
    int fd = open(file_path, O_RDWR | O_CREAT | O_TRUNC, 0644);

    if (fd == -1) {
        perror("Error opening file");
        return 1;
    }

    char data[20];

    printf("Enter 10 bytes of data: ");
    fgets(data, sizeof(data), stdin);

    // Writing the user input data
    ssize_t bytes_written1 = write(fd, data, 10);
    if (bytes_written1 != 10) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    // Moving the file pointer by 10 bytes
    off_t seek_offset = lseek(fd, 10, SEEK_CUR);
    if (seek_offset == -1) {
        perror("Error seeking in the file");
        close(fd);
        return 1;
    }

    printf("Enter another 10 bytes of data: ");
    fgets(data, sizeof(data), stdin);

    // Writing the second set of user input data
    ssize_t bytes_written2 = write(fd, data, 10);
    if (bytes_written2 != 10) {
        perror("Error writing to file");
        close(fd);
        return 1;
    }

    close(fd);

    // Display the return value of lseek
    printf("lseek return value: %ld\n", seek_offset);

    // Use od to display the contents of the file
    system("od -c test_file.txt");

    return 0;
}*/

