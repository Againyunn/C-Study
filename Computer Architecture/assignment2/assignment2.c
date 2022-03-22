#include <stdio.h>

unsigned int invertEndian(unsigned int inputValue) {
	unsigned char bytes[4];
	int result;

	bytes[0] = (unsigned char)((inputValue >> 24) & 0xff);
	bytes[1] = (unsigned char)((inputValue >> 16) & 0xff);
	bytes[2] = (unsigned char)((inputValue >> 8) & 0xff);
	bytes[3] = (unsigned char)((inputValue >> 0) & 0xff);

	//little-endian으로 변환하여 result에 저장
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

	int count = 0; //초기값 result 저장용 체크 변수
	int check; //읽어오기 위한 임의 변수
	unsigned int inputContent; //가져온 big-endian값
	unsigned int outputContent; //변경한 little-endian값
	unsigned int result = NULL; // 19개의 데이터의 xor한 값(hexa출력용)


	//각각의 파일 오픈하여 파일포인터에 저장
	fopen_s(&outputFile, "output.bin", "wb");
	fopen_s(&inputFile, "input.bin", "rb");

	//big-endian파일에서 데이터 읽어오기
	while (1) {
		check = fread(&inputContent, sizeof(inputContent), 1, inputFile);

		//읽어오기 탈출조건
		if (check != 1)
			break;

		//little-endian으로 변환
		outputContent = invertEndian(inputContent);

		//little-endian 저장
		fwrite(&outputContent, sizeof(outputContent), 1, outputFile);


		//테스트용
		//printf("big-endian: %8x\n", inputContent);
		//printf("little-endian: %8x\n", outputContent);
		//printf("n-th Loop: %d\n", count + 1);


		//xor값 누적 저장
		if (count == 0) //처음인 경우 result 초기값 지정
			result = outputContent;

		else
			result = result ^ outputContent;

		//정상적인 연산 1회 끝냈으므로 count++처리
		count++;
	}

	printf("데이터 XOR결과 : %8x\n", result);

	fclose(outputFile);
	fclose(inputFile);

}