#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>
#include <semaphore.h>

void sg_catch(int sig_no){
    printf("signal catch\n");
}

int main(){
    int pid;
    int status;

    //signal을 받았을 때 처리할 함수 지정(SIGUSR1을 받으면 sig_catch가 실행)
    signal(SIGUSR1, sig_catch);

    if((pid = fork()) == 0){
        pause();//정지 → SIGUSR1 신호 발생
        printf("Child wake up\n");
        exit(0);
    }
    else{

        kill(pid, SIGUSR1);//SIGUSR1 신호를 받으면 pid의 작업을 종료
        wait(&status);
    }
}