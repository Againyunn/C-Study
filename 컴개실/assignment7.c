#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
char word1[] = "Pneumonoultramicroscopicsilicovolcanoconiosis";
char word1_len =0;
char *word2 = "i live in korea";
char word2_len =0;
char word3[60] = "Pneumonoultramicroscopicsilicovolcanoconiosis";
char word4[] = " is the longest word in English";
char my_school[] = "한국외국어대학교";

int main(void)
{
	//1. 함수를 사용하지 않고 NULL값을 제외한 word1, word2의 길이를 word1_len, word2_len에 대입 후 출력

	while (word1[word1_len] != '\0')
	{
		word1_len++;
	}
	while (word2[word2_len] != '\0')
	{
		word2_len++;
	}
	printf("word1의 길이 %d , word2의 길이 %d \n", word1_len, word2_len);

	//2. strncat() 함수를 사용하여 word3에 word4의 10byte 만큼만 연결 후 word3 출력
	strncat(word3, word4, 10);
	printf("%s\n", word3);

	//3. strcmp() 혹은 strncmp()함수를 사용하여 my_school이 한국외국어대학교 인지 검증하는 코드 작성
	if (strcmp(my_school, "한국외국어대학교")==0)
	{
		printf("한국외국어대학교 학생입니다.\n");
	}
	else
	{
		printf("한국외국어대학교 학생이 아닙니다.\n");
	}
}







