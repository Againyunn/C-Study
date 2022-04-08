#include <stdio.h>
//#include <stdlib.h>

//산술연산
//int addSubtract(int X, int Y, int s0)
//s0에 따라 ADD, SUB결정
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

//논리 연산
//int logicOperation(int X, int Y, int s1s0) 
//s1s0에 따라 AND, OR, XOR, NOR 결정
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

//시프트 연산
//int shiftOperation(int X, int Y, int s1s0)
//s1s0에 따라 No shift, SLL, SRL, SRA 결정
int shiftOperation(int V, int Y, int s1s0) { //V는 shift할 자리 수
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

	else { //s1s0 == 3 SRA연산하도록 설정 (4개 비트가 입력된다는 가정)

		ret = Y >> V;

		//양수일 때(앞의 2개 비트를 0으로 만들기)
		if (Y > 0) {
			ret = 0x3 & ret;
		}
		//음수일 때(앞의 2개 비트를 1로 만들기)
		if (Y < 0) {
			ret = 0xF | ret;
		}
		////테스트
		//printf("s1s0 = 3일 때, ret = %8x\n", ret);
	}

	return ret;
}


//less than 검사
//int checkSetLess(int X, int Y)
int checkSetLess(int X, int Y) {
	int ret;

	//X < Y일 때 addSubtract()사용
	if (addSubtract(X, Y, 1) < 0 ){
		return 1;
	}
	else {
		return 0;
	}

	return ret;
}

//Add/Sub연산 결과가 0인지 판별
//int checkZero(int Oa)
int checkZero(int Oa) {
	int ret;

	//result Oa == zero 인지 확인
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

	////테스트
	//printf("s32: %8x, s10: %8x\n", s32, s10);

	if (s32 == 0) {
		ret = shiftOperation(X, Y, s10);
	}

	else if(s32 == 1) {
		ret = checkSetLess(X, Y);
	}

	else if (s32 == 2) {
		*Z = s10 & 0x1;//Z포인터에 저장하여 외부로 반환
		Z =  s10 & 0x1;//s0의 값만 추출하여 Z에 저장

		////테스트
		//printf("z: %8x\n", Z);
		ret = addSubtract(X, Y, Z);
	}

	else {
		ret = logicOperation(X, Y, s10);
	}

	return ret;
}

//모든 함수를 실행할 메인 로직
void test(int x, int y) {
	//int x, y, c, s, z;
	int  c, s, z;

	//x = 0xF;
	//y = 0x1;

	printf("x: %8x, y: %8x\n", x, y);

	for (int i = 0; i < 16; i++) {
		////테스트
		//printf("i : %d\n", i);
		s = ALU(x, y, i, &z);
		printf("s: %8x, z: %8x\n", s, z);
	}

	return;
}

int main(void) {
	int x, y, i;

	for (i = 1; i < 20; i += 2) {
		//현재 값 확인용
		
		x = i - 1;
		y = i;
		
		printf("테스트%d x: %d, y: %d\n",(i/2), x, y);

		test(x, y);

		printf("\n");
	}

}