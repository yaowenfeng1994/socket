//
// Created by 姚文锋 on 2018/8/15.
//

#ifndef SOCKET_SP_UTILITY_H
#define SOCKET_SP_UTILITY_H
#include <iostream>
#include <vector>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>

#include <sys/select.h>
#include <sys/poll.h>
#define PORT 8088
#define BACKLOG 2
#define MAXDATASIZE 100 /* 每次可以接收的最大字节 */

extern int selectPollServer();
extern int selectPollClient();

#endif //SOCKET_UTILITY_H
