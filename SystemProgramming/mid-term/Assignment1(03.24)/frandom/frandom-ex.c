#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* fp;
	char buf[256];
	int rspn;
	long pos;

	//첫번째 파일을 읽기용으로 fp에 저장
	if ((fp = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return 1;
	}

	//fseek를 통해 fp의 offset을 8L으로 변경후 pos에 offset값 저장
	rspn = fseek(fp, 8L, SEEK_SET);
	pos = ftell(fp); // pos == 8L 상태 (fp의 offset == 8L)

	//fp의 offset ~ 256까지의 값을 buf에 저장 후 출력
	fgets(buf, 256, fp);  
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);

	//fp의 offset을 0으로 초기화 한 뒤 pos 업데이트
	rewind(fp);
	pos = ftell(fp); // pos == 0 상태 (fp의 offset == 0)

	//fp의 offset ~ 256까지의 값을 buf에 저장 후 출력
	fgets(buf, 256, fp); 
	fclose(fp);
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);
	return 0;
}
