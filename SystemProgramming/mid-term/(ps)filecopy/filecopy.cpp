#include <stdio.h>

#define BUFFER_SIZE 1024 //1kb 지정

//full buffer 사용하여 파일 복사
int main(int argc, char* argv[]) {
	char ubuf[BUFFER_SIZE], fbuf[BUFFER_SIZE];
	int n;
	FILE* fpin, * fpout;

	if (argc != 3) {
		perror(argv[0]);
		return 1;
	}

	if ((fpin = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return 2;
	}

	if ((fpout = fopen(argv[2], "w")) == NULL) {
		perror(argv[2]);
		return 3;
	}

	//setvbuf 는 성공 = 0 , 실패 != 0 반환
	if (setvbuf(fpin, ubuf, _IOFBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpin");
		return 4;
	}

	if (setvbuf(fpout, ubuf, _IOFBF, BUFFER_SIZE) != 0) {
		perror("setvbuf(fpout)");
		return 5;
	}

	//fread(저장할 버퍼 주소, 개별 사이즈, 인덱스 크기, 읽을 객체)
	while (n = fread(fbuf, sizeof(char), BUFFER_SIZE, fpin) > 0) {
		//fwrite(버퍼 주소, 개별 사이즈, 인덱스 크기, 쓰고 저장할 객체)
		fwrite(fbuf, sizeof(char), n, fpout);
	}

	fclose(fpin);
	fclose(fpout);
	return 0;
}