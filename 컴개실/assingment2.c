#define _CRT_SECURE_NO_WARNINGS 
#include <stdio.h>

int main(void)
{
	//1. 배열 내 최대값, 최소값 찾기 array[7] = {100, 200, 300, 12, 334, 82, 99}
	int max1 = 0;
	int min1 = 0;
	int a1[] = { 100,200,300,12,334,82,99 };
	int len1 = sizeof(a1) / sizeof(int);
	max1 = a1[0];//초기값 지정
	min1 = a1[0];

	for (int i = 1; i < len1; i++)
	{
		if (max1 < a1[i])
			max1 = a1[i];
		if (min1 > a1[i])
			min1 = a1[i];
	}
	printf("배열 내 최대값 = %d \n", max1);
	printf("배열 내 최소값 = %d \n", min1);

	//2. 배열 내 총 중복횟수를 구해라  array[] = { 9,1,2,3,4,5,6,7,2,8,9,4,5,6}
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
	printf("총 중복 값은 = %d \n", dup);

	//3. 배열에 임의의 값을 넣어서 (길이는 자유), 총합, 평균 값 구하기
	int a3[3]; //배열의 길이를 3으로 지정
	int num = 0;
	int sum = 0;
	int avr = 0;
	for (int i = 0; i < 3; i++)
	{
		printf("num3[%d]에 넣을 값을 입력하세요 : \n", i);
		scanf("%d", &num);
		a3[i] = num;
		sum += a3[i];
	}
	avr = sum / 3;
	printf("총합은 = %d, 평균은 = %d", sum, avr);
}