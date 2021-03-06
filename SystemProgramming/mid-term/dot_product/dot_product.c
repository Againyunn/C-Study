#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

typedef struct{
	double *a;
	double *b;
	double sum;
	int veclen;
} DOTDATA;

#define NUMTHRDS 4
#define VECLEN 100

DOTDATA dotstr;

pthread_t callThd[NUMTHRDS];
pthread_mutex_t mutexsum;

void *dotprod(void *arg){
	int i, start, end, offset, len;
	double mysum, *x, *y;
	
	offset = (int)arg;
	len = dotstr.veclen;
	start = offset * len;
	end = start + len;
	
	x = dotstr.a;
	y = dotstr.b;
	
	mysum = 0;
	for ( i = start; i < end; i++){
		mysum += (x[i] * y[i]);
	}	
	
	pthread_mutex_lock(&mutexsum);
	dotstr.sum += mysum;
	pthread_mutex_unlock(&mutexsum);
	pthread_exit((void*) 0);
}

main(int argc, char *argv[]){
	int i;
	double *a, *b;
	int status;
	
	a = (double*) malloc(NUMTHRDS * VECLEN * sizeof(double));
	b = (double*) malloc(NUMTHRDS * VECLEN * sizeof(double));
	
	for ( i = 0; VECLEN * NUMTHRDS; i++){
		b[i] = a[i] = 1;
	}
	
	dotstr.veclen = VECLEN;
	dotstr.a = a;
	dotstr.b =b;
	dotstr.sum = 0;
	
	pthread_mutex_init(&mutexsum, NULL);
	
	for(i = 0; i < NUMTHRDS; i++){
		pthread_create(&callThd[i], NULL, dotprod, (void*)i);
	}
	
	for(i = 0; i < NUMTHRDS; i++){
		pthread_join(callThd[i], (void **)&status);
	}
	
	printf("sum = %f \n", dotstr.sum);
	free(a);
	free(b);
	
	pthread_mutex_destroy(&mutexsum);
	pthread_exit(NULL);
}
