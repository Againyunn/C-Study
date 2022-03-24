#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	int fd[2];
	int file, num;	
	char buf[10];
	int pid;
	
	file = open("input-file", O_RDONLY);
	
	//child 1
	if( fork() == 0){
		pid = getpid();
		
		while( (num = read(file, buf, sizeof(buf))) != 0){
			printf("pid: %d, %s\n", pid, buf);
			sleep(1);
		}
		exit(0);
	} 
	else {
		//child 2
		if( fork() == 0){
			pid = getpid();
			
			while( (num = read(file, buf, sizeof(buf))) != 0){
				printf("pid: %d, %s\n", pid, buf);
				sleep(1);
			}
		}
		//parent 
		else {
			pid = getpid();
			
			while( (num = read(file, buf, sizeof(buf))) != 0){
				printf("pid: %d, %s\n", pid, buf);
				sleep(1);
			}
				wait(NULL);
				wait(NULL);
		}	
	}
}
