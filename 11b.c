#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(){
	int fdold = open("dup.txt",O_WRONLY |O_APPEND ,0777);
	int value;
	//scanf("Enter the fd new %d",&value);
	int fdnew = dup2(fdold,5);
	
	printf("%d\n",fdold);
	printf("%d\n",fdnew);
	
	char s[30];
        snprintf(s,sizeof(s),"File Descriptor of fdold: %d\n",fdold);
        write(fdold,s, strlen(s));
    
        char t[30];
        snprintf(t,sizeof(t),"File Descriptor of fdnew: %d\n",fdnew);
        write(fdnew,t, strlen(t));
      
        if(fdold == -1 || fdnew == -1)
		printf("Useless");
        return 0;
}
