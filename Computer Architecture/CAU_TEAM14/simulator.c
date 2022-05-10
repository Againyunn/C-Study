#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdio>

/*제어용 전역변수*/
unsigned int PC, IR;
FILE* pFile;


/*메인에 사용될 함수 선언*/
void printNotice();
int checkArgument1(int lenCode, char type);
int checkArgument2(int lenCode, char type);
int checkArgument3(int lenCode, int type);

int main(){
    //시뮬레이터 변수 설정
    char cmdLine[50];
    int lenCode;
    int cmdLen;
    int cmdErr;

    //레지스터 초기화 함수


    while(1){
        //COMAND 변수 초기화
        lenCode = 0; //명령어의 인자 수
        cmdLen = 0; //명령어의 자리수(1~2자리 식별용)
        cmdErr = 0;
        char *cmdArr[10] = {NULL, };
        

        //시뮬레이터 사용법 출력
        printNotice();

    /*명령입력받기*/
        printf("명령어를 입력하세요.\n>>> ");
        gets(cmdLine);

        char* ptr = strtok(cmdLine, " ");

        while (ptr != NULL)            // 자른 문자열이 나오지 않을 때까지 반복
        {
            cmdArr[lenCode] = ptr;      // 문자열을 자른 뒤 메모리 주소를 문자열 포인터 배열에 저장
            lenCode++;                       

            ptr = strtok(NULL, " ");   // 다음 문자열을 잘라서 포인터를 반환
        }

        if(cmdArr[0] != NULL){
            cmdLen = strlen(cmdArr[0]);
        }

    /*어떤 명령어인지 식별*/
        if(cmdLen == 1){ //명령어가 한글자일 때

            switch (*cmdArr[0])
            {
        /*l 명령어*/
            case 'l':
                if(checkArgument2(lenCode, 'l') == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

                break;
        /*j 명령어*/
            case 'j':
                if(checkArgument2(lenCode, 'j') == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

                break;
        
        /*g 명령어*/
            case 'g':
                if(checkArgument1(lenCode, 'g') == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

                break;

        /*s 명령어*/    
            case 's':
                if(checkArgument1(lenCode, 's') == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

                break;

        /*m 명령어*/
            case 'm':
                if(checkArgument3(lenCode, 1) == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

                break;

        /*r 명령어*/
            case 'r':
                if(checkArgument1(lenCode, 'r') == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

                break;

        /*x 명령어*/
            case 'x':
                printf("프로그램을 종료합니다.\n");
                exit(1);
                break;

            default:
                printf("Error: 명령어를 다시 입력해주세요.\n");
                break;
            }

        }
        

        else if(cmdLen == 2){ //명령어가 두글자일 때

        /*sr 명령어*/
            if(!strcmp(cmdArr[0], "sr")){
                if(checkArgument3(lenCode, 2) == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

            }

        /*sm 명령어*/
            else if(!strcmp(cmdArr[0], "sm")){
                if(checkArgument3(lenCode, 3) == 1) //명령어 유효성검사
                    break;
                
                //함수삽입

            }

            else{
                printf("Error: 명령어를 다시 입력해주세요.\n");
            }

        }

        else{
            printf("Error: 명령어를 다시 입력해주세요.\n");
        }
        
    }



}


//시뮬레이터 사용법 출력함수
void printNotice(){
    printf("\t\t\t*명령어 입력형식*\n");
    printf("l 실행파일이름\t\t\t:실행파일이 시뮬레이터 메모리에 올라갑니다.\n");
    printf("j 프로그램 시작 위치 \t\t:입력한 위치에 시뮬레이터 실행을 준비합니다.\n");
    printf("g\t\t\t\t:현재pc위치에서 시뮬레이터가 명령어를 끝까지 처리합니다.\n");
    printf("s\t\t\t\t:명령어 하나를 처리하고 사용자 명령을 밭는 상태로 중지합니다.\n");
    printf("m start end\t\t\t:start~end범위의 메모리 내용을 출력합니다.\n");
    printf("r\t\t\t\t:현재 레지스터의 내용을 출력합니다.\n");
    printf("x\t\t\t\t:시뮬레이터 프로그램을 종료합니다.\n");
    printf("sr register number value\t:특정 레지스터의 값을 설정합니다.\n");
    printf("sm location value\t\t:메모리 특정 주소의 값을 설정합니다.\n");
    printf("---------------------------------------------------------------------------------------------\n");
}

//올바르지 않은 인자 확인 함수
int checkArgument1(int lenCode, char type){
    int result = 0;

    if(lenCode >= 2){
        printf("Error: 명령어의 형식을 지켜주세요.\n");

        switch (type)
        {
        case 'j':
            printf("\tex) j");
            result = 1;
            break;

        case 'g':
            printf("\tex) g");
            result = 1;
            break;

        case 's':
            printf("\tex) s");
            result = 1;
            break;

        case 'r':
            printf("\tex) r");
            result = 1;
            break;

        default:
            break;
        }
    }

    return result;
}

int checkArgument2(int lenCode, char type){
    int result = 0;

    if(lenCode >= 3){
        printf("Error: 명령어의 형식을 지켜주세요.\n");
        
        switch (type)
        {
        case 'l':
            printf("\tex) l 실행파일의경로와이름");
            result = 1;
            break;

        case 'j':
            printf("\tex) j 프로그램시작위치");
            result = 1;
            break;

        default:
            break;
        }
    }

    return result;
}

int checkArgument3(int lenCode, int type){
    int result = 0;

    if(lenCode >= 4){
        printf("Error: 명령어의 형식을 지켜주세요.\n");


        switch (type)
        {
    /*m 명령어*/
        case 1:
            printf("\tex) m 시작주소 종료주소\n");
            result = 1;
            break;

    /*sr 명령어*/
        case 2:
            printf("\tex) sr 레지스터번호 지정할값\n");
            result = 1;
            break;  

    /*sm 명령어*/
        case 3:
            printf("\tex) sm 메모리주소 지정할값\n");
            result = 1;
            break;                  
        default:
            break;
        }

        // if(!strcmp(type, "m")){
        //     printf("\tex) m 시작주소 종료주소\n");
        //     result = 1;
        // }

        // else if(!strcmp(type, "sr")){
        //     printf("\tex) sr 레지스터번호 지정할값\n");
        //     result = 1;
        // }

        // else if(!strcmp(type, "sm")){
        //     printf("\tex) sm 메모리주소 지정할값\n");
        //     result = 1;
        // }
    }

    return result;
}