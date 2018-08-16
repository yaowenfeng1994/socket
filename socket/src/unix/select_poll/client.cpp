//
// Created by 姚文锋 on 2018/8/15.
//
#include "sp_utility.h"

using namespace std;

int selectPollClient() {
    cout << "client" << endl;

    struct sockaddr_in remote_addr;

    remote_addr.sin_family = AF_INET;
//     inet_pton(AF_INET, "192.168.1.166", &remote_addr.sin_addr);
    remote_addr.sin_port = htons(PORT);
    remote_addr.sin_addr.s_addr = inet_addr("192.168.1.166");
    bzero(&remote_addr,sizeof(remote_addr));

    int remote_sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if(connect(remote_sockfd,(struct sockaddr*)&remote_addr,sizeof(struct sockaddr)) == -1)
    {
        perror("connect");
        exit(1);
    }
    //文件描述符集合
    fd_set read_fds;
    FD_ZERO(&read_fds);

    FD_SET(remote_sockfd, &read_fds);
    //add stand input device
    FD_SET(0,&read_fds);

    string str;
//    char  buf[1024]={0};

    while (1)
    {
        FD_SET(remote_sockfd, &read_fds);
        FD_SET(0,&read_fds);//add stand input device

        int ret = select(remote_sockfd+1,&read_fds,NULL,NULL,NULL);
        if(ret < 0)
        {
            perror("select");
        }

        if(FD_ISSET(remote_sockfd, &read_fds))
        {
            char recvBuf[1024];
            ret = recv(remote_sockfd,recvBuf,sizeof(recvBuf),0);
            if(ret > 0)
            {
                str.clear();
                recvBuf[ret] = '\0';
                str.append(recvBuf);
                cout<<str<<endl;
            }

        }

        if(FD_ISSET(0, &read_fds))
        {
            // memset(buf, 0, sizeof(buf));
            // scanf("%s",buf);
            char sendBuf[1024] = " Hello, i am client! ";
            ret = send(remote_sockfd, sendBuf, strlen(sendBuf), 0);
            if(ret<=0)
            {
                perror("send");
            }
            else
            {
                str.clear();
                str = str+"send: "+sendBuf+"success\n";
                cout<<str;
            }
        }

    }

    close(remote_sockfd);
}
