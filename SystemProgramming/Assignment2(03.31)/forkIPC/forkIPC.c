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
	if( fork() != 0){		
		
		pipe(fd);
		
		//parent
		if( fork() != 0){
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
				printf("parent");
			}
			//test
			printf("parent");
			close(input);
			close(fd[1]);
			wait(NULL);
			wait(NULL);
		}
		
		//child 1
		else{
			close(fd[0]);
			input = open("input", 0);
			
			//extract capital letters from "input" and put them to pipe2
			int countCap = 0;
			while((num = read(input, bufChild1, 10)) != 0){
				for(int i = 0; i < 10; i++){
					if( islower(bufChild1[i]) != 0){
						countCap++;
						bufCap[countCap] = buf[i];
					}
					
					if( countCap == 10){
						write(fd[2], bufCap, countCap);
						countCap = 0;
					}
				}
				
				if( countCap > 0){
					write(fd[2], bufCap, countCap);
				}
				
				//test
				printf("child1");
			}
			
			//get lower letters from pipe1 and put them to pipe2
			while((num = read(fd[1], bufLow, 10)) != 0){
				write(fd[2], bufLow, num);
			}
			
			//test
			printf("child1");
			
			close(input);
			close(fd[2]);
			exit(1);
		}
	}
	//child2
	else{
		close(fd[1]);
		output = open("output", 0);
		while((num = read(fd[2], bufChild2, 10)) != 0){
			write(output, bufChild2, num);
		}
		
		//test
		printf("child1");
			
		close(output);
		close(fd[2]);
		exit(2);
	}
}
