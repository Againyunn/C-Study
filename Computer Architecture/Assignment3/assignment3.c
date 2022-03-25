#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <sys/types.h>
#include <string.h>

//�о�ͼ� 2������ ��ȯ��
int binary[4]; //2���� ��ȯ��
int putNum = 0; //�� �ڸ��� 2������ ���� ��
unsigned int instructionNum[12]; //���� �а� �ִ� ��ɾ��� 2����
int instructionCheck = 0; //�Էµ� 2������ �ε��� ��

//16���� �� 2���� ��ȯ
void convert(unsigned int c, int putNum) {
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


//�������Ϳ� ��ɾ ����(big-endianȰ��)
void memoryWrite(unsigned int addr, unsigned int data) { //����� �޸��� �ε��� ��ġ, �Էµ� ������

	//�߰��ʿ�
}


//�޸�(MEM)�� ���� �а� ��ɾ� ���ڵ�
unsigned int memoryRead(unsigned int addr) {	//���� �޸��� �ε��� ��ġ

	//�߰��ʿ�
}


int main(void) {
	//�����б� ����
	FILE* inputFile = NULL; //�Է¹��� ���� ������
	int check; //�о���� ���� ���� ����
	unsigned int inputContent; //������ big-endian��

	//��ɾ��� ó�� �ܰ�
	int count = 0;//���� �ܰ踦 �ľ��ϱ� ���� count��
	int instructionNum = 0;//��ɾ��� ����  /���� �߻� �� unsigned �� �ٲٱ�
	

	//�޸� & �������� ���� 
	//const int M_SIZE = 1024; //�޸�ũ��
	unsigned char MEM[1024]; //�޸�
	unsigned int IR;	//��ɾ� ��������
	unsigned int countMEM = 0;//�޸𸮿� ����Ǵ� ��ġ

	fopen_s(&inputFile, "as_ex01_arith.bin", "rb");

	//�о���� ���� �ؼ�

	//8���� hexa��Ʈ�� Ȯ���Ͽ� ��ɾ� ���� �ľ�
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);
	instructionNum = strtol(inputContent, NULL, 16);	//��ɾ� ���� �ľ�
	

	int totalNum = instructionNum * 8;//������ �о�� ��ɾ� ������ �����ͼ�
	check = fread(&inputContent, sizeof(inputContent), 8, inputFile);	//�����Ϳ����� ���� �а� ����
	check = fread(&inputContent, sizeof(inputContent), totalNum, inputFile);	//��ɾ� ���� �о����

	//��ɾ��� ������ŭ 32bit������ ������ �� �� 6��, �� 6�� �а� ��ɾ� ����
	int instructionCount = 0;
	while (instructionNum != 0) { //��ɾ��� ������ŭ ���� ������ �ݺ�
		char* temp = (char)inputContent;

		//32bit�� �о� 1�� ��ɾ�(12bit)����
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

		//�޸𸮿� ��ɾ� ����
		memoryWrite(countMEM, instructionNum);

		countMEM += 12; //1�� ��ɾ �޸𸮿� ���������Ƿ� pointer�� ��ġ + 12 ó��

		instructionNum--;//�о�� ��ɾ� �� 1�� ���̱�
	}

	//�޸𸮸� �о� ��ɾ� ���ڵ��ϰ� ���

	//�߰� �ʿ�

}
		

	




