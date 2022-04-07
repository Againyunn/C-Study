#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <unistd.h>
#include <string.h>

#define NUM_THREADS3

struct thread_data{
	int thread_id;
	int sum;
	char *message;
	//char message[3][1024];
};

struct thread_data thread_data_array[NUM_THREADS3];
pthread_t threads[NUM_THREADS3];

void *printHello(void *arg){
	struct thread_data *my_data;
	int taskid, sum;
	char *hello_msg;
	
	my_data = (struct thread_data *)arg;
	taskid = my_data->thread_id;
	sum = my_data->sum;
	hello_msg = my_data->message;
	
	printf("taskid = %d\n", taskid);
	printf("sum = %d\n", sum);
	printf("message = %s\n", hello_msg);
}

int main(int argc, char *argv[]){
	int rc, i, sum;
	void *res;
	char messages[3][1024];
	
	strcpy(messages[0], "hello");
	strcpy(messages[1], "System Programming");
	strcpy(messages[2], "World");
	
	for( i = 0; i < 3; i++){
		sum += i;
		
		thread_data_array[i].thread_id = i;
		thread_data_array[i].sum = sum;
		thread_data_array[i].message = messages[i];
		
		rc = pthread_create(&threads[i], NULL, printHello, (void*)&thread_data_array[i]);
	}
	
	for( i = 0; i < 3; i++){
		pthread_join(threads[i], &res);
	}
//
}
