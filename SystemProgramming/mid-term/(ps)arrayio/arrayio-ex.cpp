#define _CRT_SECURE_NO_WARNINGS
#define ARRAY_SIZE 10

#include <stdio.h>

int main(int argc, char* argv[]) {
	int i;
	int sample_array[ARRAY_SIZE]; //배열에 임의 값이 저장되어 있다고 가정
	FILE* stream; //사용자에게 입력받은 파일의 pointer

	if (argc != 3) {
		perror(argv[0]);
		exit(1);
	}

	//stream pointer를 입력받은 파일로 지정
	if ((stream = fopen(argv[1], "w")) == NULL) {
		perror(argv[1]);
		return 1;
	}

	//sample_array에 위치한 값 그대로 라는 stream pointer에 저장
	if (fwrite(sample_array, sizeof(int), ARRAY_SIZE, stream) != ARRAY_SIZE) {
		perror("fwrite error");
		return 2;
	}

}

