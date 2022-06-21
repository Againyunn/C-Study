#include <signal.h>
#include <time.h>

#define SIGTIMER    (SIGRTMAX)
#define ONESHOTTIMER (SIGRTMAX - 1)

timer_t SetTimer(int signo, int sec, int mode);
void SignalHandler(int signo,siginfo_t *info, void *context);
timer_t timerid, oneshotTimer;

int main(){
    struct sigaction sigact;
    sigemptyset(&sigact.sa_mask);
    sigact.sa_flags = SA_SIGINFO;
    sigact.sa_sigaction = SignalHandler;

    if(sigaction(SIGTIMER, &sigact, NULL) == -1){
        perror("sigaction failed");
        return -1;
    }

    if(sigaction(ONESHOTTIMER, &sigact, NULL) == -1){
        perror("sigaction failed");
        return -1;
    }

    timerid = SetTimer(SIGTIMER, 1000, 1);
    oneshotTimer = SetTimer(ONESHOTTIMER, 5000, 0);
    while(1);
    return 0;
}