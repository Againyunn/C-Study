#include <stdio.h>
#define _CRT_SECURE_NO_WARNINGS

unsigned int PC, IR;
char command1;
char* command2;


void main() {


    while (1) {
        //������ �Է¹��� ��ɾ� �ʱ�ȭ
        command1, command2 = NULL;

        //Get command line;
        printf("��ɾ �Է��ϼ���.\n");
        scanf("%c %s", &command1, command2);

        if (command1 == 'l'){
            //�Է¹��� ���ڿ� �ؼ� �� ���� �̸� ����

            //���� ��� FD ����

            //���α׷�&������ �޸� ���� ����

            //PC&SP �ʱⰪ ����

            //load program; break;
        }

        if (command1 == 'j') {
            //�Է¹��� ���ڿ� �ؼ� �� �ּ� �� ����

            //PC�� �ش� �ּ� ������ ����

        }

        if (command1 == 'g') {
            //���� PC��ġ �޾ƿ���

            //��ɾ ������ ó��

            //syscall 10 ��ɾ ������ if�� Ż��
            continue;

        }

        if (command1 == 's') {
            //���� PC��ġ �޾ƿ���

            //���� ��ɾ� 1���� ó��

            //��ɾ ���� ����� register, memory�� �޾Ƽ� ���

        }


        if (command1 == 'm') {
            //�Է¹��� ��ɾ� �ؼ� �� start�� end �� ����

            //memory�Լ� ����
                
            //��� �� ���
        }

        if (command1 == 'r') {
            //register�Լ� ����

            //��� �� ���

        }

        //exit program;
        if (command1 == 'x') {
            /*������ ���� �ؾ��ϳ� ?*/
            return 0;
        }

        if (command1 == 'sr') {
            //�Է¹��� ��ɾ� �ؼ� �� register number�� value �� ����

            //register�Լ� ����

            //��� �� ���
        }

        if (command1 == 'sm') {
            //�Է¹��� ��ɾ� �ؼ� �� location�� value �� ����

            //memory�Լ� ����

            //��� �� ���
        }
    }
}
