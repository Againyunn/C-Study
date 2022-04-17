#include <stdio.h>
#include <string.h>


unsigned char progMEM[0x100000], dataMEM[0x100000], stakMEM[0x100000];

int indexProgMEM, indexDataMEM, indexStakMEM = 0;


int MEM(unsigned int A, char* V, int nRW, int S) {
    unsigned int sel, offset;
    unsigned char* pM;
    sel = A; //>> 20;
    offset = A & 0xFFFFF;

    pM = "";

    ////테스트용
    //printf("sel: %d\n", sel);
    //printf("offsest: %d\n", offset);

    // address decoding and select a physical memory
    if (sel == 0x004)
        pM = progMEM;  // program memory
    else if (sel == 0x100)
        pM = dataMEM;  // data memory
    else if (sel == 0x7FF)
        pM = stakMEM;  // stack
    else {
        printf("Empty memory\n");
        //exit(1);
    }

    //V값을 문자열 포인터로 변경
    //char* temp = "HI";
    ////V = (char)V;
    //memcpy(temp, V, strlen(V));
    //printf("%s", temp);

    // offset processing for alignment
    if (S == 0) {  // byte : 텍스트  A사용
        //각 문자 하나씩 pM에 앞-> 뒤 index순서로 저장
        for (int i = 0; i < strlen(V); i++) {
            pM[i] = V[i];

            printf(V[i]);
        }
    }

    else if (S == 1) { // half word   A & 0xfffffffe

        //반워드 offset 구하기
        offset = A & 0xfffffffe;

        if (nRW == 0) { // read     : V값 무시, data반환
            
            //pM에 저장된 모든 데이터 반환
            for (int i = 0; i < strlen(pM); i++) {
                printf("%c", pM[i]);
            }
            printf("\n");

        }
        else if (nRW == 1) { // write     : V값을 주소에 저장, return 무시

            //V값을 주소에 저장
            for (int i = 0; i < strlen(V); i++) {
                pM[offset + i] = V[i];
            }
        }
    }

    else if (S == 2) { // word   A & 0xfffffffc
        //워드 offset 구하기
        offset = A & 0xfffffffc;

        //V값을 주소에 저장
        for (int i = 0; i < strlen(V); i++) {
            pM[offset + i] = V[i];
        }

    }

    else {// error
        printf("It's wrong command. Please check the command\n");

    } 
    
    //return 0;
}

int main(){
    //쓰기
    printf("V: 10, nRW: 1, S: 0\n");
    MEM(4, "10", 1, 0);

    //읽기
    printf("V: 10, nRW: 0, S: 0\n");
    MEM(4, "10", 0, 1);



};