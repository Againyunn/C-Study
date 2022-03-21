#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE* fp;
	char buf[256];
	int num, Nnum;
	char str[30], Nstr[30];
	
	//사용자에게 num과 str값 입력받기
	scanf("%d %s", &num, str);
	if ((fp = fopen("test.dat", "w")) == NULL) {
		perror("test.dat");
		return 1;
	}

	//fp 파일에 직접 num과 str 입력
	fprintf(fp, "%d %s\n", num, str);

	//freopen을 쓰는 이유: fp에 이미 offset이 설정되어 있다.
	//그러므로 fp의 offset을 초기화하기 위한 방법
	if ((fp = freopen("test.dat", "r", fp)) == NULL) {
		perror("test.dat");
		return 1;
	}

	//fp 파일로부터 num과 str을 받아서, Nnum과 Nstr로 저장
	fscanf(fp, "%d %s\n", &Nnum, Nstr);
	printf("%d %s\n", Nnum, Nstr);

	fclose(fp);
	return 0;
}