//arr1�� arr2�� ��Ŀ��� �� ��, result �迭�� ��� ���
#include <stdio.h>;

int main(void)
{
	//1. arr1�� arr2�� ���� 3�� 4�� �̾�� �Ѵ�.

	int arr1[3][4];
	int arr2[3][4];

	//2. arr1, arr2 �迭�� ��, ���� ���̸� ���Ͻÿ�.
	int arr1_col_len = sizeof(arr1[0]) / sizeof(arr1[0][0]); //��
	int arr1_row_len = ((sizeof(arr1)/arr1_col_len) / sizeof(arr1[0][0])); //��

	int arr2_col_len = sizeof(arr2[0]) / sizeof(arr2[0][0]); //��
	int arr2_row_len = ((sizeof(arr2)/arr2_col_len )/ sizeof(arr2[0][0])); //��

	//���� ��� �ݺ��� ���Ǻο� 2.���� ���� arr1, arr2 ��&���� ���̸� ���
	//3. arr1�� 1-12�� ���� ������� �Է�
	int input1 = 1;
	for (int i = 0; i < arr1_row_len; i++)
	{
		for (int j = 0; j < arr1_col_len; j++)
		{
			arr1[i][j] = input1;
			input1 += 1;
		}
	}

	//4. arr2�� 12-1�� ���� ������� �Է�
	int input2 = 12;
	for (int i = 0; i < arr2_row_len; i++)
	{
		for (int j = 0; j < arr2_col_len; j++)
		{
			arr2[i][j] = input2;
			input2 -= 1;
		}
	}
	//�̶� 3��, 4���� scanf() �� ��� x 
	
	//5. arr1 * arr2�� �������� ��� ��� �� result �迭�� ������� �Է�
	int result[3][4];

	for (int i = 0; i < arr1_row_len; i++)
	{
		for (int j = 0; j < arr1_col_len; j++)
		{
			result[i][j] = arr1[i][j] * arr2[i][j];
		}
	}
	
	//6. result ���
	for (int i = 0; i < arr1_row_len; i++)
	{
		for (int j = 0; j < arr1_col_len; j++)
		{
			printf("%d\t", result[i][j]);
		}
		printf("\n");
	}

}


