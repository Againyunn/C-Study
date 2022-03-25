#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

//읽어와서 2진수로 변환용
int binary[4]; //2진수 변환용
int putNum = 0; //몇 자리나 2진수로 넣을 지
unsigned int instructionNum[12]; //지금 읽고 있는 명령어의 2진수
int instructionCheck = 0; //입력된 2진수의 인덱스 수

//16진수 → 2진수 변환
void convert(unsigned int c, int putNum) {
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
			instructionNum[instructionCheck] = binary[i];
			instructionCheck++;
		}
	}

	if (putNum < 0) {
		for (int i = 3; i >= -putNum; i--) {
			instructionNum[instructionCheck] = binary[i];
			instructionCheck++;
		}
	}


}


//레지스터에 명령어만 저장(big-endian활용)
void memoryWrite(unsigned int addr, unsigned int data) { //저장될 메모리의 인덱스 위치, 입력될 데이터

	//추가필요
}


//메모리(MEM)의 값을 읽고 명령어 디코딩
unsigned int memoryRead(unsigned int addr) {	//읽을 메모리의 인덱스 위치

	//추가필요
}


int main(void) {
	//파일읽기 관련
	FILE* inputFile = NULL; //입력받은 파일 포인터
	int check; //읽어오기 위한 임의 변수
	unsigned int inputContent; //가져온 big-endian값

	//명령어의 처리 단계
	int count = 0;//현재 단계를 파악하기 위한 count값
	int instructionNum = 0;//명령어의 개수  /오류 발생 시 unsigned 로 바꾸기
	

	//메모리 & 레지스터 관련 
	//const int M_SIZE = 1024; //메모리크기
	unsigned char MEM[1024]; //메모리
	unsigned int IR;	//명령어 레지스터
	unsigned int countMEM = 0;//메모리에 저장되는 위치

	fopen_s(&inputFile, "as_ex01_arith.bin", "rb");

	//읽어들인 파일 해석

	//8개의 hexa비트를 확인하여 명령어 개수 파악
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);
	instructionNum = strtol(inputContent, NULL, 16);	//명령어 개수 파악
	

	int totalNum = instructionNum * 8;//실제로 읽어올 명령어 영역의 데이터수
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);	//데이터영역의 개수 읽고 무시
	check = fread(&inputContent, sizeof(inputContent), totalNum, inputFile);	//명령어 영역 읽어오기

	//명령어의 개수만큼 32bit형태의 데이터 중 앞 6개, 뒤 6개 읽고 명령어 구분
	int instructionCount = 0;
	while (instructionNum != 0) { //명령어의 개수만큼 읽을 때까지 반복
		char* temp = (char)inputContent;

		//32bit를 읽어 1개 명령어(12bit)추출
		for (int i = 0; i < 8; i++) {

			if (instructionCount == 0) {
				convert(temp[i], 4);
			}

			if (instructionCount == 1) {
				convert(temp[i], 2);
			}

			if (instructionCount == 6) {
				convert(temp[i], -2);
			}

			if (instructionCount == 7) {
				convert(temp[i], 4);
			}
				
			instructionCount++;
		}

		//메모리에 명령어 저장
		memoryWrite(countMEM, instructionNum);

		countMEM += 12; //1개 명령어를 메모리에 저장했으므로 pointer의 위치 + 12 처리

		instructionNum--;//읽어올 명령어 수 1개 줄이기
	}

	//메모리를 읽어 명령어 디코딩하고 출력

	//추가 필요

}
		

	




