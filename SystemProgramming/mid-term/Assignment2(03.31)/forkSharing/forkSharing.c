#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <string.h>

int main(int argc, char *argv[]){
	//각 변수 선언
	int fd[2];
	int file, num;	
	char buf[10];
	int pid;
	
	//읽기전용으로 input-file열기
	file = open("input-file", O_RDONLY);
	
	//child 1생성
	if( fork() == 0){
		pid = getpid(); //현 process의 id 호출(child 1)
		
		//input-file에서 10byte만큼 읽어서 buf에 저장 후 terminal에 출력
		while( (num = read(file, buf, sizeof(buf))) != 0){
			printf("pid: %d, %s\n", pid, buf);
			sleep(1); //1초 대기
		}
		exit(0);
	} 
	else { //parent
		//child 2생성
		if( fork() == 0){
			pid = getpid(); //현 process의 id 호출(child 2)
			
			//input-file에서 10byte만큼 읽어서 buf에 저장 후 terminal에 출력
			while( (num = read(file, buf, sizeof(buf))) != 0){
				printf("pid: %d, %s\n", pid, buf);
				sleep(1); //1초 대기
			}
		}
		//parent 
		else {
			pid = getpid(); //현 process의 id 호출(parent)
			
			//input-file에서 10byte만큼 읽어서 buf에 저장 후 terminal에 출력
			while( (num = read(file, buf, sizeof(buf))) != 0){
				printf("pid: %d, %s\n", pid, buf);
				sleep(1); //1초 대기
			}
				//child들이 종료될 때까지 parent process는 대기
				wait(NULL);
				wait(NULL);
		}	
	}
}
