//This is 1.c

#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	int v=symlink("temp","softLink");
	if(v!=0){
		perror("failed");
		return 1;
	}
	int f =link("temp","hardLink");
	if(f!=0){
		perror("failed");
		return 1;
	}
	int e=mknod("destFIFO",S_IFIFO,0);
	if(e!=0)
		perror("failed");
	return 0;
}
