#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TMPFILE "/tmp/mylog"


int main(void){
	FILE *fp;
	
	//TMPFILE을 append모드로 열어 filedescripter fp에 저장
	if (( fp = fopen( TMPFILE, "a+" )) == NULL ) {
		perror("fopen error");
		exit(2);
	}
	
	//fp에 문자열과 pid를 입력
	fprintf(fp, "This is temporary log entry of pid %d\n", getpid() );
	
	//fp를 닫고, 메인 프로그램 종료
	fclose(fp);
	
	
	exit(0);
}


