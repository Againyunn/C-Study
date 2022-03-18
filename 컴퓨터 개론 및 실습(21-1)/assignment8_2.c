#define _CRT_SECURE_NO_WARNINGS
//#define stderr
#include <stdio.h>

char zero_char[5][5] = //0�� �迭
{   {'0', '0', '1', '0', '0'},
	{'0', '1', '0', '1', '0'},
	{'0', '1', '0', '1', '0'},
	{'0', '1', '0', '1', '0'},
	{'0', '0', '1', '0', '0'}
};

char one_char[5][5] = //1�� �迭
{   {'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'}
};
char two_char[5][5] = //2�� �迭
{   {'0', '1', '1', '0', '0'},
	{'1', '0', '0', '1', '0'},
	{'0', '0', '1', '0','0'},
	{'0', '1', '0', '0', '0'},
	{'1', '1', '1', '1', '0'}
};

char three_char[5][5] = //3�� �迭
{   {'0', '1', '1', '0', '0'},
	{'0', '0', '0', '1', '0'},
	{'0', '1', '1', '1', '0'},
	{'0', '0', '0', '1', '0'},
	{'0', '1', '1', '0', '0'}
};

float accuracy_char = 0.95; //�Ǵ��� ��Ȯ�� ����

char image[5][5];

int OCR(char data[5][5], char input[5][5])
{
	int length = 5;
	int num = 0;

	for (int i = 0; i < length; i++)
	{
		for (int j = 0; j < length; j++)
		{
			if ((data[i][j] == '1') && (input[i][j] == '1'))
			{
				num++;
			}
			if ((data[i][j] == '0') && (input[i][j] == '0'))
			{
				num++;
			}
		}
	}

	int answer = 0;
	if (num >= (int)(25 * accuracy_char))
	{
		answer = 1;
	}
	return answer;


	return 0;
}

int main(void)
{
	FILE *fp;

	char fname[100] = "test.txt";
	char buffer[1000];

	

	if ((fp = fopen(fname, "r")) == NULL)
	{
		fprintf(stderr, "���� %s�� �� �� �����ϴ�.\n", fname);

		exit(1);
	}
	else
	{
		int line_num = 0;
		while (fgets(buffer, 256, fp))
		{
			int len = strlen(buffer);
			//printf("len = %d\n", len);

			for (int c = 0; c < 5; c++)
			{
				image[line_num][c] = buffer[c];
			}
			line_num++;
		}
	}
	fclose(fp);

	if (OCR(zero_char, image) == 1)
	{
		printf("0�� �迭�� ���� �����մϴ�.\n");
	}

	if (OCR(one_char, image) == 1)
	{
		printf("1�� �迭�� ���� �����մϴ�.\n");
	}

	if (OCR(two_char, image) == 1)
	{
		printf("2�� �迭�� ���� �����մϴ�.\n");
	}

	if (OCR(three_char, image) == 1)
	{
		printf("3�� �迭�� ���� �����մϴ�.\n");
	}

	return 0;
}