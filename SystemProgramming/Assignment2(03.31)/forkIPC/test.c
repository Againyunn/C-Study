#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int main(void){
	int fd[3];
	int input, output;
	int num;
	char buf[10];
	char checkedBuf[10];
	
	char bufCap[10];
	char bufChild1[10];
	char bufLow[10];
	
	char bufChild2[10];
	
	pipe(fd);
	
	//parent
	
		
	pipe(fd);
	
	//parent

	input = open("input",0);
	close(fd[0]);
	
	//extract lower 10bytes char from input and put them to pipe1
	int count = 0;
	while(( num = read (input, buf, 10)) != 0){
		for(int i = 0; i < 10; i++){
			if( islower(buf[i]) != 0){
				count++;
				checkedBuf[count] = buf[i];
			}
			
			if( count == 10){
				write(fd[1], checkedBuf, count);
				count = 0;
			}
		}
		
		if( count > 0){
			write(fd[1], checkedBuf, count);
		}
		//test
		printf("%s",checkedBuf);
	}
	//test
	printf("parent");
	close(input);
	close(fd[1]);

	
		
	

}
