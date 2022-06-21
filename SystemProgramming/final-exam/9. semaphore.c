#include <semaphore.h>
int cnt = 0;
static sem_t sem;

int main(int argc, char *argv[]){
    pthread_t thread1;
    pthread_t thread2;

    if(sem_init(&hsem, 0, 1) < 0){
        fprintf(stderr, "Semaphore Initiliaztion Error");
        return 1;
    }

    //thread 생성
    pthread_create(&thread1, NULL,Thread1, NULL);
    pthread_create(&thread2, NULL, Thread2, NULL);

    //thread 실행
    pthread_join(thread1, NULL);
    pthread_join(thread2, NULL);

    //공유자원 cnt의 현재 값 출력
    printf("%d\n", cnt);

    //semaphore의 키 삭제
    sem_detroy(&hsem);

    return 0;
}

void *Thread1(void *arg){

    int i, tmp;

    for(i = 0; i < 1000; i++){
        //hsem 키 받아오기
        sem_wait(&hsem);
        tmp = cnt;
        usleep(1000);
        cnt = tmp + 1;

        //hsem 키 반납
        sem_post(&hsem);
    }

    printf("Thread1 End\n");

    return NULL;
}

void *Thread2(void *arg){

    int i, tmp;

    for(i = 0; i < 1000; i++){
        //hsem 키 받아오기
        sem_wait(&hsem);
        tmp = cnt;
        usleep(1000);
        cnt = tmp + 1;

        //hsem 키 반납
        sem_post(&hsem);
    }

    printf("Thread2 End\n");

    return NULL;
}