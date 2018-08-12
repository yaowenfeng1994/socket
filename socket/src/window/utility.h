//
// Created by 姚文锋 on 2018/8/11.
//

#ifndef SOCKET_UTILITY_H
#define SOCKET_UTILITY_H
#include <string>
#include <cstring>
#include <winsock.h>
#include <iostream>

#define BUF_SIZE 1024
#define SERVER_IP "192.168.0.103"
#define SERVER_PORT 8080
// 多少等待连接控制
#define BACKLOG 10
#define bzero(a, b) memset(a, 0, b)

extern int serverTest();
extern int clientTest();
#endif //SOCKET_UTILITY_H
