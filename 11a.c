
#include<stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include<string.h>
  
int main()
{
    
  
    int fdold = open("dup.txt", O_WRONLY | O_APPEND |O_CREAT,0777);
      
    if(fdold < 0)
        printf("Error while opening the file\n");
      
    
  
    int fdnew = dup(fdold);
          
     
    //char fd1=file_desc+'0';
    //char fd2=copy_desc+'0';
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
