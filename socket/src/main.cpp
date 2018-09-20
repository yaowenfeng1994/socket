//
// Created by 姚文锋 on 2018/8/7.
//
#if 1
#include "unix/select_poll/sp_utility.h"
#include "unix/define.h"

using namespace std;

int main() {

#if 1
    //    serverTest();
    //    pollServer();
    //    selectPollServer();

    void stopsyn(int signo) {
        printf("程序终止!\n");
        close(rawsock);
        exit(0);
    }

    if (argc != 4) {
        printf("请输入伪造IP地址，目标IP地址，目标端口号！\n");
        exit(1);
    }
    if (inet_aton(argv[1], &pesudo.sin_addr) == 0) {
        printf("伪造IP地址不正确！\n");
        exit(1);
    }
    if (inet_aton(argv[2], &target.sin_addr) == 0) {
        printf("目的IP地址不正确！\n");
        exit(1);
    }
    target.sin_port = htons(atoi(argv[3]));
    /* 信号处理函数 */
    signal(SIGINT, stopsyn);
    syn();

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

//    vector<const char*> list;
//    list = {"a", "b"};
//    list = {"vv"};
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
//        cout << "\n" << list[j];
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
