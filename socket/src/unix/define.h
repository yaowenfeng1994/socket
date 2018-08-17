//
// Created by 姚文锋 on 2018/8/7.
//

#ifndef SOCKET_DEFINE_H
#define SOCKET_DEFINE_H
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>


#define PORT 8088
#define BACKLOG 10 /*多少等待连接控制*/
#define MAXDATASIZE 100 /* 每次可以接收的最大字节 */

extern int serverTest();
extern int clientTest();

// 初始化聊天窗口
extern void InitChatWindow();
extern void input();

#endif //SOCKET_DEFINE_H
