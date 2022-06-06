#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <argparse/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
#define PORT 30000
#define HOSTADDR "127.0.0.1"


int main(int argc, char *argv[]){
    int sd, send_bytes, n, recv_bytes;
    struct sockaddr_in servaddr;
    char snddata[MAX], rcvdata[MAX];

    bzero ((char*) &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(HOSTADDR);
    servaddr.sin_port = htons(PORT);

    if((sd = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        fprintf(stderr, "can't open socket.\n");
        exit(1);
    }

    if(connect(sd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0){
        fprintf(stderr, "can't connect to server.\n");
        exit(1);
    }

    while(fgets(snddata, MAX, stdin) != NULL){
        send_bytes = strlen(snddata);
        if(sendto(sd, snddata, send_bytes, 0, (struct sockaddr*) &servaddr, sizeof(servaddr)) != send_bytes){
            fprintf(stderr, "can't send data.\n");
            exit(1);
        }

        recv_bytes = 0;

        while(recv_bytes < send_bytes){
            if((n = recvfrom(sd, rcvdata+recv_bytes, MAX, 0, (struct sockaddr*) &servaddr, sizeof(servaddr))) < 0){
                fprintf(stderr, "can't receive data.\n");
                exit(1);
            }

            recv_bytes += n;
        }

        rcvdata[recv_bytes] = 0;
        fputs(rcvdata, stdout);
    }

    close(sd);
    return 0;
}