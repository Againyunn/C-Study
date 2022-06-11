#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int main(void){
	int fd[2];
	int input, output;
	int n;
	char buf[10];
	
	//make pipe in fd
	pipe(fd);
	
	//child process
	if(fork() == 0){
		input = open("input.dat", 0);
		close(fd[0]);
		
		while((n = read(input, buf, 10)) != 0)
			write(fd[1], buf, n);	
		
		close(input);
		close(fd[1]);
		exit(0);
	}
	
	//parent process
	else{
		close(fd[1]);
		
		output = creat("output.dat", 0666);
		while((n = read(fd[0], buf, 10)) != 0){
			write(output, buf, n);
		}
		
		close(output);
		close(fd[0]);
		wait(NULL);
	}
	
	
}
