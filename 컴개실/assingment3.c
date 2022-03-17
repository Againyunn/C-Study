//arr1과 arr2을 행렬연산 한 후, result 배열에 담아 출력
#include <stdio.h>;

int main(void)
{
	//1. arr1와 arr2는 각각 3행 4열 이어야 한다.

	int arr1[3][4];
	int arr2[3][4];

	//2. arr1, arr2 배열의 행, 열의 길이를 구하시오.
	int arr1_col_len = sizeof(arr1[0]) / sizeof(arr1[0][0]); //열
	int arr1_row_len = ((sizeof(arr1)/arr1_col_len) / sizeof(arr1[0][0])); //행

	int arr2_col_len = sizeof(arr2[0]) / sizeof(arr2[0][0]); //열
	int arr2_row_len = ((sizeof(arr2)/arr2_col_len )/ sizeof(arr2[0][0])); //행

	//이하 모든 반복문 조건부에 2.에서 구한 arr1, arr2 행&열의 길이를 사용
	//3. arr1는 1-12의 값을 순서대로 입력
	int input1 = 1;
	for (int i = 0; i < arr1_row_len; i++)
	{
		for (int j = 0; j < arr1_col_len; j++)
		{
			arr1[i][j] = input1;
			input1 += 1;
		}
	}

	//4. arr2는 12-1의 값을 순서대로 입력
	int input2 = 12;
	for (int i = 0; i < arr2_row_len; i++)
	{
		for (int j = 0; j < arr2_col_len; j++)
		{
			arr2[i][j] = input2;
			input2 -= 1;
		}
	}
	//이때 3번, 4번은 scanf() 값 사용 x 
	
	//5. arr1 * arr2의 연산결과를 모두 출력 및 result 배열에 순서대로 입력
	int result[3][4];

	for (int i = 0; i < arr1_row_len; i++)
	{
		for (int j = 0; j < arr1_col_len; j++)
		{
			result[i][j] = arr1[i][j] * arr2[i][j];
		}
	}
	
	//6. result 출력
	for (int i = 0; i < arr1_row_len; i++)
	{
		for (int j = 0; j < arr1_col_len; j++)
		{
			printf("%d\t", result[i][j]);
		}
		printf("\n");
	}

}


