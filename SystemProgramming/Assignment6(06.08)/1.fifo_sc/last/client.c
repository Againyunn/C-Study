#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <unistd.h>

void *read_server(void*);

#define SIZE 128
#define FIFO1 "fifo1"//client -> server
#define FIFO2 "fifo2"//server -> client


//main함수
int main(int argc, char *argv[]){
  int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];
    int  fd1_size, fd2_size;

    //thread관련
    pthread_t read_fifo2;
    
    pthread_create(&read_fifo2, NULL, read_server, NULL);

    pthread_join(read_fifo2, NULL);
    

    //써서 FIFO1에 입력하기(CLIENT -> SERVER)
    while(1){
        if((fd1 = open(FIFO1, O_WRONLY)) == -1){
            perror("open failed");
            exit(1);
        }

        //FIFO1에 client의 값 입력
        //fd1_size = read(fd1, buffer_w, SIZE);
        if((fd1_size = read(fd1, buffer_w, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }

        printf("[CLIENT]");
        fgets(buffer_w, SIZE, stdin);

        if(write(fd1, buffer_w, SIZE) == -1){
            perror("write failed");
            exit(0);
        }

        if(!strcmp(buffer_w, "quit")){
            printf("Quit chatting\n");
            exit(0);
        }
    }
        
}


void *read_server(void *v){
    int fd2;
    char buffer_r[SIZE];
    int  fd2_size;
    
    if((fd2 = open(FIFO2, O_RDONLY)) == -1){
                perror("open failed");
                exit(1);
    }

    if((fd2_size = read(fd2, buffer_r, SIZE)) == -1){
        perror("read failed");
        exit(1);
    }

    printf("[SERVER] %s\n", buffer_r);

    if(write(fd2, NULL, SIZE) == -1){
        perror("clear failed");
        exit(1);
    }


}