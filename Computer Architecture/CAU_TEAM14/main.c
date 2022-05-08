#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

unsigned int PC, IR;
char command1;
char* command2;


void main() {


    while (1) {
        //기존에 입력받은 명령어 초기화
        command1, command2 = NULL;

        //Get command line;
        printf("명령어를 입력하세요.\n");
        scanf("%c %s", &command1, command2);

        if (command1 == 'l'){
            //입력받은 문자열 해석 후 파일 이름 추출

            //파일 열어서 FD 저장

            //프로그램&데이터 메모리 번지 설정

            //PC&SP 초기값 설정

            //load program; break;
        }

        if (command1 == 'j') {
            //입력받은 문자열 해석 후 주소 값 추출

            //PC를 해당 주소 값으로 변경

        }

        if (command1 == 'g') {
            //현재 PC위치 받아오기

            //명령어를 끝까지 처리

            //syscall 10 명령어를 만나면 if문 탈출
            continue;

        }

        if (command1 == 's') {
            //현재 PC위치 받아오기

            //현재 명령어 1개만 처리

            //명령어에 의해 변경된 register, memory값 받아서 출력

        }


        if (command1 == 'm') {
            //입력받은 명령어 해석 후 start와 end 값 저장

            //memory함수 접근
                
            //결과 값 출력
        }

        if (command1 == 'r') {
            //register함수 접근

            //결과 값 출력

        }

        //exit program;
        if (command1 == 'x') {
            /*저장을 따로 해야하나 ?*/
            return 0;
        }

        if (command1 == 'sr') {
            //입력받은 명령어 해석 후 register number와 value 값 저장

            //register함수 실행

            //결과 값 출력
        }

        if (command1 == 'sm') {
            //입력받은 명령어 해석 후 location와 value 값 저장

            //memory함수 실행

            //결과 값 출력
        }
    }
}
