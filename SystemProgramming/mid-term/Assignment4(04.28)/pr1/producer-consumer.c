#include <stdio.h>
#include <pthread.h>
#include <stdlib.h>
#include "linkedlist.h"

//producer와 consumer 함수 초기화
void* producer(void*);
void* consumer(void*);

//연결리스트 초기화
struct LinkedList theList;
struct Node data;

//연결리스트 함수 초기화
void ListInit(struct LinkedList* plist);
int isEmpty(struct LinkedList* plist);
int isFull(struct LinkedList* plist);
void insertItem(struct LinkedList* plist, int data);
int getItem(struct LinkedList* plist);
void freeAllNode(struct LinkedList* plist);

//pthread변수 선언
pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
pthread_cond_t buffer_has_space = PTHREAD_COND_INITIALIZER;
pthread_cond_t buffer_has_data = PTHREAD_COND_INITIALIZER;

//실행함수
int main(void) {

	int i;
	pthread_t threads[2]; //2개 thread 생성
	
	//연결리스트 생성
	ListInit(&theList);

	//producer와 consumer pthread생성
	pthread_create(&threads[0], NULL, producer, NULL);
	pthread_create(&threads[1], NULL, consumer, NULL);

	//두 pthread 모두 실행
	for (i = 0; i < 2; i++)
		pthread_join(threads[i], NULL);
	return 0;
}

//producer 함수 정의
void *producer(void* v) {
	//인덱스 순서 & 입력할 데이터 i 초기화
	int i;

	for (i = 0; i < 1000; i++) {
		//lock 가져오기
		pthread_mutex_lock(&mutex);

		//연결리스트가 다 찼을 때 wait 처리
		if (isFull(&theList)) {
			pthread_cond_wait(&buffer_has_space, &mutex);
		}

		//연결리스트에 데이터 추가
		insertItem(&theList, i);

		//1초 간격으로 처리
		//sleep(1);
		
		//test
		printf("producer :%d\n",i);

		//consumer에게 lock신호 전달
		pthread_cond_signal(&buffer_has_data);

		//lock 반환
		pthread_mutex_unlock(&mutex);
	}
}

void* consumer(void* v) {
	//인덱스 순서 i와 반환받을 data 초기화
	int i, data;

	for (int i = 0; i < 1000; i++) {
		//lock 가져오기
		pthread_mutex_lock(&mutex);

		//연결리스트가 비어있을 때 wait 처리
		if (isEmpty(&theList)) {
			pthread_cond_wait(&buffer_has_data, &mutex);
		}

		//연결리스트에서 데이터 가져오기
		data = getItem(&theList);

		//1초 간격으로 처리
		//sleep(1);
		
		//test
		//printf("consumer :%d\n",i);

		//consumer에게 lock신호 전달
		pthread_cond_signal(&buffer_has_space);

		//lock 반환
		pthread_mutex_unlock(&mutex);

		printf("data = %d\n", data);

	}
}

//연결리스트  함수 정의
void ListInit(struct LinkedList* plist){

   plist->numOfItems = 0;
   plist->head = NULL;
   plist->tail = NULL;
}

int isEmpty(struct LinkedList* plist){

	if(plist->numOfItems == 0){
		return TRUE;
	} else {
		return FALSE;
	}
}

int isFull(struct LinkedList* plist){

	if(plist->numOfItems == MAX_ITEM){
		return TRUE;
	} else {
		return FALSE;
	}
}


void insertItem(struct LinkedList* plist, int data) {
   struct Node * newNode = (struct Node*)malloc(sizeof(struct Node));
      newNode->data = data;
      newNode->next = NULL;

   if ( plist->head == NULL ) {
      plist->head = newNode;
      plist->tail = newNode;
   } else {
      plist->tail->next = newNode;
      plist->tail = newNode;
   }

   (plist->numOfItems)++;
}

int getItem(struct LinkedList* plist){

	struct Node* tmpNode;
	int ret;
	
	ret = plist->head->data;

	tmpNode = plist->head;
	plist->head = plist->head->next;

	free(tmpNode);
	(plist->numOfItems)--;

	return ret;
}

void freeAllNode(struct LinkedList* plist) {

	struct Node* tmpNode;
	tmpNode = plist->head;

	while(tmpNode != NULL){
		plist->head = plist->head->next;
		free(tmpNode);
		tmpNode = plist->head;

		(plist->numOfItems)--;
	}
}




