//
// Created by 姚文锋 on 2018/8/7.
//
#include "define.h"

int serverTest() {
    cout << "server" << endl;
    int sockfd, new_fd, numbytes;
    unsigned int sin_size;
    char buf[MAXDATASIZE];
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr; /* connector's address information */

    sockfd = ::socket(AF_INET, SOCK_STREAM, 0); /*需要错误检查 */
    //htons()作用是将端口号由主机字节序转换为网络字节序的整数值。(host to net)
    //inet_addr()作用是将一个IP字符串转化为一个网络字节序的整数值，用于sockaddr_in.sin_addr.s_addr。
    //inet_ntoa()作用是将一个sin_addr结构体输出成IP字符串(network to ascii)
    my_addr.sin_family = AF_INET;
    my_addr.sin_port = htons(PORT);
    my_addr.sin_addr.s_addr = inet_addr("192.168.1.166");
    printf("%s\n", inet_ntoa(my_addr.sin_addr));
    bzero(&(my_addr.sin_zero), 8);

    if (::bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
        perror("bind");
        cout << "bind error" << endl;
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    while(1) {
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = ::accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n", inet_ntoa(their_addr.sin_addr));
        if (0==fork()) {
            if ((numbytes=recv(new_fd, buf, MAX_DATA_SIZE, 0)) == -1) {
                perror("recv");
                exit(1);
            }
            buf[numbytes] = '\0';
            printf("Received: %s",buf);
        }
        if (0==fork()) { /* this is the child process */
            if (send(new_fd, "Hello, i am server!\n", 100, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd); /* parent doesn't need this */
        while (waitpid(-1, NULL, WNOHANG) > 0); /* clean up child processes */
    }
}
