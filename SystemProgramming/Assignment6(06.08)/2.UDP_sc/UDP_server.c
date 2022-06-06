#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 1024
#define PORT 30000
#define BACKLOG 5

int main(int argc, char *argv[]){
    int sd, nsd, pid, bytes, cliaddrsize;
    struct sockaddr_in cliaddr, servaddr;
    char data[MAX];

    if((sd = socket(AF_INET, SOCK_DGRAM, 0)) < 0){
        fprintf(stderr, "can't open socket.\n");
        exit(1);
    }

    bzero ((char*) &servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(PORT);

    if(bind(sd, (struct sockaddr*) &servaddr, sizeof(servaddr)) < 0){
        fprintf(stderr, "can't connect to server.\n");
        exit(1);
    }

    // listen(sd, BACKLOG);

    while(1){
        cliaddrsize = sizeof(cliaddr);
	while(1){
		bytes = recvfrom(sd, data, MAX, 0, (struct sockaddr*) &cliaddr, &cliaddrsize);
		
		    if(bytes == 0){
		        break;
		    }
		    
		    else if(bytes < 0){
		        fprintf(stderr, "can't receive data.\n");
		        break;
		        // exit(1);
		    }
		
  		if(bytes > 0){
  		    //fputs(data, stdout);

		    if(sendto(sd, data, bytes, 0, (struct sockaddr*) &cliaddr, sizeof(cliaddr)) != bytes){
		        fprintf(stderr, "can't send data.\n");
		        break;		        
		        //exit(1);
		    }

		}
		}

	}
    }

