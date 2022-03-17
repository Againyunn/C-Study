#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h> //srand, rand 


//�� ���� ����(���밪)
int subBtw(int x, int y) {
	return abs(x - y);
}

void testOperator(int x, int y) {

	//hexa ��(16����)
	printf("hexa: x= %x, y= %x\n", x, y);

	//������
	printf("\n%s", "<������>\n");
	printf(" & ����: %x\n", (x& y));
	printf(" | ����: %x\n", (x | y));
	printf(" ^ ����: %x\n", (x ^ y));
	printf(" ~ ����: NOT x = %x\n", (~x));
	printf(" ~ ����: NOT y = %x\n", (~y));

	//shift����
	printf("\n%s", "<shift����>\n");
	printf(" �� ���� ���̸�ŭ �� ���� �տ��� shif����\n");

	int sub = subBtw(x, y);
	int sum = x + y;

	printf(" �� ���� ����: %d\n", sub);
	printf(" �� ���� ��: %d\n", sum);

	printf(" << ����: %x\n", (sum << sub));
	printf(" >> ����: %x\n", (sum >> sub));
}

int main(void) {
	//���� ����
	int x, y = 0;
	srand(time(NULL));

	//5�� ���� ���� ������ x, y ����
	for (int i = 0; i < 5; i++) {
		
		//random x��, y��
		
		x = rand() % 9;
		y = rand() % 9;
		
		testOperator(x, y);
		printf("\n%d�� ���� ��\n\n\n", (i + 1));
	}
	return 0;
}