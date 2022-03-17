#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int ref;
	FILE* fp;

	//읽기 전용 파일로 fp에 저장한뒤, fp에 값 입력 시도 → 당연히 에러 발생 상황
	fp = fopen("test.dat", "r");
	putc('?', fp);
	if (ref = ferror(fp)) {
		printf("ferror() return %d\n", ref);
	}
	
	//fp의 에러 초기화
	clearerr(fp);

	//fp에 에러가 없으므로 0반환
	printf("ferror() return %d\n", ferror(fp));
	fclose(fp);
	return 0;

	//ferror() : 에러가 있는 경우 == 1이상의 값, 에러가 없는 경우 == 0 반환
}