#include <stdio.h>


//��Ȯ�� �ʿ�
int main() {
	
	struct {
		short count;
		char sample;
		long total;
		float numeric[LENGTH];
	}object;

	FILE *stream;

	if (fwrite(&object, sizeof(object), 1, stream) != 1) {	//open�� ��ü, ��ü�� ũ��, ��ü�� ����, ������ ������
		perror("fwrite error");
	}
	


};