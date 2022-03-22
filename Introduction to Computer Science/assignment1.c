# include <stdio.h>

int main(void)
{
	//1번 문항
	int b1 = 12;
	int b2 = 6;
	long c1 = 2;
	long c2 = 8;
	float d1 = 3.1;
	double e1 = 15.1;

	//2번 문항
	float float_b2 = (float)b2; 
	int int_d1 = (int)d1; 
	printf("int b2를 float 타입으로 변환 시킨 값 : %f \n", float_b2);
	printf("float d1를 int로 타입으로 변환 시킨 값 : %d \n", int_d1);

	//3번 문항
	printf("b1 + b2 = %d \n", b1 + b2); 
	printf("b1 - b2 = %d \n", b1 - b2);
	printf("b1 * b2 = %d \n", b1 * b2);
	printf("b1 / b2 = %d \n", b1 / b2);
	printf("b1 %% b2 = %d \n", b1 % b2);

	//4번 문항
	b1 += 14;
	b2 *= 2;
	printf("+= 연산자를 사용해서 만든 b1의 값 : %d \n", b1);
	printf("*= 연산자를 사용해서 만든 b2의 값 : %d \n", b2);

	//5번 문항
	int result = (c1 > c2) ? c1: c2;
	printf("둘 중에 더 큰 수는 %d",result);
	printf("입니다. \n");


	//6번 문항
	if (b1 > 8)
	{
		printf("b1은 8보다 큽니다. \n");
	}
	else
	{
		printf("b1은 8보다 작습니다. \n");
	}
}