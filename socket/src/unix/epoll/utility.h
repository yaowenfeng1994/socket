//
// Created by 姚文锋 on 2018/8/10.
//

#ifndef SOCKET_UTILITY_H
#define SOCKET_UTILITY_H
#include <iostream>
#include <sys/socket.h>
#include <arpa/inet.h>

#include <sys/select.h>
#include <sys/poll.h>

// mac下没有epoll
#include <sys/types.h>
#include <sys/event.h>
#include <sys/time.h>

// server ip
#define SERVER_IP "127.0.0.1"
// server port
#define SERVER_PORT 8888
// 多少等待连接控制
#define BACKLOG 10
//epoll size
#define EPOLL_SIZE 5000
#endif //SOCKET_UTILITY_H
