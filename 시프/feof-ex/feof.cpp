#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>

int main() {
	int stat = 0;
	FILE* fp;
	char buf[256];

	fp = fopen("test.dat", "r");

	//stat�� 0�� �ƴϸ� while �ݺ�
	while (!stat)
		//fp�� ������ �� 256��ŭ buf�� �����Ͽ� �ֿܼ� ���
		if (fgets(buf, 256, fp))
			printf("%s\n", buf);
		
		//���� if������ ���� �������� ���ϴ� ����(false)�̸� stat�� 0�� �����ǵ���
		else
			stat = feof(fp); //feof(������) : �������� offset�� ���� ��Ҵ� �� Ȯ���Ͽ� ���̸� 0 ��ȯ

	printf("feof returned %d\n", stat);
	fclose(fp);
	return 0;
}