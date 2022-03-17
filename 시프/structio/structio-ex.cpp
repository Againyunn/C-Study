#include <stdio.h>


//재확인 필요
int main() {
	
	struct {
		short count;
		char sample;
		long total;
		float numeric[LENGTH];
	}object;

	FILE *stream;

	if (fwrite(&object, sizeof(object), 1, stream) != 1) {	//open할 객체, 객체의 크기, 객체의 개수, 저장할 포인터
		perror("fwrite error");
	}
	


};