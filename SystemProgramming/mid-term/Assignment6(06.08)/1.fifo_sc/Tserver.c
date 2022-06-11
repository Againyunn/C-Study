#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#define SIZE 128
#define FIFO1 "fifo1"
#define FIFO2 "fifo2"


//main함수
int main(int argc, char *argv[]){
 int fd1, fd2;
    char buffer_w[SIZE], buffer_r[SIZE];
    // char inputData[SIZE];
    int  fd1_size, fd2_size;
    
    if(mkfifo(FIFO1, 0666) == -1){
        perror("mkfifo failed");
        exit(1);
    }
    
    if(mkfifo(FIFO2, 0666) == -1){
        perror("mkfifo failed");
        exit(1);
    }
    
      if((fd1 = open(FIFO1, O_RDWR)) == -1){
            perror("open failed");
            exit(1);
        }
    
    
      if((fd2 = open(FIFO2, O_WRONLY)) == -1){
            perror("open failed");
            exit(1);
        }

    while(1){
        //FIFO1생성: client의 전송 메시지 읽기

       
        //FIFO1의 client의 값 받아오기
        //fd1_size = read(fd1, buffer_r, SIZE);
        
        if((fd1_size = read(fd1, buffer_r, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }
	
	//if(fd1_size > 0){
	
        // if(!strcmp(buffer_r, "quit")){
        //     printf("Quit chatting\n");
        //     exit(0);
        // }
		printf("[CLIENT]%s\n", buffer_r);

		if(write(fd1, NULL, SIZE) == -1){
		    perror("clear failed");
		    exit(1);
		}
		
		//close(fd1);
	//}

        //FIFO2생성: server의 메시지를 client에서 전송
      

        //FIFO2에 server의 값 입력
        //fd2_size = read(fd2, buffer_w, SIZE);
	if((fd2_size = read(fd2, buffer_w, SIZE)) == -1){
            perror("read failed");
            exit(1);
        }


        printf("[SERVER]");
        fgets(buffer_w, SIZE, stdin);
        if(write(fd2, buffer_w, SIZE) == -1){
            perror("write failed");
            exit(1);
        }

        if(!strcmp(buffer_w, "quit")){
            printf("Quit chatting\n");
            exit(0);
        }
        
        //close(fd2);

    }


}

