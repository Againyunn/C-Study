#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <semaphore.h>

//사용할 버퍼의 크기 설정
#define MAX_BSIZE 10

int cnt = 0;//공유자원
static sem_t hsem, num_buff, num_data; //semaphore 변수들


void *Producer(void *arg) {
    int i, tmp;

    for(;;){
        sem_wait(&num_buff);//buffer에 쓸 공간이 있는 지 num_buf의 신호를 받기
        sem_wait(&hsem);//공유자원에 접근하기 위한 semaphore의 신호받기(semaphore lock 얻기)
        
        cnt++; //공유자원에 대한 작업 +1 처리(for문을 한번 순회할 때마다 +1)
        printf("prod cnt: %d \n", cnt);
        sleep(1);

        sem_post(&hsem); //공유자원에 대한 권한을 반환(semaphore lock반환)
        sem_post(&num_data); //buffer에 데이터가 쓰였으므로 num_data의 신호를 전달
    }
    
    printf("Producer Ends\n");
    return NULL;
}


void *Consumer(void *arg){
    int i, tmp;

    for(;;){
        sem_wait(&num_data);//buffer에 쓸 공간이 있는 지 num_data의 신호를 받기
        sleep(1);
        sem_wait(&hsem);//공유자원에 접근하기 위한 semaphore의 신호받기(semaphore lock 얻기)
        
        cnt--; //공유자원에 대한 작업 +1 처리(for문을 한번 순회할 때마다 +1)
        printf("cons cnt: %d \n", cnt);
        
        
        sem_post(&hsem); //공유자원에 대한 권한을 반환(semaphore lock반환)
        sem_post(&num_buff); //buffer의 데이터를 사용했으므로 num_buff의 신호를 전달
    }
    
    printf("Consumer Ends\n");
    return NULL;
}


int main(int argc, char *argv[]){
    //thread 변수 2개 선언
    pthread_t thread1;
    pthread_t thread2;

    //semaphore lock 초기화 : 공유자원에 대한 접근권한 제어용
    if(sem_init(&hsem, 0, 1) < 0){
        fprintf(stderr, "Semaphore Initialization Error\n");
        return 1;
    }

    //semaphore lock 초기화 : buffer에 데이터를 써도 된다는 것을 전달하기 위한 목적
    if(sem_init(&num_buff, 0, MAX_BSIZE) < 0){
        fprintf(stderr, "Semaphore Initialization Error\n");
        return 1;
    }

    //semaphore lock 초기화 : buffer에 데이터가 쓰였다는 것을 전달하기 위한 목적
    if(sem_init(&num_data, 0, 0) < 0){
        fprintf(stderr, "Semaphore Initialization Error\n");
        return 1;
    }

    //thread 2개를 생성하고 동작할 함수 할당
    pthread_create(&thread1, NULL, Producer, NULL);//생산자(+1 작업)
    pthread_create(&thread2, NULL, Consumer, NULL);//소비자(-1 작업)

    //thread 2개 실행
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //현재 공유자원의 값 출력
    printf("%d\n", cnt);

    //semaphore 할당을 해제하여 작업종료
    sem_destroy(&hsem);

    return 0;
}
