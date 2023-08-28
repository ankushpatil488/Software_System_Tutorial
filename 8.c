#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<stdio.h>
#include<unistd.h>
	
int main(int argc,char *argv[]){
	if(argc != 2){
		printf("You are useless");
		return 0;
	}

	int fd_read = open(argv[1],O_RDONLY);
	if(fd_read == -1)
	{
		printf("Useless");
	}
	int eof = 0;
	while(!eof){
		char buf;
		while(1){
			int char_read = read(fd_read, &buf, 1);
			if(char_read == 0){
				eof=1;
				break;
			}
			else {
				printf("%c",buf);
				if(buf=='\n')
		        	    break;
			}
		}

		
	}
	int fd_read_close = close(fd_read);
	if(fd_read_close == -1 )
		printf("Useless");
		
	return 0;
}
