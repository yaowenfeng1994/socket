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

#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <signal.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
//#include <linux/ip.h>
//#include <linux/tcp.h>
#include <stdlib.h>
#include <sys/types.h>


#define PORT 8088
#define BACKLOG 10 /*多少等待连接控制*/
#define MAX_DATA_SIZE 100 /* 每次可以接收的最大字节 */
using namespace std;

extern int serverTest();
extern int clientTest();
extern int syn();

// 初始化聊天窗口
extern void InitChatWindow();
extern void input();

#endif //SOCKET_DEFINE_H
