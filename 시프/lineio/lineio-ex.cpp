#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BUFFER_SIZE 100 //string������ �޾Ƽ� ������ ������ ũ�� 100���� ����

// line�������� buffer�� ����� ���� �� �� ���徿 �а� ����
int main(int argc, char* argv[]) {

	char ubuf[BUFFER_SIZE], line[BUFFER_SIZE]; //�ӽ� ����� ����
	FILE* fpin, * fpout; //���� �б� ����, ���� ���� ������

	if (argc != 3) {
		perror(argv[0]);
		return 1;
	}

	if ((fpin = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return 2;
	}

	if ((fpout = fopen(argv[2], "a")) == NULL) {
		perror(argv[2]);
		return 3;
	}

	//�Է������� buffer ����
	if (setvbuf(fpout, ubuf, _IOLBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpout)");
		return 4;
	}

	//��������� buffer ����
	if (setvbuf(fpout, ubuf, _IOLBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpout)");
		return 5;
	}


	while (fgets(line, BUFFER_SIZE, fpin) != NULL) {
		fputs(line, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}