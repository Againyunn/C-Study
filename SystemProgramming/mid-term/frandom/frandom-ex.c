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
	pos = ftell(fp); // pos == 8L ���� (fp�� offset == 8L)

	fgets(buf, 256, fp);  //fp�� offset ~ 256������ ���� buf�� ����
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);

	rewind(fp);
	pos = ftell(fp); // pos == 0 ���� (fp�� offset == 0)

	fgets(buf, 256, fp); //fp�� offset ~ 256������ ���� buf�� ����
	fclose(fp);
	printf("Position : %ld\n", pos);
	printf("%s\n", buf);
	return 0;
}
