#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<stdlib.h>
int main(){
	int fd = open("sourcefile.txt", O_RDWR, 0766);
        if(fd==-1){
		perror("error while opening the file");
		close(fd);
		return 1;
	}
	
	struct flock writeLock;
	writeLock.l_type=F_WRLCK;
	writeLock.l_whence=SEEK_SET;
	writeLock.l_start=0;
	writeLock.l_len=0;
	printf("Before Entering into Critical Section \n");
	fcntl(fd,F_SETLKW,&writeLock);
	
	
	
	
	char ticketno[20];
	char *output;
	read(fd,&ticketno,sizeof(ticketno));
	long i=strtol(ticketno,&output,10);

	i++;
	char s[20];
	snprintf(s,sizeof(s),"%ld\n",i);
	printf("Current Ticket No is: %ld\n",i);
	lseek(fd,0L,SEEK_SET);
        write(fd,s,strlen(s));
	//write(fd,&ticketno,sizeof(ticketno));
	
	printf("Inside the Critical Section");
	printf("Press any key to Unlock and press Enter\n");
	getchar();
	writeLock.l_type=F_UNLCK;
	fcntl(fd,F_SETLKW,&writeLock);
	printf("Write Lock is Unlocked");
	close(fd);
	return 0;
}
