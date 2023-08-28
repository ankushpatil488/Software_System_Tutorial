#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	int fd = open("file16.txt", O_RDWR | O_CREAT , 0766);
        if(fd==-1){
		perror("error while opening the file");
		close(fd);
		return 1;
	}
	struct flock readLock;
	readLock.l_type=F_RDLCK;
	readLock.l_whence=SEEK_SET;
	readLock.l_start=0;
	readLock.l_len=0;
	printf("Read Lock going to apply\n");
	fcntl(fd,F_SETLKW,&readLock);
	printf("Read lock is Locked\n");
	printf("Press any key to Unlock read Lock\n");
	getchar();
	readLock.l_type=F_UNLCK;
	fcntl(fd,F_SETLKW,&readLock);
	printf("Read Lock is Unlocked");
	close(fd);
	return 0;
}
