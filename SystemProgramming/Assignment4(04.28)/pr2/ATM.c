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
    //사용할 변수 선언
    struct record current;
    //record_no: 현재 계좌번호, destination_record_no: 송금받을 계좌번호
    int record_no, destination_record_no;
    int fd, pos, i, n;
    char yes;
    char operation;
    int amount;
    char buffer[100];
    int quit = FALSE;

    //거래기록
    fd = open("./account", O_RDWR | O_CREAT, S_IRUSR | S_IWUSR);

    //메인 프로그램
    while(1){
        //조회할 계좌입력
    	printf("enter account number (0-99):");
	    scanf("%d", &record_no);
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
                //lock권한 받기
                reclock(fd, record_no, sizeof(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);
                lseek(fd, pos, SEEK_SET);

                //id 입력받기
                printf("> id ? ");
                scanf("%d", &current.id); 

                //이름 입력받기
                printf("> name ? ");
                scanf("%s", current.name);

                //잔고 0으로 초기화
                current.balance = 0;

                //계좌 개설
                n = write(fd, &current, sizeof(struct record));

                //계좌 정보 출력
                display_record(&current);

                //lock 권한 반납
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;
            
            //계좌 읽어오기
            case 'r':
                //lock권한 받기
                reclock(fd, record_no, sizeof(struct record), F_RDLCK);
                pos = record_no * sizeof(struct  record);
                lseek(fd, pos, SEEK_SET);

                //계좌 정보 반환
                n = read(fd, &current, sizeof(struct record));

                //계좌 정보 출력
                display_record(&current);

                //lock 권한 반납
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;
            
            //계좌에 입금
            case 'd':
                //lock권한 받기
                reclock(fd, record_no, sizeof(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);
                lseek(fd, pos, SEEK_SET);

                //계좌 정보 반환
                n = read(fd, &current, sizeof(struct record));

                //계좌 정보 출력
                display_record(&current);

                //입금할 금액 입력
                printf("enter amount\n");
                scanf("%d", &amount);

                //계좌 잔고에 입금 금액 반영
                current.balance += amount;

                //계좌 정보 저장
                lseek(fd, pos, SEEK_SET);
                write(fd, &current, sizeof(struct record));

                //lock 권한 반납
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;

            //계좌에서 인출
            case 'w':
                //lock권한 받기
                reclock(fd, record_no, sizeof(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);
                lseek(fd, pos, SEEK_SET);

                //계좌 정보 반환
                n = read(fd, &current, sizeof(struct record));

                //계좌 정보 출력
                display_record(&current);

                //인출할 금액 입력
                printf("enter amount\n");
                scanf("%d", &amount);

                //계좌 잔고에 인출 금액 반영
                current.balance -= amount;

                //계좌 정보 저장
                lseek(fd, pos, SEEK_SET);
                write(fd, &current, sizeof(struct record));

                //lock 권한 반납
                reclock(fd, record_no, sizeof(struct record), F_UNLCK);
                break;


            //타 계좌로 송금
            case 't':
            	
		        //송금받을 계좌 번호 입력
	    	    printf("enter destination account number (0-99):");
		        scanf("%d", &destination_record_no);
            
                //인출할 계좌 선택 후 인출금액만큼 차감
                reclock(fd, record_no, sizeof(struct record), F_WRLCK);
                pos = record_no * sizeof(struct record);
                lseek(fd, pos, SEEK_SET);
                
                //인출할 계좌 불러오기
                n = read(fd, &current, sizeof(struct record));

                //계좌 정보 출력
                display_record(&current);

                //인출 후 송금할 금액 입력
                printf("enter transfer amount\n");
                scanf("%d", &amount);

                current.balance -= amount;

                //계좌 정보 저장
                lseek(fd, pos, SEEK_SET);
                write(fd, &current, sizeof(struct record));

                //송금받을 계좌 선택 후 송금받은 금액만큼 추가
                reclock(fd, destination_record_no, sizeof(struct record), F_WRLCK);
                pos = destination_record_no * sizeof(struct record);
                lseek(fd, pos, SEEK_SET);

                //송금받을 계좌 불러오기
                n = read(fd, &current, sizeof(struct record));

                //계좌 정보 출력
                display_record(&current);

                current.balance += amount;

                //계좌정보 저장
                lseek(fd, pos, SEEK_SET);
                write(fd, &current, sizeof(struct record));        
                
                //lock권한 반납
                reclock(fd, destination_record_no, sizeof(struct record), F_UNLCK);
                break;

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
