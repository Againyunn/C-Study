#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
//#include <cstdio>

/*����� ��������*/
unsigned int PC, IR;
FILE* pFile;


/*���ο� ���� �Լ� ����*/
void printNotice();
int checkArgument1(int lenCode, char type);
int checkArgument2(int lenCode, char type);
int checkArgument3(int lenCode, int type);

int main(){
    //�ùķ����� ���� ����
    char cmdLine[50];
    int lenCode;
    int cmdLen;
    int cmdErr;

    //�������� �ʱ�ȭ �Լ�


    while(1){
        //COMAND ���� �ʱ�ȭ
        lenCode = 0; //��ɾ��� ���� ��
        cmdLen = 0; //��ɾ��� �ڸ���(1~2�ڸ� �ĺ���)
        cmdErr = 0;
        char *cmdArr[10] = {NULL, };
        

        //�ùķ����� ���� ���
        printNotice();

    /*����Է¹ޱ�*/
        printf("��ɾ �Է��ϼ���.\n>>> ");
        gets(cmdLine);

        char* ptr = strtok(cmdLine, " ");

        while (ptr != NULL)            // �ڸ� ���ڿ��� ������ ���� ������ �ݺ�
        {
            cmdArr[lenCode] = ptr;      // ���ڿ��� �ڸ� �� �޸� �ּҸ� ���ڿ� ������ �迭�� ����
            lenCode++;                       

            ptr = strtok(NULL, " ");   // ���� ���ڿ��� �߶� �����͸� ��ȯ
        }

        if(cmdArr[0] != NULL){
            cmdLen = strlen(cmdArr[0]);
        }

    /*� ��ɾ����� �ĺ�*/
        if(cmdLen == 1){ //��ɾ �ѱ����� ��

            switch (*cmdArr[0])
            {
        /*l ��ɾ�*/
            case 'l':
                if(checkArgument2(lenCode, 'l') == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

                break;
        /*j ��ɾ�*/
            case 'j':
                if(checkArgument2(lenCode, 'j') == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

                break;
        
        /*g ��ɾ�*/
            case 'g':
                if(checkArgument1(lenCode, 'g') == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

                break;

        /*s ��ɾ�*/    
            case 's':
                if(checkArgument1(lenCode, 's') == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

                break;

        /*m ��ɾ�*/
            case 'm':
                if(checkArgument3(lenCode, 1) == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

                break;

        /*r ��ɾ�*/
            case 'r':
                if(checkArgument1(lenCode, 'r') == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

                break;

        /*x ��ɾ�*/
            case 'x':
                printf("���α׷��� �����մϴ�.\n");
                exit(1);
                break;

            default:
                printf("Error: ��ɾ �ٽ� �Է����ּ���.\n");
                break;
            }

        }
        

        else if(cmdLen == 2){ //��ɾ �α����� ��

        /*sr ��ɾ�*/
            if(!strcmp(cmdArr[0], "sr")){
                if(checkArgument3(lenCode, 2) == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

            }

        /*sm ��ɾ�*/
            else if(!strcmp(cmdArr[0], "sm")){
                if(checkArgument3(lenCode, 3) == 1) //��ɾ� ��ȿ���˻�
                    break;
                
                //�Լ�����

            }

            else{
                printf("Error: ��ɾ �ٽ� �Է����ּ���.\n");
            }

        }

        else{
            printf("Error: ��ɾ �ٽ� �Է����ּ���.\n");
        }
        
    }



}


//�ùķ����� ���� ����Լ�
void printNotice(){
    printf("\t\t\t*��ɾ� �Է�����*\n");
    printf("l ���������̸�\t\t\t:���������� �ùķ����� �޸𸮿� �ö󰩴ϴ�.\n");
    printf("j ���α׷� ���� ��ġ \t\t:�Է��� ��ġ�� �ùķ����� ������ �غ��մϴ�.\n");
    printf("g\t\t\t\t:����pc��ġ���� �ùķ����Ͱ� ��ɾ ������ ó���մϴ�.\n");
    printf("s\t\t\t\t:��ɾ� �ϳ��� ó���ϰ� ����� ����� ��� ���·� �����մϴ�.\n");
    printf("m start end\t\t\t:start~end������ �޸� ������ ����մϴ�.\n");
    printf("r\t\t\t\t:���� ���������� ������ ����մϴ�.\n");
    printf("x\t\t\t\t:�ùķ����� ���α׷��� �����մϴ�.\n");
    printf("sr register number value\t:Ư�� ���������� ���� �����մϴ�.\n");
    printf("sm location value\t\t:�޸� Ư�� �ּ��� ���� �����մϴ�.\n");
    printf("---------------------------------------------------------------------------------------------\n");
}

//�ùٸ��� ���� ���� Ȯ�� �Լ�
int checkArgument1(int lenCode, char type){
    int result = 0;

    if(lenCode >= 2){
        printf("Error: ��ɾ��� ������ �����ּ���.\n");

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
        printf("Error: ��ɾ��� ������ �����ּ���.\n");
        
        switch (type)
        {
        case 'l':
            printf("\tex) l ���������ǰ�ο��̸�");
            result = 1;
            break;

        case 'j':
            printf("\tex) j ���α׷�������ġ");
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
        printf("Error: ��ɾ��� ������ �����ּ���.\n");


        switch (type)
        {
    /*m ��ɾ�*/
        case 1:
            printf("\tex) m �����ּ� �����ּ�\n");
            result = 1;
            break;

    /*sr ��ɾ�*/
        case 2:
            printf("\tex) sr �������͹�ȣ �����Ұ�\n");
            result = 1;
            break;  

    /*sm ��ɾ�*/
        case 3:
            printf("\tex) sm �޸��ּ� �����Ұ�\n");
            result = 1;
            break;                  
        default:
            break;
        }

        // if(!strcmp(type, "m")){
        //     printf("\tex) m �����ּ� �����ּ�\n");
        //     result = 1;
        // }

        // else if(!strcmp(type, "sr")){
        //     printf("\tex) sr �������͹�ȣ �����Ұ�\n");
        //     result = 1;
        // }

        // else if(!strcmp(type, "sm")){
        //     printf("\tex) sm �޸��ּ� �����Ұ�\n");
        //     result = 1;
        // }
    }

    return result;
}