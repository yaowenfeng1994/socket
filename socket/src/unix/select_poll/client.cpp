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
    char buf[MAX_DATA_SIZE];
    if ((he=gethostbyname("192.168.0.102")) == NULL) { /* get the host info */
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
/*    if (send(remote_sockfd, "Hello, i am client!", 100, 0) == -1)
        perror("send");

    sleep(10);
    if (send(remote_sockfd, "close", 100, 0) == -1)
        perror("send");
    close(remote_sockfd);
    return 0;*/
    fd_set read_fds;
    fd_set write_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&write_fds);
    while (true) {
        FD_SET(remote_sockfd, &read_fds);
        FD_SET(0, &read_fds); //add stand input device
        int ret = select(remote_sockfd + 1, &read_fds, &write_fds, NULL, NULL);
        if (ret < 0) {
            perror("select");
            break;
        }
        if (FD_ISSET(remote_sockfd, &read_fds))
        {
            if (recv(remote_sockfd, buf, MAX_DATA_SIZE, 0) == -1)
            {
                perror("recv");
                continue;
            } else {
                printf("%s\n",buf);
            }
        }
        if (FD_ISSET(0, &write_fds))
        {

        }
    }
    return 0;
}
