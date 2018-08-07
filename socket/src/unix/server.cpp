//
// Created by 姚文锋 on 2018/8/7.
//
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>

#define MYPORT 8080
#define BACKLOG 10 /*多少等待连接控制*/

using namespace std;


int serverTest() {
    cout << "server" << endl;
    int sockfd, new_fd;
    unsigned int sin_size;
    struct sockaddr_in my_addr;
    struct sockaddr_in their_addr; /* connector's address information */

    sockfd = ::socket(AF_INET, SOCK_STREAM, 0); /*需要错误检查 */
//    printf("%d\n", sockfd);
    my_addr.sin_family = AF_INET; /* host byte order */

    my_addr.sin_port = htons(MYPORT); /* short, network byte order */

    my_addr.sin_addr.s_addr = inet_addr("192.168.1.166");
//    printf("%s\n", inet_ntoa(my_addr.sin_addr));

    bzero(&(my_addr.sin_zero), 8); /* zero the rest of the struct */

//    int bindResult = ::bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
//    cout << bindResult << endl;
//
//    int connectResult = connect(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
//    cout << connectResult << endl;
    if (::bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr))== -1) {
        perror("bind");
        cout << "bind erroe" << endl;
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    while(1) { /* main accept() loop */
        sin_size = sizeof(struct sockaddr_in);
        if ((new_fd = ::accept(sockfd, (struct sockaddr *)&their_addr, &sin_size)) == -1) {
            perror("accept");
            continue;
        }
        printf("server: got connection from %s\n", \
        inet_ntoa(their_addr.sin_addr));
        if (!fork()) { /* this is the child process */
            if (send(new_fd, "Hello, world!\n", 14, 0) == -1)
                perror("send");
            close(new_fd);
            exit(0);
        }
        close(new_fd); /* parent doesn't need this */
        while (waitpid(-1, NULL, WNOHANG) > 0); /* clean up child processes */
    }
}
