#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	char board[3][3];
	int x, y, k, i, j, t;
	// ���带 �ʱ�ȭ�Ѵ�.
	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++) board[x][y] = ' ';

	// ����ڷκ��� ��ġ�� �޾Ƽ� ���忡 ǥ���Ѵ�.
	for (k = 0; k < 9; k++) {
		printf("(x, y) ��ǥ: ");
		scanf(" %d %d", &x, &y);

		if (board[x][y] == ' ')//�ε����� ��ĭ�� ��� �Է� �ޱ�
		{
			if (board[x][y] = (k % 2 == 0)) // ������ ���� 'X', 'O���Է�
				board[x][y] = 'X';
			else
				board[x][y] = 'O';
		}
		else // �ٸ� ����ڰ� ������ �Է��� ���� ��� �� ������ ����
		{
			printf("\n�̹� �ٸ� ���� �ֽ��ϴ�.\n�ٽ� �Է����ּ���.\n");
			k--; //������ �Ͽ��� �ٽ� �Է��ϵ��� k�� ����
		}

		for (i = 0; i < 3; i++)// ���带 ȭ�鿡 �׸���
		{
			printf("---|---|---\n");
			printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
		}
		printf("---|---|---\n");

		t = 0; //for�� �ݺ� Ż�� ���� ������ ���Ǻ��� t
		//t = 0 �̸� �Է� �ݺ�, t = 1�̸� �ݺ� ����
		for (j = 0; j < 3; j++) //������ ���ڸ� ���� �ݺ���for
		{
			if ((board[j][0] == 'X' && board[j][1] == 'X' && board[j][2] == 'X') || (board[0][j] == 'X' && board[1][j] == 'X' && board[2][j] == 'X'))
			{
				printf("\nX �� �¸��߽��ϴ�.\n");
				t = 1;
				break;
			}
			if ((board[j][0] == '0' && board[j][1] == '0' && board[j][2] == '0') || (board[0][j] == '0' && board[1][j] == '0' && board[2][j] == '0'))
			{
				printf("\n0 �� �¸��߽��ϴ�.\n");
				t = 1;
				break;
			}
			if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
			{
				printf("\nX �� �¸��߽��ϴ�.\n");
				t = 1;
				break;
			}
			if (board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0')
			{
				printf("\n0 �� �¸��߽��ϴ�.\n");
				t = 1;
				break;
			}
		}
		if (t == 1) //������ ���ڰ� ���������Ƿ� for�� Ż���Ͽ� ���α׷� ����
		{
			break;
		}
	}
	return 0;
}