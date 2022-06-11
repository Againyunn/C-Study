#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 128
#define FIFO "fifo"

//client 함수
//main함수

int main(int argc, char *argv[]){
    int fd;
    char buffer[SIZE];

    if((fd = open(FIFO, O_WRONLY)) == -1){
        perror("open failed");
        exit(1);
    }

    while(1){
        printf("[CLIENT]");
        fgets(buffer, SIZE, stdin);

        if(write(fd, buffer, SIZE) == -1){
            perror("write failed");
            exit(0);
        }

        if(!strcmp(buffer, "quit", 4) == 0){
            printf("Quit\n");
        }
    }
}
    
//fgets로 문장 입력받기

//입력받은 문장이 quit인지 식별

//quit이면 종료

//입력받은 문장을 client에 전달



