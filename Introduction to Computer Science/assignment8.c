#include <stdio.h>

int zero[5][5] = //0의 배열
{	{0, 0, 1, 0, 0},
	{0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0},
	{0, 1, 0, 1, 0},
	{0, 0, 1, 0, 0}
};

int one[5][5] = //1의 배열
{   {0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0},
	{0, 0, 1, 0, 0}
};

int two[5][5] = //2의 배열
{   {0, 1, 1, 0, 0},
	{1, 0, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{1, 1, 1, 1, 0}
};

int three[5][5] = //3의 배열
{   {0, 1, 1, 0, 0},
	{0, 0, 0, 1, 0},
	{0, 1, 1, 1, 0},
	{0, 0, 0, 1, 0},
	{0, 1, 1, 0, 0}
};

int input[5][5] = //입력 값
{   {0, 1, 1, 1, 0},
	{1, 0, 0, 1, 0},
	{0, 0, 1, 0, 0},
	{0, 1, 0, 0, 0},
	{1, 1, 1, 1, 0}
};

float accuracy = 0.95; //판단할 정확도 지정

//정확도에 따른 정답 판별 함수
int check(int c[5][5]) { 
	int length = 5;
	int num = 0;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if ((c[i][j] == 1) && (input[i][j] == 1))
			{
				num ++;
			}
			if ((c[i][j] == 0) && (input[i][j] == 0))
			{
				num++;
			}
		}
	}

	int answer = 0;
	if (num>= (int)(25 * accuracy))
	{
		answer = 1;
	}
	return answer;
}


int main2(void) {
	if (check(zero) == 1)
	{
		printf("0번 배열과 가장 유사합니다.\n");
	}

	if (check(one) == 1)
	{
		printf("1번 배열과 가장 유사합니다.\n");
	}
	
	if (check(two) == 1)
	{
		printf("2번 배열과 가장 유사합니다.\n");
	}
	
	if (check(three) == 1)
	{
		printf("3번 배열과 가장 유사합니다.\n");
	}
	
	return 0;
}