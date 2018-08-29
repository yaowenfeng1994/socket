//
// Created by 姚文锋 on 2018/8/7.
//
#if 1
#include <iostream>
#include <curses.h>
#include <stdio.h>
#include "unix/define.h"
#include "unix/epoll/epoll_server.cpp"
#include "unix/select_poll/sp_utility.h"

using namespace std;

int main() {

#if 0
//    serverTest();
//    pollServer();
    selectPollServer();

#endif
#if 1
//   clientTest();
//    selectPollClient();
    char buf[1024]= "close";

    int a = strcmp(buf, "close");
    cout << buf << endl;
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
