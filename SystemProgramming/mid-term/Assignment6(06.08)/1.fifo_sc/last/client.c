#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *read_server(void*);
int fd_lock(int fd);
int fd_open(int fd);
int fd_isopen(int fd);

#define SIZE 128
#define FIFO1 "fifo1"//client -> server
#define FIFO2 "fifo2"//server -> client


//main함수
int main(int argc, char *argv[]){
	int fd1;
	char buffer_w[SIZE];
	int  fd1_size;


	//printf("pid: %d",getpid());

	//thread관련
	pthread_t read_fifo2;

	pthread_create(&read_fifo2, NULL, read_server, NULL);

	while(1){


		//buffer_w[0] = 'b';
		//써서 FIFO1에 입력하기(CLIENT -> SERVER)
		while(1){
			if((fd1 = open(FIFO1, O_RDWR)) == -1){
				perror("open failed");
				exit(1);
			}  
			
			if (fd_isopen(fd1) == -1)
			{
				
				perror("file1 is lock ");
				break; 
				//exit(0);
			}
			//FIFO1에 client의 값 입력
			//fd1_size = read(fd1, buffer_w, SIZE);
			if((fd1_size = read(fd1, buffer_w, SIZE)) == -1){
				
			    	perror("read1 failed");
			    	close(fd1);
			    	break;
			    //exit(1);
			}

			printf("[CLIENT]");
			fgets(buffer_w, SIZE, stdin);

			if(write(fd1, buffer_w, SIZE) == -1){
			    perror("write failed");
			    exit(0);
			}

			if(!strcmp(buffer_w, "quit")){
			    printf("Quit chatting\n");
			    exit(0);
			}
			if (fd_unlock(fd1) == -1)
			{
				perror("file1 unlock error ");
			}
			unlink("./fifo1");
			close(fd1);
			break;
		}
	    
		pthread_join(read_fifo2, NULL);
        }
}


void *read_server(void *v){
    int fd2;
    char buffer_r[SIZE];
    int  fd2_size;
    

    while(1){
		if((fd2 = open(FIFO2, O_RDONLY)) == -1){
			perror("open failed");
			exit(1);
		}
		if (fd_isopen(fd2) == -1)
		{
			
			perror("file2 is lock "); 
			break;
			//exit(0);
		}
		if((fd2_size = read(fd2, buffer_r, SIZE)) == -1){
			perror("read2 failed");
			break;
			//exit(1);
		}

		printf("[SERVER] %s\n", buffer_r);
		if (fd_unlock(fd2) == -1)
		{
			perror("file2 unlock error ");
		}
		unlink("./fifo2");
		close(fd2);
	    /*if(write(fd2, NULL, SIZE) == -1){
		perror("clear failed");
		exit(1);
	    }*/
		break;
	}

}

// 파일이 잠겨있는지 확인하고 잠겨 있지 않으면
// 잠금을 얻고 
// 잠겨 있을경우 잠김이 풀릴때까지 기다린다(F_SETLKW) 
int fd_isopen(int fd)
{
    struct flock lock;

    lock.l_type = F_WRLCK; 
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    return fcntl(fd, F_SETLKW, &lock);
}

// 파일 잠금을 얻은후 모든 작업이 끝난다면 
// 파일 잠금을 돌려준다. 
int fd_unlock(int fd)
{
    struct flock lock;

    lock.l_type = F_UNLCK; 
    lock.l_start = 0;
    lock.l_whence = SEEK_SET;
    lock.l_len = 0;

    return fcntl(fd, F_SETLK, &lock);
}
