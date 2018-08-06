//
// Created by 姚文锋 on 2018/8/6.
//

#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MYPORT 80

using namespace std;
//int result = ::bind(localSocket, (struct sockaddr *)&localAddr,sizeof(localAddr));

int main() {
    cout << "hello" << endl;
    int sockfd;
    char recvline[MAX_INPUT+1];
    struct sockaddr_in my_addr;

    sockfd = ::socket(AF_INET, SOCK_STREAM, 0); /*需要错误检查 */
    printf("%d\n", sockfd);
    my_addr.sin_family = AF_INET; /* host byte order */

    my_addr.sin_port = htons(MYPORT); /* short, network byte order */

    my_addr.sin_addr.s_addr = inet_addr("123.207.57.98");
    printf("%s\n", inet_ntoa(my_addr.sin_addr));

    bzero(&(my_addr.sin_zero), 8); /* zero the rest of the struct */

//    int bindResult = ::bind(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
//    cout << bindResult << endl;

    int connectResult = connect(sockfd, (struct sockaddr *)&my_addr, sizeof(struct sockaddr));
    cout << connectResult << endl;

}
