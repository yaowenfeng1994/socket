//
// Created by 姚文锋 on 2018/8/7.
//

#ifndef SOCKET_DEFINE_H
#define SOCKET_DEFINE_H
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <netdb.h>
#include <pthread.h>


#define PORT 8088
#define BACKLOG 10          /*多少等待连接控制*/
#define MAX_DATA_SIZE 100   /* 每次可以接收的最大字节 */

#define MAXCHILD 1024        /* 最多线程数 */
#define TARGET_HOST "14.18.101.62"
#define TARGET_PORT 18086

using namespace std;

struct ip {
    unsigned char       hl;             /* header length */
    unsigned char       tos;            /* type of service */
    unsigned short      total_len;      /* total length */
    unsigned short      id;             /* identification */
    unsigned short      frag_and_flags; /* fragment offset field */
    unsigned char       ttl;            /* time to live */
    unsigned char       proto;          /* protocol */
    unsigned short      checksum;       /* checksum */
    unsigned int        sourceIP;
    unsigned int        destIP;
};

struct tcp {
    unsigned short      sport;
    unsigned short      dport;
    unsigned int        seq;
    unsigned int        ack;
    unsigned char       lenres;
    unsigned char       flag;
    unsigned short      win;
    unsigned short      sum;
    unsigned short      urp;
};

struct pseudo {
    unsigned int        saddr;
    unsigned int        daddr;
    char                zero;
    char                protocol;
    unsigned short      length;
};

struct newSocketFd {
    sockaddr_in addr;
    int         sock_fd;
};

/* 程序活动标志 */
static int alive = -1;
/* 原始套接字 */
extern int sock_fd;

extern int serverTest();
extern int clientTest();
extern int syn();
extern void sig_int(int signo);

extern unsigned short inline checksum (unsigned short *buffer, unsigned short size);
extern void init_header(struct ip *ip, struct tcp *tcp, struct pseudo *pseudo_header);
extern void send_synflood(struct newSocketFd *address);

// 初始化聊天窗口
//extern void InitChatWindow();
//extern void input();

#endif //SOCKET_DEFINE_H
