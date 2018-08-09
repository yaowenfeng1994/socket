//
// Created by 姚文锋 on 2018/8/7.
//
#include <iostream>
#include <curses.h>
#include <stdio.h>
#include "unix/define.h"

using namespace std;

int main() {
#if 0
    cout << "Hello, World!" << "\n" << "skr skr";
    return 0;
#endif
#if 0
    serverTest();
#endif
#if 0
    char argv[]="192.158.1.166";//字符串0
//    char argv1[]="123";//字符串1
    char *pArgv[]={argv};
    clientTest(2, pArgv);
#endif
#if 1
    InitChatWindow();
    input();
#endif
}
