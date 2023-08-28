#include<stdio.h>
#include<stdlib.h>
#include <sys/select.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
	fd_set rfds;
	struct timeval tv;
	int retval;
	
	FD_ZERO(&rfds);
	FD_SET(0,&rfds);
	
	tv.tv_sec=10;
	tv.tv_usec=0;
	retval=select(1,&rfds,NULL,NULL,&tv);
	
	if(retval)
		printf("Data is available within 10 sec\n");
	else
		printf("Data is not availablewithin 5 sec\n");
}
