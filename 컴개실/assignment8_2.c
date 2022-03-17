#define _CRT_SECURE_NO_WARNINGS
//#define stderr
#include <stdio.h>

char zero_char[5][5] = //0의 배열
{   {'0', '0', '1', '0', '0'},
	{'0', '1', '0', '1', '0'},
	{'0', '1', '0', '1', '0'},
	{'0', '1', '0', '1', '0'},
	{'0', '0', '1', '0', '0'}
};

char one_char[5][5] = //1의 배열
{   {'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'},
	{'0', '0', '1', '0', '0'}
};
char two_char[5][5] = //2의 배열
{   {'0', '1', '1', '0', '0'},
	{'1', '0', '0', '1', '0'},
	{'0', '0', '1', '0','0'},
	{'0', '1', '0', '0', '0'},
	{'1', '1', '1', '1', '0'}
};

char three_char[5][5] = //3의 배열
{   {'0', '1', '1', '0', '0'},
	{'0', '0', '0', '1', '0'},
	{'0', '1', '1', '1', '0'},
	{'0', '0', '0', '1', '0'},
	{'0', '1', '1', '0', '0'}
};

float accuracy_char = 0.95; //판단할 정확도 지정

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
		fprintf(stderr, "파일 %s를 열 수 없습니다.\n", fname);

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
		printf("0번 배열과 가장 유사합니다.\n");
	}

	if (OCR(one_char, image) == 1)
	{
		printf("1번 배열과 가장 유사합니다.\n");
	}

	if (OCR(two_char, image) == 1)
	{
		printf("2번 배열과 가장 유사합니다.\n");
	}

	if (OCR(three_char, image) == 1)
	{
		printf("3번 배열과 가장 유사합니다.\n");
	}

	return 0;
}