#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 128
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"


//main함수
int main(int argc, char *argv[]){
    int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];

    if((fd1 = open(FIFO1, O_WRONLY)) == -1){
        perror("open failed");
        exit(1);
    }

    if((fd2 = open(FIFO2, O_RDWR)) == -1){
        perror("open failed");
        exit(1);
    }

    while(1){
        //client의 값 입력
        printf("[CLIENT]");
        fgets(buffer_w, SIZE, stdin);

        //FIFO1에 client의 값 입력
        if(write(fd1, buffer_w, SIZE) == -1){
            perror("write failed");
            exit(0);
        }

        if(!strcmp(buffer_w, "quit")){
            printf("Quit chatting\n");
            exit(0);
        }

        //FIFO2의 server의 값 받아오기
        if(read(fd2, buffer_r, SIZE) == -1){
            perror("read failed");
            exit(1);
        }

        // if(!strcmp(buffer_r, "quit")){
        //     printf("Quit chatting\n");
        //     exit(0);
        // }

        printf("[SERVER] %s\n", buffer_r);
    }
}
    
