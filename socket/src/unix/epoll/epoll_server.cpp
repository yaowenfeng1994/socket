//
// Created by 姚文锋 on 2018/8/10.
//
#include "e_utility.h"

using namespace std;

int pollServer() {
    cout << "poll server run" << endl;
    struct sockaddr_in serverAddress;
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    bzero(&(serverAddress.sin_zero), 8);
    // 创建用于监听的套接字
    int listenerSocket = socket(AF_INET, SOCK_STREAM, 0);
    if(listenerSocket < 0)
    {
        perror("listenerSocket create fail");
        exit(-1);
    }
    printf("listenerSocket %d create success\n", listenerSocket);
    if (::bind(listenerSocket, (struct sockaddr *)&serverAddress, sizeof(struct sockaddr)) < 0) {
        perror("listenerSocket bind fail");
        exit(1);
    }

    if (listen(listenerSocket, BACKLOG) == -1) {
        perror("listenerSocket listen fail");
        exit(1);
    }
    kqueue();
    //创建kqueue
    int epollfd = kqueue();
    if(epollfd < 0)
    {
        perror("epollfd error");
        exit(-1);
    }
    printf("epoll created, epollfd = %d\n", epollfd);

/*    struct kevent {                                                                           */
/*        uintptr_t	ident;		    比如该事件关联的文件描述符                                      */
/*        int16_t		filter;	    可以指定监听类型,如EVFILT_READ,EVFILT_WRITE,EVFILT_TIMER等     */
/*        uint16_t	flags;		    可以指定事件操作类型,比如EV_ADD,EV_ENABLE, EV_DELETE等          */
/*        uint32_t	fflags;		                                                                */
/*        intptr_t	data;		                                                                */
/*        void		*udata;		    可以携带的任意数据                                             */
/*    };                                                                                        */

    struct kevent events;
//    static struct epoll_event events[EPOLL_SIZE];
    //往内核事件表里添加事件
//    addfd(epollfd, listenerSocket, true);
    return 0;
}