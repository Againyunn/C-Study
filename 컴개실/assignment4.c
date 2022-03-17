#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
int main(void)
{
	char board[3][3];
	int x, y, k, i, j, t;
	// 보드를 초기화한다.
	for (x = 0; x < 3; x++)
		for (y = 0; y < 3; y++) board[x][y] = ' ';

	// 사용자로부터 위치를 받아서 보드에 표시한다.
	for (k = 0; k < 9; k++) {
		printf("(x, y) 좌표: ");
		scanf(" %d %d", &x, &y);

		if (board[x][y] == ' ')//인덱스가 빈칸일 경우 입력 받기
		{
			if (board[x][y] = (k % 2 == 0)) // 순번에 따라 'X', 'O’입력
				board[x][y] = 'X';
			else
				board[x][y] = 'O';
		}
		else // 다른 사용자가 기존에 입력한 값을 덮어쓸 수 없도록 설정
		{
			printf("\n이미 다른 값이 있습니다.\n다시 입력해주세요.\n");
			k--; //동일한 턴에서 다시 입력하도록 k값 설정
		}

		for (i = 0; i < 3; i++)// 보드를 화면에 그린다
		{
			printf("---|---|---\n");
			printf(" %c | %c | %c \n", board[i][0], board[i][1], board[i][2]);
		}
		printf("---|---|---\n");

		t = 0; //for문 반복 탈출 여부 결정할 임의변수 t
		//t = 0 이면 입력 반복, t = 1이면 반복 정지
		for (j = 0; j < 3; j++) //게임의 승자를 정할 반복문for
		{
			if ((board[j][0] == 'X' && board[j][1] == 'X' && board[j][2] == 'X') || (board[0][j] == 'X' && board[1][j] == 'X' && board[2][j] == 'X'))
			{
				printf("\nX 가 승리했습니다.\n");
				t = 1;
				break;
			}
			if ((board[j][0] == '0' && board[j][1] == '0' && board[j][2] == '0') || (board[0][j] == '0' && board[1][j] == '0' && board[2][j] == '0'))
			{
				printf("\n0 이 승리했습니다.\n");
				t = 1;
				break;
			}
			if (board[0][0] == 'X' && board[1][1] == 'X' && board[2][2] == 'X')
			{
				printf("\nX 가 승리했습니다.\n");
				t = 1;
				break;
			}
			if (board[0][0] == '0' && board[1][1] == '0' && board[2][2] == '0')
			{
				printf("\n0 이 승리했습니다.\n");
				t = 1;
				break;
			}
		}
		if (t == 1) //게임의 승자가 정해졌으므로 for문 탈출하여 프로그램 종료
		{
			break;
		}
	}
	return 0;
}