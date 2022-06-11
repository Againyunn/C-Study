#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

#define BUFFER_SIZE 100 //string식으로 받아서 저장할 버퍼의 크기 100으로 지정

// line형식으로 buffer를 만들어 저장 → 한 문장씩 읽고 저장
int main(int argc, char* argv[]) {

	char ubuf[BUFFER_SIZE], line[BUFFER_SIZE]; //임시 저장용 버퍼
	FILE* fpin, * fpout; //각각 읽기 파일, 쓰기 파일 포인터

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

	//입력파일의 buffer 지정
	if (setvbuf(fpout, ubuf, _IOLBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpout)");
		return 4;
	}

	//출력파일의 buffer 지정
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