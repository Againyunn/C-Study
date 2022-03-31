#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TMPFILE "/tmp/mylog"

//exit handler function
static void myexit(void);

int main(void){
	FILE *fp;
	
	//프로그램 종료 시 실행할 함수 지정 → myexit함수 실행
	if( atexit( myexit ) != 0) {
		perror("atexit error");
		exit(1);
	}
	
	//TMPFILE을 append모드로 열어 filedescripter fp에 저장
	if (( fp = fopen( TMPFILE, "a+" )) == NULL ) {
		perror("fopen error");
		exit(2);
	}
	
	//fp에 문자열과 pid를 입력
	fprintf(fp, "This is temporary log entry of pid %d\n", getpid() );
	
	//fp를 닫고, 메인 프로그램 종료
	fclose(fp);
	
	//파일 확인을 위해 20초 대기
	sleep(20);
	exit(0);
}

//프로그램 종료 시 실행할 함수 정의
static void myexit(void){
	
	//TMPFILE 삭제하기
	if( unlink(TMPFILE) ){
		perror("myexit : unlink");
		exit(3);
	}
}

