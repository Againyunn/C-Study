#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <stdlib.h> //srand, rand 


//두 수의 차이(절대값)
int subBtw(int x, int y) {
	return abs(x - y);
}

void testOperator(int x, int y) {

	//hexa 값(16진수)
	printf("hexa: x= %x, y= %x\n", x, y);

	//논리연산
	printf("\n%s", "<논리연산>\n");
	printf(" & 연산: %x\n", (x& y));
	printf(" | 연산: %x\n", (x | y));
	printf(" ^ 연산: %x\n", (x ^ y));
	printf(" ~ 연산: NOT x = %x\n", (~x));
	printf(" ~ 연산: NOT y = %x\n", (~y));

	//shift연산
	printf("\n%s", "<shift연산>\n");
	printf(" 두 수의 차이만큼 두 수의 합에서 shif연산\n");

	int sub = subBtw(x, y);
	int sum = x + y;

	printf(" 두 수의 차이: %d\n", sub);
	printf(" 두 수의 합: %d\n", sum);

	printf(" << 연산: %x\n", (sum << sub));
	printf(" >> 연산: %x\n", (sum >> sub));
}

int main(void) {
	//변수 정의
	int x, y = 0;
	srand(time(NULL));

	//5번 루프 돌며 데이터 x, y 선언
	for (int i = 0; i < 5; i++) {
		
		//random x값, y값
		
		x = rand() % 9;
		y = rand() % 9;
		
		testOperator(x, y);
		printf("\n%d번 연산 끝\n\n\n", (i + 1));
	}
	return 0;
}