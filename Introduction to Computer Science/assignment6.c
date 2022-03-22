#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//문제1 : 정적변수 연습 프로그램
//첫번째 함수
void increaseNum(void)
{
	static check = 0;
	check++;
	if (check == 100)
	{
		printf("현재 나의 값은 = %d\n", check);
	}
}

//두번째 함수
void increaseNumArr(int i)//반복문의 int i 
{
	static int checkArray[100];
	checkArray[i] = i;

	if (i == 99) //i가 99인 경우
	{
		for (int j = 0; j < 100; j++)
			printf("%d\n", checkArray[j]);
	}
	return 0;
}

//문제2 : 로또번호 생성 프로그램
static int realLottoNum[7] = { 6, 12, 19, 23, 34, 42, 35 };
static int newLottoNum[7] = { 0, 0, 0, 0, 0, 0, 0 };

//로또번호 생성 함수
void makingLottoNum(void)
{	

	srand(time(NULL));
	for (int i = 0; i < 7; i++)
	{
		int temp = 0; //임의 변수 지정
		temp = rand() % 45 + 1;
		if (checkDuplicate(temp) == 1) //중복되는 값x인 경우
		{
			newLottoNum[i] = temp;
		}
		else //중복되는 값인 경우
		{
			i--;
		}
	}
}

//로또번호 중복 체크 함수
int checkDuplicate(int num)
{
	for (int i = 0; i < 7; i++)
	{
		if (newLottoNum[i] == num)
		{
			return 0;
		}
	}
	return 1;
}

//로또번호 당첨 여부 체크 함수
void checkSucceed(void)
{
	int pass = 0;
	for (int i = 0; i < 7; i++)
	{
		if (realLottoNum[i] == newLottoNum[i])
		{
			pass++;
		}
	}
	if (pass == 7)
	{
		printf("\n1등에 당첨되었습니다. 축하합니다!\n");
	}
	else
	{
		printf("\n다음 기회에...\n");
	}
}

int main(void)
{
	for (int i = 0; i < 100; i++)
	{	
		increaseNum();
		increaseNumArr(i);
	}
	
	makingLottoNum();
	for (int i = 0; i < 7; i++) //새로 만들어진 로또번호 생성
	{
		printf("%d \t", newLottoNum[i]);
	}
	checkSucceed();

	return 0;
}