//
// Created by 姚文锋 on 2018/8/15.
//
#include "sp_utility.h"

using namespace std;

int selectPollClient() {
    cout << "client" << endl;
    int remote_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *he;
    struct sockaddr_in remote_addr;
    if ((he=gethostbyname("192.168.1.166")) == NULL) { /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(PORT);
    remote_addr.sin_addr = *((struct in_addr *)(he->h_addr));
//    remote_addr.sin_addr.s_addr = inet_addr("192.168.1.166");
    bzero(&(remote_addr.sin_zero), 8);

    if (connect(remote_sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    }
    if (send(remote_sockfd, "Hello, i am client!\n", 100, 0) == -1)
        perror("send");

    sleep(3);
    if (send(remote_sockfd, "close\n", 100, 0) == -1)
        perror("send");
    close(remote_sockfd);
    return 0;
}
