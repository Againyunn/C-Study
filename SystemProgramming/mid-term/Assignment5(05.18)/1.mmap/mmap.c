#include <sys/mman.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <fcntl.h>

#define FILE_MODE (S_IRUSR | S_IWUSR)

void mperr(char *call, int val){
    perror(call);
    exit(val);
}

int main(int argc, char *argv[]){
    int fdin, fdout; //file descriptor 생성
    caddr_t src, dst;   //각각의 mmap()결과로 생성된 메모리의 주소를 담을 변수
    struct stat statbuf;    //file의 stat정보를 담을 변수

    if(argc != 3)
        mperr("usage : a.out <fromfile> <tofile>", 1);
        
    //source file의 fd생성
    if((fdin = open(argv[1], O_RDONLY)) < 0){
        fprintf(stderr, "cannot open %s for writing", argv[1]);
        exit(2);
    }

    //destination file의 fd생성
    if((fdout = open(argv[2], O_RDWR | O_CREAT | O_TRUNC, FILE_MODE)) < 0){
        fprintf(stderr, "cannot open %s for writing", argv[2]);
        exit(3);  
    }

    //source file의 fd에서 읽어올 stat정보가 없으면 에러 반환
    if(fstat(fdin, &statbuf) < 0)
        mperr("fstat error", 4);

    //statbuf에서 읽어올 데이터가 없으면 에러 반환
    if(lseek(fdout, statbuf.st_size - 1, SEEK_SET) == -1)
        mperr("lseek error", 5);

    //destination dile의 fd에 저장하지 못하면 에러 반환
    if(write(fdout, "", 1) != 1)
        mperr("write error", 6);

    //src에 statbuf의 크기만큼 fdin를 읽기전용, 즉시 동기화로 설정하여 메모리에 할당(fdin의 처음부터 statbuf.st_size까지 읽는 메모리로 지정)
    if((src = mmap(0, statbuf.st_size, PROT_READ, MAP_SHARED, fdin, 0)) == MAP_FAILED)
        mperr("mmap error for input", 7);

    //dst에 statbuf의 크기만큼 fout를 쓰기 전용, 즉시 동기화로 설정하여 메모리에 할당(fdout의 처음부터 statbuf.st_size까지 읽는 메모리로 지정)
    if((dst = mmap(0, statbuf.st_size, PROT_WRITE, MAP_SHARED, fdout, 0)) == MAP_FAILED)
        mperr("mmap error for output", 8);

    //src에서 statbuf.st_size만큼 dst로 메모리copy(kernel level에서 작업 발생)
    memcpy(dst, src, statbuf.st_size);

    //할당된 src 공간 해제
    if(munmap(src, statbuf.st_size) != 0)
        mperr("munmap(src) error", 9);
    
    //할당된 dst 공간 해제
    if(munmap(dst, statbuf.st_size) != 0)
        mperr("munmap(src) error", 10);
    
    exit(0);
}