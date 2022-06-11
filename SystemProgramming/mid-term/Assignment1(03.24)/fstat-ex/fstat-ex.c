#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[])
{
	struct stat statbuf;
	
	//명령어의 인자 수가 맞지 않으면 에러 반환
	if(argc != 3){
		perror("argument error");
		return 1;
	}
	
	//첫번째 인자 값이 어떤 명령어를 수행하라는 의미인지 파악
	//stat의 경우: 첫번째 인자를 받아서 stat인지 확인
	if(!strcmp(argv[1], "stat")){
		if(stat(argv[2], &statbuf) < 0){
			perror("stat");
			return 2;
		}
	}
	//fstat의 경우: 첫번째 인자를 받아서 fstat인지 확인
	else if(!strcmp(argv[1], "fstat")){
		int filedes = open(argv[2], O_RDWR);//file decripter가 필요하여, 해당 값 받기
		if(fstat(filedes, &statbuf) < 0){
			perror("fstat");
			return 3;
		}
	}
	//lstat의 경우: 첫번째 인자를 받아서 lstat인지 확인
	else if(!strcmp(argv[1], "lstat")){
		if(lstat(argv[2], &statbuf) < 0){
			perror("lstat");
			return 4;
		}
	}
	
	//각각 regular, directory, link 파일인지 식별 후, 입력받은 인자값과 파일의 유형 값 반환
	if(S_ISREG(statbuf.st_mode))
		printf("%s is Reguler File\n", argv[2]);
	if(S_ISDIR(statbuf.st_mode))
		printf("%s is Directory\n", argv[2]);
	if(S_ISLNK(statbuf.st_mode))
		printf("%s is Link File\n", argv[2]);	
	
	return 0;
}
	
