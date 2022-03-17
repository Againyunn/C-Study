#include <stdio.h>
#include <stdlib.h>
#include <time.h>

//����1 : �������� ���� ���α׷�
//ù��° �Լ�
void increaseNum(void)
{
	static check = 0;
	check++;
	if (check == 100)
	{
		printf("���� ���� ���� = %d\n", check);
	}
}

//�ι�° �Լ�
void increaseNumArr(int i)//�ݺ����� int i 
{
	static int checkArray[100];
	checkArray[i] = i;

	if (i == 99) //i�� 99�� ���
	{
		for (int j = 0; j < 100; j++)
			printf("%d\n", checkArray[j]);
	}
	return 0;
}

//����2 : �ζǹ�ȣ ���� ���α׷�
static int realLottoNum[7] = { 6, 12, 19, 23, 34, 42, 35 };
static int newLottoNum[7] = { 0, 0, 0, 0, 0, 0, 0 };

//�ζǹ�ȣ ���� �Լ�
void makingLottoNum(void)
{	

	srand(time(NULL));
	for (int i = 0; i < 7; i++)
	{
		int temp = 0; //���� ���� ����
		temp = rand() % 45 + 1;
		if (checkDuplicate(temp) == 1) //�ߺ��Ǵ� ��x�� ���
		{
			newLottoNum[i] = temp;
		}
		else //�ߺ��Ǵ� ���� ���
		{
			i--;
		}
	}
}

//�ζǹ�ȣ �ߺ� üũ �Լ�
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

//�ζǹ�ȣ ��÷ ���� üũ �Լ�
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
		printf("\n1� ��÷�Ǿ����ϴ�. �����մϴ�!\n");
	}
	else
	{
		printf("\n���� ��ȸ��...\n");
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
	for (int i = 0; i < 7; i++) //���� ������� �ζǹ�ȣ ����
	{
		printf("%d \t", newLottoNum[i]);
	}
	checkSucceed();

	return 0;
}