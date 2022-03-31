#include <stdio.h>

#define BUFFER_SIZE 1024 //1kb ����

//full buffer ����Ͽ� ���� ����
int main(void) {
	char ubuf[BUFFER_SIZE], fbuf[BUFFER_SIZE];
	int n;
	FILE* fpin, * fpout;

	if ((fpin = fopen("input.dat", "r")) == NULL) {
		perror("input.dat");
		return 2;
	}

	if ((fpout = fopen("output.dat", "w")) == NULL) {
		perror("output.dat");
		return 3;
	}

	//setvbuf �� ���� = 0 , ���� != 0 ��ȯ
	if (setvbuf(fpin, ubuf, _IOFBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpin");
		return 4;
	}

	if (setvbuf(fpout, ubuf, _IOFBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpout)");
		return 5;
	}

	while ((n = fread(fbuf, sizeof(char), BUFFER_SIZE, fpin)) > 0) {
		fwrite(fbuf, sizeof(char), n, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}
