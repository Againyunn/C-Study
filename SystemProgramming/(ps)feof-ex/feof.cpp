#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int stat = 0;
	FILE* fp;
	char buf[256];

	fp = fopen("test.dat", "r");

	//stat이 0이 아니면 while 반복
	while (!stat)
		//fp의 데이터 중 256만큼 buf에 저장하여 콘솔에 출력
		if (fgets(buf, 256, fp))
			printf("%s\n", buf);
		
		//위의 if문에서 값을 가져오지 못하는 상태(false)이면 stat에 0이 저정되도록
		else
			stat = feof(fp); //feof(포인터) : 포인터의 offset이 끝에 닿았는 지 확인하여 끝이면 0 반환

	printf("feof returned %d\n", stat);
	fclose(fp);
	return 0;
}