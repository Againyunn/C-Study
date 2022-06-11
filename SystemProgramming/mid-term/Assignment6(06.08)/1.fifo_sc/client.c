#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <pthread.h>

void *client(void*);

#define SIZE 128
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"



pthread_mutex_t mutex1 = PTHREAD_MUTEX_INITIALIZER;
pthread_mutex_t mutex2 = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data1 = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_space2 = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data2 = PTHREAD_COND_INITIALIZER;

//main함수
int main(int argc, char *argv[]){
    int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];
    int  fd1_size, fd2_size;
    
    int i;
    pthread_t threads;
    pthread_create (&threads, NULL, client, NULL);

    pthread_join(threads, NULL);
    
    while(1){
        //FIFO2의 server의 값 받아오기
        pthread_mutex_lock(&mutex2);
        
        //test
	printf("get mutex2 lock\n");
        
        if((fd2 = open(FIFO2, O_RDWR)) == -1){
            perror("open failed");
            exit(1);
        }

	fd2_size = read(fd2, buffer_r, SIZE);
	
	//test
	printf("read mutex1 lock %d\n", fd2_size);
	
	/*
        if((fd2_size = read(fd2, buffer_r, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }*/
        //아직 데이터가 없으면 기다리기
        if(fd2_size == 0){
            pthread_cond_wait(&buffer_has_data2, &mutex2);
        }


        // if(!strcmp(buffer_r, "quit")){
        //     printf("Quit chatting\n");
        //     exit(0);
        // }

        printf("[SERVER] %s\n", buffer_r);

        if(write(fd2, NULL, SIZE) == -1){
            perror("clear failed");
            exit(1);
        }

	 close(fd2);
        pthread_cond_signal(&buffer_has_space2);
        pthread_mutex_unlock(&mutex2);
    
    }
    return 0;
}



void *client(void *v){
    int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];
    int  fd1_size, fd2_size;


    while(1){
        pthread_mutex_lock(&mutex1);
	
	//test
	printf("get mutex1 lock\n");
	
        if((fd1 = open(FIFO1, O_WRONLY)) == -1){
            perror("open failed");
            exit(1);
        }

        //FIFO1에 client의 값 입력
        fd1_size = read(fd1, buffer_w, SIZE);
        
        //test
	printf("read mutex1 lock %d\n", fd1_size);
	
        /*if((fd1_size = read(fd1, buffer_w, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }*/
        if(fd1_size != 0){
            pthread_cond_wait(&buffer_has_space1, &mutex1);
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
        
        close(fd1);

        pthread_cond_signal(&buffer_has_data1);
        pthread_mutex_unlock(&mutex1);

       
    }
}
    
