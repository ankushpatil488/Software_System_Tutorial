#include<stdio.h>
#include<fcntl.h>
#include<string.h>
#include<unistd.h>
int main(){
	int fdold=open("dup.txt",O_WRONLY |O_APPEND,0777);
	if(fdold == -1){
		perror("Failed to open the file");
		close(fdold);
		return 1;
	}
	
	int fdnew=fcntl(fdold,F_DUPFD,5);
	if(fdnew == -1){
		perror("Failed to open the file");
		close(fdnew);
		return 1;
	}
	
	char s[20];
        snprintf(s,sizeof(s),"File Descriptor: %d\n",fdold);
        write(fdold,s, strlen(s));
    
        char t[20];
        snprintf(t,sizeof(t),"File Descriptor: %d\n",fdnew);
        write(fdnew,t, strlen(t));
      
        if(fdold == -1 || fdnew == -1)
		printf("Useless");
		
        return 0;
}
