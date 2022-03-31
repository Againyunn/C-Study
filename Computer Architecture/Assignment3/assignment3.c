#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>


//읽어와서 2진수로 변환용
int binary[4]; //2진수 변환용
int putNum = 0; //몇 자리나 2진수로 넣을 지
char instructionNum[12]; //지금 읽고 있는 명령어의 2진수
int instructionCheck = 0; //입력된 2진수의 인덱스 수

//메모리 & 레지스터 관련 
//const int M_SIZE = 1024; //메모리크기
unsigned char MEM[1024]; //메모리
unsigned int IR;	//명령어 레지스터
unsigned int countMEM = 0;//메모리 저장 offset
unsigned int countRead = 0; //메모리 읽기 offset


//16진수 → 2진수 변환
void convert(char c, int putNum) {
	int n = 0;
	n = (int)c - 48; // 숫자가 아닐경우 A를 10으로 만들어줌 

	if (n > 9) 
		n -= 7; 
	for (int i = 0; i < 4; i++) { 
		binary[i] = (n % 2); n /= 2; 
	}

	//실제 명령어 bit만 저장
	if (putNum > 0) {
		for (int i = 0; i < putNum; i++) {
			instructionNum[instructionCheck] = (char)binary[i];
			instructionCheck++;
		}
	}

	if (putNum < 0) {
		for (int i = 3; i >= -putNum; i--) {
			instructionNum[instructionCheck] = (char)binary[i];
			instructionCheck++;
		}
	}


}


//레지스터에 명령어만 저장(big-endian활용)
void memoryWrite(unsigned int addr, unsigned int data) { //저장될 메모리의 인덱스 위치, 입력될 데이터

	//입력받은 data를 한 비트(한 글자) 단위로 쪼개기
	/*char* temp = (char)data;*/
	char temp[8];
	sprintf(temp, "%d", data);

	//메모리(1칸)에 hexa bit 2개씩 저장
	for (int i = 1; i < 5; i++) {
		int index = (2 * i) - 1;
		MEM[addr + i] = temp[index];	

		strcat(MEM[addr + i], temp[2 * i]);
	}


}


//메모리(MEM)의 값을 읽고 명령어 디코딩
unsigned int memoryRead(unsigned int addr) {	//읽을 메모리의 인덱스 위치

	//메모리에 저장된 값 불러서 instructionNum에 6bit씩 저장
	for (int i = 0; i < 8; i++) {

		//Opc
		if(i == 0){
			char c;
			int index = 4;
			
			//Opc 출력
			printf("Opc: %x", MEM[addr + i]);

			char* temp = strtok(MEM[addr + i], "");

			while (temp != NULL) {
				convert(temp, index);
				temp = strtok(NULL, " ");
				index /= 2;
			}

		}

		//Fct
		if (i == 7) {
			char c;
			int index = -2;

			//Opc 출력
			printf("Fct: %x", MEM[addr + i]);

			char* temp = strtok(MEM[addr + i], "");

			while (temp != NULL) {
				convert(temp, index);
				temp = strtok(NULL, " ");
				index = -index;
				index *= 2;
			}
		}
	}
	
	//Inst
	//strcmp(000001, instructionNum);

	
}


int main(void) {

	//offset 초기화
	countMEM = 0;
	countRead = 0;

	//파일읽기 관련
	FILE* inputFile = NULL; //입력받은 파일 포인터
	int check; //읽어오기 위한 임의 변수
	unsigned int inputContent; //가져온 big-endian값

	//명령어의 처리 단계
	int count = 0;//현재 단계를 파악하기 위한 count값
	int instNum = 0;//명령어의 개수  /오류 발생 시 unsigned 로 바꾸기
	int dataNum = 0;
	

	fopen_s(&inputFile, "as_ex01_arith.bin", "rb");

	//읽어들인 파일 해석

	//8개의 hexa비트를 확인하여 명령어 개수 파악
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);
	instNum = strtol(inputContent, NULL, 16);	//명령어 개수 파악
	
	printf("%d",instNum);

	//데이터영역의 개수 읽고 데이터 개수 파악
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);
	dataNum = strtol(inputContent, NULL, 16);	//데이터 개수 파악

	//명령어 영역의 수만큼 반복하며 8bit씩 읽어서 메모리에 저장
	for (int i = 0; i < instNum; i++) {

		//한 영역의 명령어(8bit)읽어오기
		check = fread(&inputContent, sizeof(inputContent), 8, inputFile);

		//메모리에 명령어 저장 32bit(8피스)
		memoryWrite(countMEM, inputContent);

		//메모리 쓰기 offset 추가
		countMEM += 8;
	}

	//출력문
	printf("Number of Instructions: %d, Number of Data: %d\n", instNum, dataNum);

	//저장된 메모리에서 명령어 읽고 출력하기
	for (int i = 0; i < instructionNum; i++) {

		//메모리 읽기
		memoryRead(countRead);

		//메모리 읽기 offset 추가
		countRead += 8;

	}

}
		

	




