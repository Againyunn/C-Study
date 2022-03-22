#include <stdio.h>

int realAccount = 201703262;
int realPassword = 201703262;

int inputAccount = 0;
int inputPassword = 0;

float budget = 0;

int check_account_password(int inputAccount, int inputPassword) //로그인 정보 확인 함수
{
	if ((realAccount == inputAccount) && (realPassword == inputPassword)) //계좌번호 and 패스워드가 맞는 경우
	{
		return 1;
	}
	else // 계좌번호 and 패스워드가 잘못 된 경우
	{
		return 0;
	}
}

void save(float plus ) //잔액에 입력 받은 금액 가산 함수
{
	budget += plus;
	return;
}

float withdrawl(float minus) //잔액에 입력 받은 금액 감산 함수
{
	budget -= minus;
	return budget;
}

int main(void)//메인 함수
{
	int checkLoop1 = 0;
	while (checkLoop1 == 0) //로그인 루프 구현
	{
		printf("당신의 계좌번호를 입력하세요 :\n");
		scanf_s("%d",&inputAccount);

		printf("당신의 비밀번호를 입력하세요 :\n");
		scanf_s("%d", &inputPassword);

		if (check_account_password(inputAccount, inputPassword) == 1) //로그인 정보 부합여부 확인
		{
			checkLoop1 = 1;
		}
		else
		{
			printf("잘못된 정보입니다. 다시 입력하세요.\n");
			printf("\n");
		}
	}

	int checkLoop2 = 0;
	int checkSwitch = 0;

	while (checkLoop2 == 0) //계좌 입출금 동작 루프 구현
	{
		float inputMoney = 0;
		float printOut = 0;
		
		printf("\n1. 입금  2. 출금  3. 나가기\n");
		scanf_s("%d", &checkSwitch);

		switch (checkSwitch)
		{
		case(1): //입금 
			printf("입금금액 :\n");
			scanf_s("%f", &inputMoney);
			printf("계좌에 %.2f 원 입금되었습니다.\n", inputMoney);
			save(inputMoney);
			break;

		case(2): //출금
			printf("출금금액 :\n");
			scanf_s("%f", &inputMoney);
			printOut=withdrawl(inputMoney);
			printf("계좌에서 %.2f 원 출금되었습니다.\n", inputMoney);
			printf("현재 잔액은 %.2f 원 입니다.\n", printOut);
			break;

		case(3): //나가기
			printf("프로그램을 종료합니다.\n");
			checkLoop2 = 1;
			break;

		default:
			printf("올바른 값을 다시 입력하세요. \n");
			break;
		}
	}
	return 0;
}