#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

void *Incrementer();
void *Decrementer();
int counter = 0;

pthread_mutex_t mVar = PTHREAD_MUTEX_INITIALIZER;

void *Incrementer(){
	for(;;){
		pthread_mutex_lock(&mVar);
		counter++;
		printf("Inc : %d \n", counter);
		pthread_mutex_unlock(&mVar);
	}
}

void *Decrementer(){
	for(;;){
		pthread_mutex_lock(&mVar);
		counter--;
		printf("Dec : %d \n", counter);
		pthread_mutex_unlock(&mVar);
	}
}

int main(){
	pthread_t ptid, ctid;
	
	pthread_mutex_init(&mVar, NULL);
	
	pthread_create(&ptid, NULL, Incrementer, NULL);
	pthread_create(&ctid, NULL, Decrementer, NULL);
	pthread_join(ptid, NULL);
	pthread_join(ctid, NULL);
	return 0;
}
