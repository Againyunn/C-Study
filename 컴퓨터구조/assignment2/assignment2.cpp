#include <stdio.h>

int main() {
	FILE* pFile = NULL;
	errno_t err;
	int count;
	unsigned int data;
	unsigned int data1 = 0xAABBCCDD;
	unsigned int data2 = 0x11223344;

	//input.bin을 pFile에 저장, err의 그 결과 값 저장(1이면 오류)
	err = fopen_s(&pFile, "input.bin", "wb");

	if (err) {
		printf("파일을 열 수 없습니다.\n");
		return 1;
	}

	//각각의 데이터를 data1과 date2의 데이터를 pFile에 저장
	fwrite(&data1, sizeof(data1), 1, pFile);
	fwrite(&data2, sizeof(data2), 1, pFile);
	
	fclose(pFile);

	err = fopen_s(&pFile, "input.bin", "rb");

	if (err) {
		printf("파일을 열 수 없습니다.\n");
		return 1;
	}

	//pFile의 데이터를 읽어와 data에 저장(에러 발생 시, 1반환되므로 count에 결과 값 저장하여 관찰)
	while (true) {
		count = fread(&data, sizeof(data1), 1, pFile);

		if (count != 1) //정상적으로 읽어지지 않으면 while 탈출
			break;

		printf("%8x\n", data);
	}

	fclose(pFile);

	return 0;

}