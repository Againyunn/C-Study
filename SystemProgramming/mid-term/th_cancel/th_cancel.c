#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>

void *threadFunc(void *arg){
	int count = 0;
	printf("new thread started ... \n");
	int retval;
	
	pthread_setcancelstate(PTHREAD_CANCEL_DISABLE, NULL);
	pthread_setcanceltype(PTHREAD_CANCEL_DEFERRED, NULL);
	
	while(1){
		printf("count = %d \n", count);
		sleep(1);
		count++;
		pthread_testcancel();
		
		//for testing pthread_eixt() return value
		if(count == 10){
			break;
		}
	}
	pthread_exit((void *) count);
}

int main(int argc, char *argv[]){
	pthread_t tid;
	int retval;
	void *res;
	
	pthread_create(&tid, NULL, threadFunc, NULL);
	sleep(5);
	
	pthread_cancel(tid);
	retval = pthread_join(tid, &res);
	
	if(retval != 0){
		perror("pthread_join : ");
		exit(EXIT_FAILURE);
	}
	
	else{
		printf("thread is normal exit retval = %d \n", (int)res);
	}
	
	exit(EXIT_SUCCESS);
}
