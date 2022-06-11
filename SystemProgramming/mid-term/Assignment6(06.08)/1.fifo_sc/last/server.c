#include <stdio.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>

void *read_client(void*);
int fd_lock(int fd);
int fd_open(int fd);
int fd_isopen(int fd);

#define SIZE 128
#define FIFO1 "./fifo1"//client -> server
#define FIFO2 "./fifo2"//server -> client


//main함수
int main(int argc, char *argv[]){
	int fd2;
	char buffer_w[SIZE];
	// char inputData[SIZE];
	int fd2_size;

	//printf("pid: %d",getpid());

	//thread관련
	pthread_t read_fifo1;

	if(mkfifo(FIFO1, 0666) == -1){
	perror("mkfifo failed");
	exit(1);
	}


	if(mkfifo(FIFO2, 0666) == -1){
	perror("mkfifo failed");
	exit(1);
	}

	pthread_create(&read_fifo1, NULL, read_client, NULL);

	while(1){
	    //buffer_w[0] = 'a';
	    //fputs("ready", stdout);


	    //printf("file open");
	    //써서 FIFO2에 입력하기(SERVER -> CLIENT)
	    while(1){
		if((fd2 = open(FIFO2, O_RDWR)) == -1){
			perror("open failed");
			exit(1);
		}
	    
		if (fd_isopen(fd2) == -1)
		{
			perror("file2 is lock "); 
			break;
			//exit(0);
		}
		fd2_size = read(fd2, buffer_w, SIZE);
		//printf("file read");
		if(fd2_size == -1){
			perror("read2 failed");
			close(fd2);
			break;
			//exit(1);
		}
		
		//printf("read: %d",fd2_size);
		
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
		if (fd_unlock(fd2) == -1)
		{
			perror("file2 unlock error ");
		}
		unlink("./fifo2");
		close(fd2);
		break;
	    } 
	    
	    pthread_join(read_fifo1, NULL);
    }
}

void *read_client(void *v){
	int fd1;
	char buffer_r[SIZE];
	int  fd1_size;



	while(1){
		if((fd1 = open(FIFO1, O_RDONLY)) == -1){
			perror("open failed");
			exit(1);
		}
		if (fd_isopen(fd1) == -1)
		{
			break;
			//perror("file1 is lock "); 
			//exit(0);
		}
		if((fd1_size = read(fd1, buffer_r, SIZE)) == -1){
			perror("read1 failed");
			break;
			//exit(1);
		}

		printf("[CLIENT]%s\n", buffer_r);
		if (fd_unlock(fd1) == -1)
		{
			perror("file1 unlock error ");
		}
		unlink("./fifo1");
		close(fd1);
	    /*if(write(fd1, NULL, SIZE) == -1){
		perror("clear failed");
		exit(1);
	    }*/
	//	break;
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






