//
// Created by 姚文锋 on 2018/8/7.
//
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <sys/wait.h>
#include <netdb.h>
#include <unistd.h>
#include <arpa/inet.h>

#define PORT 8080 /* 客户机连接远程主机的端口 */
#define MAXDATASIZE 100 /* 每次可以接收的最大字节 */

using namespace std;

int clientTest(int argc, char *argv[]) {
    cout << "client" << endl;
    int sockfd, numbytes;
    char buf[MAXDATASIZE];
    struct hostent *he;
    struct sockaddr_in their_addr; /* connector's address information */

    if (argc != 2) {
        fprintf(stderr,"usage: client hostname\n");
        exit(1);
    }

    if ((he=gethostbyname("192.168.1.166")) == NULL) { /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    if ((sockfd = socket(AF_INET, SOCK_STREAM, 0)) == -1) {
        perror("socket");
        exit(1);
    }
    their_addr.sin_family = AF_INET; /* host byte order */
    their_addr.sin_port = htons(PORT); /* short, network byte order */
    their_addr.sin_addr = *((struct in_addr *)(he->h_addr));
//    their_addr.sin_addr.s_addr = inet_addr("192.168.1.166");
    bzero(&(their_addr.sin_zero), 8); /* zero the rest of the struct */
    if(connect(sockfd,(struct sockaddr *)&their_addr,sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    if (send(sockfd, "Hello, i am client!\n", 100, 0) == -1)
        perror("send");

    if ((numbytes=recv(sockfd, buf, MAXDATASIZE, 0)) == -1) {
        perror("recv");
        exit(1);
    }
    buf[numbytes] = '\0';
    printf("Received: %s",buf);
    close(sockfd);
    return 0;
}
