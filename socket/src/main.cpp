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
    selectPollClient();
//    char buf[1024]= "close";
//    if (strcmp(buf, "close") == 0)
//    {
//        cout << 2222<< endl;
//    }
//    cout << a << endl;

//    vector<int> list = {1};
//    for (vector<int>::iterator it=list.begin();it != list.end();)
//    {
//        if (*it == 1)
//        {
//            it = list.erase(it);
//            if (list.size()==0)
//            {
//                break;
//            }
//        }
//        cout << *it << endl;
//        ++it;
//    }
//
//    for (int j =0;j<list.size();++j)
//    {
//        cout << list[j] << endl;
//    }
//    char a[20];
//    cout << "请输入你要说的话: ";
//    cin.getline(a, 200);
//    cout << a <<endl;
//    string user_name;
//    cout << "请输入你在聊天室中的用户名: ";
//    getline(cin, user_name);
//    cout << user_name <<endl;
//    strcpy(a, user_name.c_str());
//    cout << a <<endl;
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
