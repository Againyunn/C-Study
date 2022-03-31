#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>


//�о�ͼ� 2������ ��ȯ��
int binary[4]; //2���� ��ȯ��
int putNum = 0; //�� �ڸ��� 2������ ���� ��
char instructionNum[12]; //���� �а� �ִ� ��ɾ��� 2����
int instructionCheck = 0; //�Էµ� 2������ �ε��� ��

//�޸� & �������� ���� 
//const int M_SIZE = 1024; //�޸�ũ��
unsigned char MEM[1024]; //�޸�
unsigned int IR;	//��ɾ� ��������
unsigned int countMEM = 0;//�޸� ���� offset
unsigned int countRead = 0; //�޸� �б� offset


//16���� �� 2���� ��ȯ
void convert(char c, int putNum) {
	int n = 0;
	n = (int)c - 48; // ���ڰ� �ƴҰ�� A�� 10���� ������� 

	if (n > 9) 
		n -= 7; 
	for (int i = 0; i < 4; i++) { 
		binary[i] = (n % 2); n /= 2; 
	}

	//���� ��ɾ� bit�� ����
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


//�������Ϳ� ��ɾ ����(big-endianȰ��)
void memoryWrite(unsigned int addr, unsigned int data) { //����� �޸��� �ε��� ��ġ, �Էµ� ������

	//�Է¹��� data�� �� ��Ʈ(�� ����) ������ �ɰ���
	/*char* temp = (char)data;*/
	char temp[8];
	sprintf(temp, "%d", data);

	//�޸�(1ĭ)�� hexa bit 2���� ����
	for (int i = 1; i < 5; i++) {
		int index = (2 * i) - 1;
		MEM[addr + i] = temp[index];	

		strcat(MEM[addr + i], temp[2 * i]);
	}


}


//�޸�(MEM)�� ���� �а� ��ɾ� ���ڵ�
unsigned int memoryRead(unsigned int addr) {	//���� �޸��� �ε��� ��ġ

	//�޸𸮿� ����� �� �ҷ��� instructionNum�� 6bit�� ����
	for (int i = 0; i < 8; i++) {

		//Opc
		if(i == 0){
			char c;
			int index = 4;
			
			//Opc ���
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

			//Opc ���
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

	//offset �ʱ�ȭ
	countMEM = 0;
	countRead = 0;

	//�����б� ����
	FILE* inputFile = NULL; //�Է¹��� ���� ������
	int check; //�о���� ���� ���� ����
	unsigned int inputContent; //������ big-endian��

	//��ɾ��� ó�� �ܰ�
	int count = 0;//���� �ܰ踦 �ľ��ϱ� ���� count��
	int instNum = 0;//��ɾ��� ����  /���� �߻� �� unsigned �� �ٲٱ�
	int dataNum = 0;
	

	fopen_s(&inputFile, "as_ex01_arith.bin", "rb");

	//�о���� ���� �ؼ�

	//8���� hexa��Ʈ�� Ȯ���Ͽ� ��ɾ� ���� �ľ�
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);
	instNum = strtol(inputContent, NULL, 16);	//��ɾ� ���� �ľ�
	
	printf("%d",instNum);

	//�����Ϳ����� ���� �а� ������ ���� �ľ�
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);
	dataNum = strtol(inputContent, NULL, 16);	//������ ���� �ľ�

	//��ɾ� ������ ����ŭ �ݺ��ϸ� 8bit�� �о �޸𸮿� ����
	for (int i = 0; i < instNum; i++) {

		//�� ������ ��ɾ�(8bit)�о����
		check = fread(&inputContent, sizeof(inputContent), 8, inputFile);

		//�޸𸮿� ��ɾ� ���� 32bit(8�ǽ�)
		memoryWrite(countMEM, inputContent);

		//�޸� ���� offset �߰�
		countMEM += 8;
	}

	//��¹�
	printf("Number of Instructions: %d, Number of Data: %d\n", instNum, dataNum);

	//����� �޸𸮿��� ��ɾ� �а� ����ϱ�
	for (int i = 0; i < instructionNum; i++) {

		//�޸� �б�
		memoryRead(countRead);

		//�޸� �б� offset �߰�
		countRead += 8;

	}

}
		

	




