#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <unistd.h>

void *read_client(void*);

#define SIZE 128
#define FIFO1 "fifo1"//client -> server
#define FIFO2 "fifo2"//server -> client



//main함수
int main(int argc, char *argv[]){
    int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];
    // char inputData[SIZE];
    int  fd1_size, fd2_size;

    //thread관련
    pthread_t read_fifo1;
    
    if(mkfifo(FIFO1, 0666) == -1){
        perror("mkfifo failed");
        exit(1);
    }
    
    if(mkfifo(FIFO2, 0666) == -1){
        perror("mkfifo failed");
        exit(1);
    }

    pthread_create(&read_fifo1, NULL, read_client, NULL);

    pthread_join(read_fifo1, NULL);

    
    //써서 FIFO2에 입력하기(SERVER -> CLIENT)
    while(1){
        if((fd2 = open(FIFO2, O_WRONLY)) == -1){
            perror("open failed");
            exit(1);
        }

        if((fd2_size = read(fd2, buffer_w, SIZE)) == -1){
                perror("read failed");
                exit(1);
            }

        printf("[SERVER]");
        fgets(buffer_w, SIZE, stdin);
        if(write(fd2, buffer_w, SIZE) == -1){
            perror("write failed");
            exit(1);
        }

        if(!strcmp(buffer_w, "quit")){
            printf("Quit chatting\n");
            exit(0);
        }
    } 
}

void *read_client(void *v){
    int fd1;
    char buffer_r[SIZE];
    int  fd1_size;

    if((fd1 = open(FIFO1, O_RDONLY)) == -1){
        perror("open failed");
        exit(1);
    }

    if((fd1_size = read(fd1, buffer_r, SIZE)) == -1){
        perror("read failed");
        exit(1);
    }

	printf("[CLIENT]%s\n", buffer_r);

    if(write(fd1, NULL, SIZE) == -1){
        perror("clear failed");
        exit(1);
    }
}

   





