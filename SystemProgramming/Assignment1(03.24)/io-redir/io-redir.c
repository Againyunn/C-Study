#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

int main()
{
	int backup_des, stdout_des, ofdes;
	
	//stdout의 descripter값을 stdout_des에 저장 후, backup_des에 복제
	stdout_des = fileno(stdout);
	backup_des = dup(stdout_des);
	
	//일반적인 stdout의 file descripter에 출력
	printf("Hello, world! (1)\n");
	
	//test.txt를 ofdes에 저장
	ofdes = open("test.txt", O_WRONLY|O_CREAT|O_TRUNC, S_IRUSR|S_IWUSR);
	
	//ofdes의 descripter값을 stdout_des(stdout의 file descripter)로 저장
	dup2(ofdes,stdout_des);
	//ofdes(test.txt파일의 discripter)로 변경된 stdout의 file descripter에 출력(test.tx에 입력)
	printf("Hello, world! (2)\n");
	
	//backup_des(백업해둔 원래 stdout의 descripter값)의 descripter값을 stdout_des(stdout의 file descripter)로 저장
	dup2(backup_des,stdout_des);
	//원래대로 복구된 stdout의 file descripter에 출력
	printf("Hello, world! (3)\n");
	
	close(ofdes);
}
