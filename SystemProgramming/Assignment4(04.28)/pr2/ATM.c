#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

//TRUE, FALSE로 직접 사용하기 위한 방법
#define TRUE    1
#define FALSE   0

#define NUM_RECORDS 100

struct record{
    char name[20];
    int id;
    int balance;
};

int reclock(int fd, int recno, int len, int type);
void display_record(struct record *curr);

int main(){
    struct record current;
    int record_no;
    int fd, pos, i, n;
    char yes;
    char operation;
    int amount;
    char buffer[100];
    int quit = FALSE;

    fd = open("./account", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);
    while(1){
        printf("%d", &record_no);
        fgets(buffer, 100, stdin);

        //선택가능한 범위를 벗어난 경우
        if(record_no < 0 && record_no >= NUM_RECORDS)
            break;

        //명령어 입력받기
        printf("enter operation name (c/r/d/w/t/q): ");
        scanf("%c", &operation);

        switch(operation){
            //계좌 생성
            case 'c': 
                reclock(fd, record_no, size_of(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);
                lseek(fd, pos, SEEK_SET);

                //id 입력받기
                printf("> id ? ");
                scanf("%d", &current.id); 

                //이름 입력받기
                printf("> name ? ");
                scanf("%s", current.name);

                //계좌 개설
                current.balance = 0;

                n = write(fd, &current, sizeof(struct record));

                display_record(&current);
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;
            
            //계좌 읽어오기
            case 'r':
                reclock(fd, record_no, sizeof(struct record), F_RDLCK);
                pos = record_no * sizeof(struct  record);
                lseek(fd, pos, SEEK_SET);
                n = read(fd, &current, sizeof(struct record));
                display_record(&current);

                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;
            
            //계좌에 입금
            case 'd':
                reclock(fd, record_no, sizeof(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);

                lseek(fd, pos, SEEK_SET);

                n = read(fd, &current, sizeof(struct record));
                display_record(&current);

                printf("enter amount\n");
                scanf("%d", &amount);

                current.balance += amount;

                lseek(fd, pos, SEEK_SET);
                write(fd, &current, sizeof(struct record));
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;

            //계좌에서 인출
            case 'w':
                reclock(fd, record_no, sizeof(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);

                lseek(fd, pos, SEEK_SET);

                n = read(fd, &current, sizeof(struct record));
                display_record(&current);

                printf("enter amount\n");
                scanf("%d", &amount);

                current.balance -= amount;

                lseek(fd, pos, SEEK_SET);
                write(fd, &current, sizeof(struct record));
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;


            //타 계좌로 송금
            //case 't':




            //종료
            case 'q':
                quit = TRUE;
                break;

            //기본값(불일치하는 명령어)
            default:
                printf("illegal input\n");
                continue;
        }
    }
    close(fd);
    fflush(NULL);
}

int reclock(int fd, int recno, int len, int type){
    struct flock fl;

    switch(type){
        case F_RDLCK:
        case F_WRLCK:
        case F_UNLCK:
            fl.l_type = type;
            fl.l_whence = SEEK_SET;
            fl.l_start = recno * len;
            fl.l_len = len;
            fcntl(fd, F_SETLKW, &fl);
            return 1;

        default:
            return -1;
    }   
}

void display_record(struct record *curr){
    printf("\n");
    printf("id: %d \n", curr -> id);
    printf("name: %s \n", curr -> name);
    printf("balance: %d \n", curr -> balance);
    printf("\n");
}