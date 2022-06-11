#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>
#include <ctype.h>

int main(void){
	//pipe 관련
	int pipe1[2];
	int pipe2[2];
	
	//file 읽고 쓰기 관련
	int input, output;
	int num;
	
	//parent
	char buf[10];
	char checkedBuf[10];
	
	//child1
	char bufChild1[10];
	char bufLow[10];
	
	//child2
	char bufChild2[10];
	
	//2개의 파이프 생성
	pipe(pipe2);
	pipe(pipe1);
		
	//parent
	if( fork() != 0){
		input = open("input",0);
		close(pipe1[0]);
		
		//extract lower 10bytes char from input and put them to pipe1
		int count = 0;
		while(( num = read (input, buf, 10)) != 0){
			
			//prevent interrupt
			//close(pipe1[0]);
			checkedBuf[10] = '\0';
			
			for(int i = 0; i < num; i++){
				if( islower(buf[i]) != 0){
					checkedBuf[count] = buf[i];
					count++;
				}
				
				if( count == num-1){
					write(pipe1[1], checkedBuf, count);
					count = 0;
					
				}	
			}
		}

		//put letters remained in checkedBuf to pipe1[1] : 처리되지 못하고 checkedBuf에 남은 값이 있다면 pipe1[1]에 저장
		if(num != 10){
			write(pipe1[1], checkedBuf, count);
		}
		
		close(input);
		close(pipe1[1]);
		
		//childs 종료까지 대기
		wait(NULL);
		wait(NULL);
	}
	
	//child 1
	else{
		close(pipe1[1]);			
		
		//conver lower letter to capital letter
		while((num = read(pipe1[0], bufLow, 10)) != 0){
			
			//prevent interrupt
			//close(pipe1[1]);	
		
			//convert to Capital letter
			for(int i = 0; i < num; i++){
				bufLow[i] = toupper(bufLow[i]);
			}
			
			write(pipe2[1], bufLow, num);
		}
		
		close(pipe2[1]);
		exit(1); //terminate child1
	}

	//child2
	if(fork() == 0){
		close(pipe2[1]);
		
		output = creat("output", 0666);
		while((num = read(pipe2[0], bufChild2, 10)) != 0){
			write(output, bufChild2, num);
		}
		
		close(output);
		close(pipe2[0]);
		exit(2);//terminate child2
	}
}
