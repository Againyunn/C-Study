#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
char word1[] = "Pneumonoultramicroscopicsilicovolcanoconiosis";
char word1_len =0;
char *word2 = "i live in korea";
char word2_len =0;
char word3[60] = "Pneumonoultramicroscopicsilicovolcanoconiosis";
char word4[] = " is the longest word in English";
char my_school[] = "�ѱ��ܱ�����б�";

int main(void)
{
	//1. �Լ��� ������� �ʰ� NULL���� ������ word1, word2�� ���̸� word1_len, word2_len�� ���� �� ���

	while (word1[word1_len] != '\0')
	{
		word1_len++;
	}
	while (word2[word2_len] != '\0')
	{
		word2_len++;
	}
	printf("word1�� ���� %d , word2�� ���� %d \n", word1_len, word2_len);

	//2. strncat() �Լ��� ����Ͽ� word3�� word4�� 10byte ��ŭ�� ���� �� word3 ���
	strncat(word3, word4, 10);
	printf("%s\n", word3);

	//3. strcmp() Ȥ�� strncmp()�Լ��� ����Ͽ� my_school�� �ѱ��ܱ�����б� ���� �����ϴ� �ڵ� �ۼ�
	if (strcmp(my_school, "�ѱ��ܱ�����б�")==0)
	{
		printf("�ѱ��ܱ�����б� �л��Դϴ�.\n");
	}
	else
	{
		printf("�ѱ��ܱ�����б� �л��� �ƴմϴ�.\n");
	}
}







