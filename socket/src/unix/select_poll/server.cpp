//
// Created by 姚文锋 on 2018/8/15.
//
#include "sp_utility.h"

int selectPollServer() {
    cout << "server" << endl;
    struct sockaddr_in server_addr;
    struct sockaddr_in client_addr;

    int sock_fd = ::socket(AF_INET, SOCK_STREAM, 0);
    int new_fd;
//    unsigned int sin_size;
    bool erase_flag;
    int max_fd = sock_fd;
    char buf[MAX_DATA_SIZE];
    char name_buf[MAX_DATA_SIZE];
    vector<clientSocketFd> connection_fds;
//    connection_fds.reserve(BACKLOG);

    server_addr.sin_family = AF_INET;
    server_addr.sin_port = htons(PORT);
//    server_addr.sin_addr.s_addr = inet_addr("192.168.0.103");
    server_addr.sin_addr.s_addr = inet_addr("172.16.213.82");
    bzero(&(server_addr.sin_zero), 8);

    if (::bind(sock_fd, (struct sockaddr *)&server_addr, sizeof(struct sockaddr))== -1) {
        perror("bind");
        exit(1);
    }

    if (listen(sock_fd, BACKLOG) == -1) {
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

    while (true)
    {
        FD_SET(sock_fd, &read_fds);
        tv.tv_sec = 2; // 这里我们打算让select等待两秒后返回，避免被锁死，也避免马上返回
        tv.tv_usec = 0;

        if (!connection_fds.empty())
        {
            cout << "当前连接池里有：(";
            for (int i =0;i<connection_fds.size();++i)
            {
                FD_SET(connection_fds[i].socketFd,&read_fds);
                FD_SET(connection_fds[i].socketFd,&exception_fds);
                cout << connection_fds[i].socketFd << ",";
            }
            cout << ")" << endl;
        }

        select(max_fd+1, &read_fds, NULL, &exception_fds, &tv);
        for (vector<clientSocketFd>::iterator it=connection_fds.begin();it != connection_fds.end();)
        {
            erase_flag = false;
            if (FD_ISSET(it->socketFd, &read_fds))
            {
                bzero(buf,sizeof(buf));
                if (recv(it->socketFd, buf, MAX_DATA_SIZE, 0) == -1)
                {
                    perror("recv");
                    close(it->socketFd);
                    FD_CLR(it->socketFd,&read_fds);
                    it = connection_fds.erase(it);
                    continue;
                } else {
                    sleep(1);
                    strcpy(name_buf, it->userName.c_str());

                    printf("%s say: %s\n",name_buf, buf);

                    strcat(name_buf, " said:");
                    strcat(name_buf, buf);

                    if (strcmp(buf, "close") == 0)
                    {
                        cout << "这里要删除conn里一个连接" << endl;
                        for (int j =0;j<connection_fds.size();++j)
                        {
                            if (connection_fds[j].socketFd == it->socketFd)
                            {
                                close(it->socketFd);
                                FD_CLR(it->socketFd, &read_fds);
                                it = connection_fds.erase(it);
                                erase_flag = true;
                            }
                        }
                        for (int k =0;k<connection_fds.size();++k)
                        {
                            cout << connection_fds[k].socketFd << endl;
                        }
                        if (connection_fds.empty())
                        {
                            cout << "当前连接池长度为0" << endl;
                            break;
                        }
                    }
                    else {
                        for (int l=0;l<connection_fds.size();++l)
                        {
                            if(connection_fds[l].socketFd != it->socketFd)
                            {
                                if (send(connection_fds[l].socketFd, name_buf, MAX_DATA_SIZE, 0) == -1)
                                {
                                    perror("send");
                                }
                            }
                        }
                    }
                }
            }
            if (!erase_flag) {
                ++it;
            }
        }

        for (vector<clientSocketFd>::iterator it=connection_fds.begin();it!=connection_fds.end();++it)
        {
            if(FD_ISSET(it->socketFd, &exception_fds))
            {
                bzero(buf, sizeof(buf));
                if (recv(it->socketFd, buf, MAX_DATA_SIZE, MSG_OOB) == -1)
                {
                    perror("exception");
                } else {
                    printf("%s",buf);
                }

            }
        }
        if (FD_ISSET(sock_fd, &read_fds))
        {
            if ((new_fd = ::accept(sock_fd, (struct sockaddr *)&client_addr, &client_addr_len)) == -1)
            {
                perror("accept");
                close(new_fd);
                break;
            } else {
                if (recv(new_fd, buf, MAX_DATA_SIZE, 0) == -1)
                {
                    perror("recv");
                } else {
                    clientSocketFd fdObj;
                    fdObj.socketFd = new_fd;
                    fdObj.userName = buf;
                    connection_fds.push_back(fdObj);
                    max_fd = new_fd;
                    // inet_ntoa(struct addr_in) 将IP地址转换为字符串并返回
                    // 只是从监听队列中取出连接，即使客户端已经断开网络连接也会accept成功
                    sprintf(buf, "当前聊天室里有%lu人", connection_fds.size());
                    for (int l=0;l<connection_fds.size();++l)
                    {
                        if (send(connection_fds[l].socketFd, buf, MAX_DATA_SIZE, 0) == -1)
                        {
                            perror("send");
                        }
                    }

                    printf("server: got connection from %s:%d\n", inet_ntoa(client_addr.sin_addr), client_addr.sin_port);
                }
            }
        }
        else
        {
            if (connection_fds.empty()) cout << "暂时还没有新的连接进来" << endl;
        }
    }
    return 0;
}