#define _CRT_SECURE_NO_WARNINGS
#define ARRAY_SIZE 10

#include <stdio.h>

int main(int argc, char* argv[]) {
	int i;
	int sample_array[ARRAY_SIZE]; //�迭�� ���� ���� ����Ǿ� �ִٰ� ����
	FILE* stream; //����ڿ��� �Է¹��� ������ pointer

	if (argc != 3) {
		perror(argv[0]);
		exit(1);
	}

	//stream pointer�� �Է¹��� ���Ϸ� ����
	if ((stream = fopen(argv[1], "w")) == NULL) {
		perror(argv[1]);
		return 1;
	}

	//sample_array�� ��ġ�� �� �״�� ��� stream pointer�� ����
	if (fwrite(sample_array, sizeof(int), ARRAY_SIZE, stream) != ARRAY_SIZE) {
		perror("fwrite error");
		return 2;
	}

}

