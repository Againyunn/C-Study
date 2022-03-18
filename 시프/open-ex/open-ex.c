#define _CRT_SECURE_NO_WARNINGS
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/stat.h>

int main(int argc, char* argv[]) {
	FILE *fpo;
	int fdo;

	if (argc != 2) {
		perror(argv[0]);
		return 1;
	}

	if ((fdo = open(argv[1], O_RDWR | O_CREAT | O_TRUNC)) == -1) { //S_IRUSR | S_IWUSR 사용 시 에러 발생
		perror(argv[1]);
		return 1;
	}

	if ((fpo = fdopen(fdo, "r+")) == NULL) {
		perror("fdopen");
		return 2;
	}


	fprintf(fpo, "Hello, world! \n");
	fclose(fpo);

}