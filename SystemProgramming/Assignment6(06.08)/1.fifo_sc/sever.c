#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

#define SIZE 128
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"

pthread_mutex_t mutex1 = PTHREAD_MUTEX INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX INITIALIZER;
pthread_cond_t buffer_has_space1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_space2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data2 = PTHREAD_COND_INITIALIZER;

//main함수
int main(int argc, char *argv[]){

    if(mkfifo(FIFO1, 0666) == -1){
        perror("mkfifo failed");
        exit(1);
    }

    if(mkfifo(FIFO2, 0666) == -1){
        perror("mkfifo failed");
        exit(1);
    }
    
    int i;
    pthread_t threads;
    pthread_create (&threads, NULL, server, NULL);

    pthread_join(threads, NULL);
    return 0;

}

void server(void *v){
    int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];
    // char inputData[SIZE];
    int  fd1_size, fd2_size;

    while(1){
        //FIFO1생성: client의 전송 메시지 읽기
        pthread_mutex_lock(&mutex1);

        if((fd1 = open(FIFO1, O_RDWR)) == -1){
            perror("open failed");
            exit(1);
        }
        //FIFO1의 client의 값 받아오기
        if((fd1_size = read(fd1, buffer_r, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }
        //아직 데이터가 없으면 기다리기
        if(fd1_size == 0){
            pthread_cond_wait(&buffer_has_data1, &mutex1);
        }

        // if(!strcmp(buffer_r, "quit")){
        //     printf("Quit chatting\n");
        //     exit(0);
        // }
        printf("[CLIENT]%s\n", buffer_r);

        if(write(fd1, NULL, SIZE) == -1){
            perror("clear failed");
            exit(1);
        }

        pthread_cond_signal(&buffer_has_space1);
        pthread_mutex_unlock(&mutex1);

        //FIFO2생성: server의 메시지를 client에서 전송
        pthread_mutex_lock(&mutex2);
        if((fd2 = open(FIFO2, O_WRONLY)) == -1){
            perror("open failed");
            exit(1);
        }

        //FIFO2에 server의 값 입력
        if((fd2_size = read(fd2, buffer_w, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }
        if(fd2_size != 0){
            pthread_cond_wait(&buffer_has_space2, &mutex2);
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
        pthread_cond_signal(&buffer_has_data2);
        pthread_mutex_unlock(&mutex2);
    }
}