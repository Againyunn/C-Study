#include <stdarg.h>
#include <signal.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

void sig_catch(int sig_no){
    printf("sig_catch, %d\n", sig_no);
}

int main(){
    int pid;
    sigset_t mysigset, oldsigset;

    sigemptyset(&mysigset);

    sigaddset(&mysigset, SIGUSR1);

    signal(SIGUSR1, sig_catch);

    sigprocmask(SIG_BLOCK, &mysigset, oldsigset);

    if(pid = fork() == 0){
        sigsuspend(&oldsigset);

        printf("Child wake up\n");
        exit(0);
    }

    else{
        sleep(1);
        kill(pid, SIGUSR1);
        wait();
    }
}



