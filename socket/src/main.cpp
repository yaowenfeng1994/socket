//
// Created by 姚文锋 on 2018/8/7.
//
#if 1
#include <iostream>
#include <curses.h>
#include <stdio.h>
#include "unix/define.h"
#include "unix/epoll/epoll_server.cpp"

using namespace std;

int main() {

#if 1
//    serverTest();
    pollServer();
#endif
#if 0
    char argv[]="192.158.1.166";//字符串0
//    char argv1[]="123";//字符串1
    char *pArgv[]={argv};
    clientTest(2, pArgv);
#endif
#if 0
    InitChatWindow();
    input();
#endif
}
#endif

#if 0
#include "window/utility.h"

int main() {
#if 0
    serverTest();
#endif
#if 1
    clientTest();
#endif
}
#endif
