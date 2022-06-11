#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(){
    int pid;

    //fork한 child 값 기다리기
    if((pid = fork()) == 0){
        while(1);
    }
    else{
        
        //pid에 SIGKILL 시그널을 전달하여 종료하게 한다.
        kill(pid, SIGKILL);
        printf("send a signal to the child\n");
        
        //프로세스가 종료될 때까지 대기
        wait();
        printf("death of child\n");
    }
}