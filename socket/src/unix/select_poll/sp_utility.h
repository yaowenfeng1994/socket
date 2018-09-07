//
// Created by 姚文锋 on 2018/8/15.
//

#ifndef SOCKET_SP_UTILITY_H
#define SOCKET_SP_UTILITY_H
#include <iostream>
#include <vector>
#include <string>

#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/select.h>
#include <sys/poll.h>

#define PORT 8088
#define BACKLOG 2
#define MAX_DATA_SIZE 512 /* 每次可以接收的最大字节 */

using namespace std;

struct clientSocketFd {
    int     socketFd;
    string  userName;
};

extern int selectPollServer();
extern int selectPollClient();

#endif //SOCKET_UTILITY_H
