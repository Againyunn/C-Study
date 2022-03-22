#include <stdio.h>

int main() {
	FILE* pFile = NULL;
	errno_t err;
	int count;
	unsigned int data;
	unsigned int data1 = 0xAABBCCDD;
	unsigned int data2 = 0x11223344;

	//input.bin�� pFile�� ����, err�� �� ��� �� ����(1�̸� ����)
	err = fopen_s(&pFile, "input.bin", "wb");

	if (err) {
		printf("������ �� �� �����ϴ�.\n");
		return 1;
	}

	//������ �����͸� data1�� date2�� �����͸� pFile�� ����
	fwrite(&data1, sizeof(data1), 1, pFile);
	fwrite(&data2, sizeof(data2), 1, pFile);
	
	fclose(pFile);

	err = fopen_s(&pFile, "input.bin", "rb");

	if (err) {
		printf("������ �� �� �����ϴ�.\n");
		return 1;
	}

	//pFile�� �����͸� �о�� data�� ����(���� �߻� ��, 1��ȯ�ǹǷ� count�� ��� �� �����Ͽ� ����)
	while (true) {
		count = fread(&data, sizeof(data1), 1, pFile);

		if (count != 1) //���������� �о����� ������ while Ż��
			break;

		printf("%8x\n", data);
	}

	fclose(pFile);

	return 0;

}