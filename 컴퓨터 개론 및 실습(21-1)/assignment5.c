#include <stdio.h>

int realAccount = 201703262;
int realPassword = 201703262;

int inputAccount = 0;
int inputPassword = 0;

float budget = 0;

int check_account_password(int inputAccount, int inputPassword) //�α��� ���� Ȯ�� �Լ�
{
	if ((realAccount == inputAccount) && (realPassword == inputPassword)) //���¹�ȣ and �н����尡 �´� ���
	{
		return 1;
	}
	else // ���¹�ȣ and �н����尡 �߸� �� ���
	{
		return 0;
	}
}

void save(float plus ) //�ܾ׿� �Է� ���� �ݾ� ���� �Լ�
{
	budget += plus;
	return;
}

float withdrawl(float minus) //�ܾ׿� �Է� ���� �ݾ� ���� �Լ�
{
	budget -= minus;
	return budget;
}

int main(void)//���� �Լ�
{
	int checkLoop1 = 0;
	while (checkLoop1 == 0) //�α��� ���� ����
	{
		printf("����� ���¹�ȣ�� �Է��ϼ��� :\n");
		scanf_s("%d",&inputAccount);

		printf("����� ��й�ȣ�� �Է��ϼ��� :\n");
		scanf_s("%d", &inputPassword);

		if (check_account_password(inputAccount, inputPassword) == 1) //�α��� ���� ���տ��� Ȯ��
		{
			checkLoop1 = 1;
		}
		else
		{
			printf("�߸��� �����Դϴ�. �ٽ� �Է��ϼ���.\n");
			printf("\n");
		}
	}

	int checkLoop2 = 0;
	int checkSwitch = 0;

	while (checkLoop2 == 0) //���� ����� ���� ���� ����
	{
		float inputMoney = 0;
		float printOut = 0;
		
		printf("\n1. �Ա�  2. ���  3. ������\n");
		scanf_s("%d", &checkSwitch);

		switch (checkSwitch)
		{
		case(1): //�Ա� 
			printf("�Աݱݾ� :\n");
			scanf_s("%f", &inputMoney);
			printf("���¿� %.2f �� �ԱݵǾ����ϴ�.\n", inputMoney);
			save(inputMoney);
			break;

		case(2): //���
			printf("��ݱݾ� :\n");
			scanf_s("%f", &inputMoney);
			printOut=withdrawl(inputMoney);
			printf("���¿��� %.2f �� ��ݵǾ����ϴ�.\n", inputMoney);
			printf("���� �ܾ��� %.2f �� �Դϴ�.\n", printOut);
			break;

		case(3): //������
			printf("���α׷��� �����մϴ�.\n");
			checkLoop2 = 1;
			break;

		default:
			printf("�ùٸ� ���� �ٽ� �Է��ϼ���. \n");
			break;
		}
	}
	return 0;
}