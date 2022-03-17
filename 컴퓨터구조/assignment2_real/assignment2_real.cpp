#include <stdio.h>

unsigned int invertEndian(unsigned int inputValue) {
	unsigned char bytes[4]; 
	int result; 
	
	bytes[0] = (unsigned char)((inputValue >> 24) & 0xff);
	bytes[1] = (unsigned char)((inputValue >> 16) & 0xff);
	bytes[2] = (unsigned char)((inputValue >> 8) & 0xff);
	bytes[3] = (unsigned char)((inputValue >> 0) & 0xff);
	
	//little-endian���� ��ȯ�Ͽ� result�� ����
	result = (
		(int)bytes[0] << 0) | 
		((int)bytes[1] << 8) | 
		((int)bytes[2] << 16) | 
		((int)bytes[3] << 24
			); 
	
	return result;
}


int main() {
	FILE* inputFile = NULL;
	FILE* outputFile = NULL;

	int count = 0; //�ʱⰪ result ����� üũ ����
	int check; //�о���� ���� ���� ����
	unsigned int inputContent; //������ big-endian��
	unsigned int outputContent; //������ little-endian��
	unsigned int result = NULL; // 19���� �������� xor�� ��(hexa��¿�)


	//������ ���� �����Ͽ� ���������Ϳ� ����
	fopen_s(&outputFile, "output.bin", "wb");
	fopen_s(&inputFile, "input.bin", "rb");
	
	//big-endian���Ͽ��� ������ �о����
	while (true) {
		check = fread(&inputContent, sizeof(inputContent), 1, inputFile);
		
		//�о���� Ż������
		if (check != 1)
			break;

		//little-endian���� ��ȯ
		outputContent = invertEndian(inputContent);

		//little-endian ����
		fwrite(&outputContent, sizeof(outputContent), 1, outputFile);


		//�׽�Ʈ��
		//printf("big-endian: %8x\n", inputContent);
		//printf("little-endian: %8x\n", outputContent);
		//printf("n-th Loop: %d\n", count + 1);


		//xor�� ���� ����
		if (count == 0) //ó���� ��� result �ʱⰪ ����
			result = outputContent;

		else
			result = result ^ outputContent;

		//�������� ���� 1ȸ �������Ƿ� count++ó��
		count++;
	}
	
	printf("19�� ������ XOR��� : %8x\n", result);

	fclose(outputFile);
	fclose(inputFile);

}