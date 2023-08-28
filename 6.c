#include<stdlib.h>
#include<stdio.h>
#include<unistd.h>
int main(){
	char msg[20];
	read(0,msg,20);
	write(1,msg,20);
}
