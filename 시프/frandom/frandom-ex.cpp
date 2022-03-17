#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char* argv[]) {
	FILE* fp;
	char buf[256];
	int rspn;
	long pos;

	if ((fp = fopen(argv[1], "r")) == NULL) {
		perror(argv[1]);
		return 1;
	}

	rspn = fseek(fp, 8L, SEEK_SET);
	pos = ftell(fp); // pos == 8L 상태 (fp의 offset == 8L)

	fgets(buf, 256, fp);  //fp의 offset ~ 256까지의 값을 buf에 저장
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);

	rewind(fp);
	pos = ftell(fp); // pos == 0 상태 (fp의 offset == 0)

	fgets(buf, 256, fp); //fp의 offset ~ 256까지의 값을 buf에 저장
	fclose(fp);
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);
}