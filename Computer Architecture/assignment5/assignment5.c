#include <stdio.h>
//#include <stdlib.h>

//�������
//int addSubtract(int X, int Y, int s0)
//s0�� ���� ADD, SUB����
int addSubtract(int X, int Y, int s0) {
	int ret;

	if (s0 < 0 || s0 > 1) {
		printf("error in addSubtract\n");
		exit(1);
	}
	if (s0 == 0) {//add
		ret = X + Y;

	}
	else {//subtract
		ret = X - Y;

	}

	return ret;
}

//�� ����
//int logicOperation(int X, int Y, int s1s0) 
//s1s0�� ���� AND, OR, XOR, NOR ����
int logicOperation(int X, int Y, int s1s0) {
	if (s1s0 < 0 || s1s0 > 3) {
		printf("error in logic\n");
		exit(1);
	}

	if (s1s0 == 0) {

		return (X & Y);
	}
		
	else if (s1s0 == 1) {

		return (X | Y);
	}

	else if (s1s0 == 2) {

		return (X ^ Y);
	}

	else {

		return (!(X | Y));
	}
}

//����Ʈ ����
//int shiftOperation(int X, int Y, int s1s0)
//s1s0�� ���� No shift, SLL, SRL, SRA ����
int shiftOperation(int V, int Y, int s1s0) { //V�� shift�� �ڸ� ��
	int ret;

	if (s1s0 < 0 || s1s0 > 3) {
		printf("error in shift\n");
		exit(1);
	}

	if (s1s0 == 0) { //No Shift
		ret = Y;
	}

	else if (s1s0 == 1) { // SLL
		ret = Y << V;
	}

	else if (s1s0 == 2) { // SRL
		ret = Y >> V;
	}

	else { //s1s0 == 3 SRA�����ϵ��� ���� (4�� ��Ʈ�� �Էµȴٴ� ����)

		ret = Y >> V;

		//����� ��(���� 2�� ��Ʈ�� 0���� �����)
		if (Y > 0) {
			ret = 0x3 & ret;
		}
		//������ ��(���� 2�� ��Ʈ�� 1�� �����)
		if (Y < 0) {
			ret = 0xF | ret;
		}
		////�׽�Ʈ
		//printf("s1s0 = 3�� ��, ret = %8x\n", ret);
	}

	return ret;
}


//less than �˻�
//int checkSetLess(int X, int Y)
int checkSetLess(int X, int Y) {
	int ret;

	//X < Y�� �� addSubtract()���
	if (addSubtract(X, Y, 1) < 0 ){
		return 1;
	}
	else {
		return 0;
	}

	return ret;
}

//Add/Sub���� ����� 0���� �Ǻ�
//int checkZero(int Oa)
int checkZero(int Oa) {
	int ret;

	//result Oa == zero ���� Ȯ��
	if ( Oa == 0) {
		ret = 1;
	}
	else {
		ret = 0;
	}

	return ret;
}

//int ALU(int x, int Y, int S, int *Z)
int ALU(int X, int Y, int S, int* Z) {
	int s32, s10;
	int ret;

	//0x3 == 0011 
	s32 = (S >> 2) & 0x3;
	s10 = S & 0x3;

	////�׽�Ʈ
	//printf("s32: %8x, s10: %8x\n", s32, s10);

	if (s32 == 0) {
		ret = shiftOperation(X, Y, s10);
	}

	else if(s32 == 1) {
		ret = checkSetLess(X, Y);
	}

	else if (s32 == 2) {
		*Z = s10 & 0x1;//Z�����Ϳ� �����Ͽ� �ܺη� ��ȯ
		Z =  s10 & 0x1;//s0�� ���� �����Ͽ� Z�� ����

		////�׽�Ʈ
		//printf("z: %8x\n", Z);
		ret = addSubtract(X, Y, Z);
	}

	else {
		ret = logicOperation(X, Y, s10);
	}

	return ret;
}

//��� �Լ��� ������ ���� ����
void test(int x, int y) {
	//int x, y, c, s, z;
	int  c, s, z;

	//x = 0xF;
	//y = 0x1;

	printf("x: %8x, y: %8x\n", x, y);

	for (int i = 0; i < 16; i++) {
		////�׽�Ʈ
		//printf("i : %d\n", i);
		s = ALU(x, y, i, &z);
		printf("s: %8x, z: %8x\n", s, z);
	}

	return;
}

int main(void) {
	int x, y, i;

	for (i = 1; i < 20; i += 2) {
		//���� �� Ȯ�ο�
		
		x = i - 1;
		y = i;
		
		printf("�׽�Ʈ%d x: %d, y: %d\n",(i/2), x, y);

		test(x, y);

		printf("\n");
	}

}