#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>


int main(int argc, char* argv[]) {
	int c;
	FILE* fpin, * fpout;

	//명령어의 인자 수가 맞지 않으면 에러 반환
	if (argc != 3) {
		perror(argv[0]);
		exit(1);
	}

	//첫번째 파일을 읽기용으로 fpin에 저장
	if ((fpin = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		exit(2);
	}

	//두번째 파일을 이어쓰기용으로 fpout에 저장
	if ((fpout = fopen(argv[2], "a")) == NULL) {
		perror(argv[2]);
		exit(3);
	}

	//버퍼 없이 처리 sutbuf(객체, NULL)
	setbuf(fpin, NULL);
	setbuf(fpout, NULL);

	//fpin의 char를 하나씩 읽어서 fpout에 저장
	//fpin을 getc(객체)로 while반복하며 읽어서 putc(객체)로 fout에 저장 
	while ((c = getc(fpin)) != EOF) {
		putc(c, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	exit(0);
}