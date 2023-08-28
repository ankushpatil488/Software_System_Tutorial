#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
int main(){
    char s[20];
    int a;
    int fd=open("sourcefile.txt", O_RDWR );
    printf("Enter the random value");
    scanf("%d",&a);
    
    snprintf(s,sizeof(s),"%d\n",a);
    write(fd,s,strlen(s));
    close(fd);
    return 1;
}
