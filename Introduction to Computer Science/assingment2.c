#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

int main(void)
{
	//1. �迭 �� �ִ밪, �ּҰ� ã�� array[7] = {100, 200, 300, 12, 334, 82, 99}
	int max1 = 0;
	int min1 = 0;
	int a1[] = { 100,200,300,12,334,82,99 };
	int len1 = sizeof(a1) / sizeof(int);
	max1 = a1[0];//�ʱⰪ ����
	min1 = a1[0];

	for (int i = 1; i < len1; i++)
	{
		if (max1 < a1[i])
			max1 = a1[i];
		if (min1 > a1[i])
			min1 = a1[i];
	}
	printf("�迭 �� �ִ밪 = %d \n", max1);
	printf("�迭 �� �ּҰ� = %d \n", min1);

	//2. �迭 �� �� �ߺ�Ƚ���� ���ض�  array[] = { 9,1,2,3,4,5,6,7,2,8,9,4,5,6}
	int dup = 0;
	int a2[] = { 9,1,2,3,4,5,6,7,2,8,9,4,5,6 };
	int len2;
	len2 = sizeof(a2) / sizeof(int);
	for (int i = 0; i < len2; i++)
	{
		for (int j = 0; j < len2; j++)
		{
			if ((i < j) && (a2[i] == a2[j]))
			{
				dup += 1;
			}
		}
	}
	printf("�� �ߺ� ���� = %d \n", dup);

	//3. �迭�� ������ ���� �־ (���̴� ����), ����, ��� �� ���ϱ�
	int a3[3]; //�迭�� ���̸� 3���� ����
	int num = 0;
	int sum = 0;
	int avr = 0;
	for (int i = 0; i < 3; i++)
	{
		printf("num3[%d]�� ���� ���� �Է��ϼ��� : \n", i);
		scanf("%d", &num);
		a3[i] = num;
		sum += a3[i];
	}
	avr = sum / 3;
	printf("������ = %d, ����� = %d", sum, avr);
}