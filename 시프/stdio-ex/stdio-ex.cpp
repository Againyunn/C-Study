#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main(int argc, char *argv[]) {
	FILE* fp;
	char buf[256];
	int num, Nnum;
	char str[30], Nstr[30];
	
	//����ڿ��� num�� str�� �Է¹ޱ�
	scanf("%d %s", &num, str);
	if ((fp = fopen("test.dat", "w")) == NULL) {
		perror("test.dat");
		return 1;
	}

	//fp ���Ͽ� ���� num�� str �Է�
	fprintf(fp, "%d %s\n", num, str);

	//freopen�� ���� ����: fp�� �̹� offset�� �����Ǿ� �ִ�.
	//�׷��Ƿ� fp�� offset�� �ʱ�ȭ�ϱ� ���� ���
	if ((fp = freopen("test.dat", "r", fp)) == NULL) {
		perror("test.dat");
		return 1;
	}

	//fp ���Ϸκ��� num�� str�� �޾Ƽ�, Nnum�� Nstr�� ����
	fscanf(fp, "%d %s\n", &Nnum, Nstr);
	printf("%d %s\n", Nnum, Nstr);

	fclose(fp);
	return 0;
}