#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(void) {
	int ref;
	FILE* fp;

	//�б� ���� ���Ϸ� fp�� �����ѵ�, fp�� �� �Է� �õ� �� �翬�� ���� �߻� ��Ȳ
	fp = fopen("test.dat", "r");
	putc('?', fp);
	if (ref = ferror(fp)) {
		printf("ferror() return %d\n", ref);
	}
	
	//fp�� ���� �ʱ�ȭ
	clearerr(fp);

	//fp�� ������ �����Ƿ� 0��ȯ
	printf("ferror() return %d\n", ferror(fp));
	fclose(fp);
	return 0;

	//ferror() : ������ �ִ� ��� == 1�̻��� ��, ������ ���� ��� == 0 ��ȯ
}