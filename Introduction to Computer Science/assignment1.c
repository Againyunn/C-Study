# include <stdio.h>

int main(void)
{
	//1�� ����
	int b1 = 12;
	int b2 = 6;
	long c1 = 2;
	long c2 = 8;
	float d1 = 3.1;
	double e1 = 15.1;

	//2�� ����
	float float_b2 = (float)b2; 
	int int_d1 = (int)d1; 
	printf("int b2�� float Ÿ������ ��ȯ ��Ų �� : %f \n", float_b2);
	printf("float d1�� int�� Ÿ������ ��ȯ ��Ų �� : %d \n", int_d1);

	//3�� ����
	printf("b1 + b2 = %d \n", b1 + b2); 
	printf("b1 - b2 = %d \n", b1 - b2);
	printf("b1 * b2 = %d \n", b1 * b2);
	printf("b1 / b2 = %d \n", b1 / b2);
	printf("b1 %% b2 = %d \n", b1 % b2);

	//4�� ����
	b1 += 14;
	b2 *= 2;
	printf("+= �����ڸ� ����ؼ� ���� b1�� �� : %d \n", b1);
	printf("*= �����ڸ� ����ؼ� ���� b2�� �� : %d \n", b2);

	//5�� ����
	int result = (c1 > c2) ? c1: c2;
	printf("�� �߿� �� ū ���� %d",result);
	printf("�Դϴ�. \n");


	//6�� ����
	if (b1 > 8)
	{
		printf("b1�� 8���� Ů�ϴ�. \n");
	}
	else
	{
		printf("b1�� 8���� �۽��ϴ�. \n");
	}
}