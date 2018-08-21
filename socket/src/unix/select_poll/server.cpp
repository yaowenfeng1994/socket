//
// Created by 姚文锋 on 2018/8/15.
//
#include "sp_utility.h"

using namespace std;

int selectPollServer() {
    cout << "server" << endl;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int sockfd = ::socket(AF_INET, SOCK_STREAM, 0);
    int new_fd, numbytes;
    unsigned int sin_size;
    int max_fd = sockfd;
    char buf[MAX_DATA_SIZE];
    vector<int>	 connFds;
    connFds.reserve(BACKLOG);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
    server_addr.sin_addr.s_addr = inet_addr("192.168.1.166");
    bzero(&(server_addr.sin_zero), 8);

    if (::bind(sockfd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sockfd, BACKLOG) == -1) {
        perror("listen");
        exit(1);
    }

    socklen_t client_addr_len = sizeof(client_addr);

    //文件描述符集合
    fd_set read_fds;
    fd_set exception_fds;
    FD_ZERO(&read_fds);
    FD_ZERO(&exception_fds);
    timeval tv;

    while(1)
    {
        FD_SET(sockfd,&read_fds);
        tv.tv_sec = 2;//这里我们打算让select等待两秒后返回，避免被锁死，也避免马上返回
        tv.tv_usec = 0;
        for(int i =0;i<connFds.size();++i)
        {
            FD_SET(connFds[i],&read_fds);
            FD_SET(connFds[i],&exception_fds);
            cout << connFds[i] << endl;
        }
        select(max_fd+1, &read_fds, NULL, &exception_fds, NULL);
        for (vector<int>::iterator it=connFds.begin();it != connFds.end();)
        {
            if (FD_ISSET(*it, &read_fds))
            {
                bzero(buf,sizeof(buf));
                if ((numbytes=recv(*it, buf, MAX_DATA_SIZE, 0)) == -1)
                {
                    perror("recv");
                    close(*it);
                    FD_CLR(*it,&read_fds);
                    it = connFds.erase(it);
                    continue;
                }
                else
                {
                    buf[numbytes] = '\0';
                    printf("Received: %s",buf);
                    sleep(1);
                    for(int i =0;i<connFds.size();++i)
                    {
                        if(connFds[i] != *it)
                        {
                            string str("some one said:");
                            str.append(buf);
                            int ret = send(*it,str.c_str(),str.length(),0);
                            if(ret<=0)
                            {
                                perror("send");
                            }
                        }

                    }
                }
            }
            ++it;
        }

        for(vector<int>::iterator it = connFds.begin();it != connFds.end();++it)
        {
            if(FD_ISSET(*it, &exception_fds))
            {
                bzero(buf, sizeof(buf));
                int ret = recv(*it, buf, MAX_DATA_SIZE, MSG_OOB);
                if(ret < 0)
                {
                    perror("exception");
                }
                else
                {
                    buf[ret] = '\0';
                    printf("%s",buf);
                }

            }
        }

        if (FD_ISSET(sockfd, &read_fds))
        {
            if ((new_fd = ::accept(sockfd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
            {
                perror("accept");
                close(new_fd);
                break;
            }
            connFds.push_back(new_fd);
            max_fd = new_fd;
            // inet_ntoa(struct addr_in) 将IP地址转换为字符串并返回
            // 只是从监听队列中取出连接，即使客户端已经断开网络连接也会accept成功
            printf("server: got connection from %s\n", inet_ntoa(client_addr.sin_addr));

/*                if (0==fork()) {
                    if ((numbytes=recv(new_fd, buf, MAXDATASIZE, 0)) == -1) {
                        perror("recv");
                        exit(1);
                    }
                    buf[numbytes] = '\0';
                    printf("Received: %s",buf);
                }*/
        }
        else
        {
            cout << "还没有连接进来" << endl;
        }
    }
    return 0;
}