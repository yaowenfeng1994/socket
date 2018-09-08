//
// Created by 姚文锋 on 2018/8/15.
//
#include "sp_utility.h"

int selectPollClient() {
    cout << "client" << endl;
    int remote_sockfd = socket(AF_INET, SOCK_STREAM, 0);
    struct hostent *he;
    struct sockaddr_in remote_addr;
    string user_name;
    char buf[MAX_DATA_SIZE];
    if ((he=gethostbyname("192.168.0.103")) == nullptr) { /* get the host info */
        herror("gethostbyname");
        exit(1);
    }

    remote_addr.sin_family = AF_INET;
    remote_addr.sin_port = htons(PORT);
    remote_addr.sin_addr = *((struct in_addr *)(he->h_addr));
    bzero(&(remote_addr.sin_zero), 8);

    cout << "请输入你在聊天室中的用户名: ";
    getline(cin, user_name);
    if (connect(remote_sockfd, (struct sockaddr *)&remote_addr, sizeof(struct sockaddr)) == -1) {
        perror("connect");
        exit(1);
    } else {
        strcpy(buf, user_name.c_str());
        if (send(remote_sockfd, buf, MAX_DATA_SIZE, 0) == -1)
            perror("send");
    }
/*    if (send(remote_sockfd, "Hello, i am client!", 100, 0) == -1)
        perror("send");

    sleep(10);
    if (send(remote_sockfd, "close", 100, 0) == -1)
        perror("send");
    close(remote_sockfd);
    return 0;*/
    fd_set read_fds;
    FD_ZERO(&read_fds);
    while (true) {
        FD_SET(remote_sockfd, &read_fds);
        FD_SET(0, &read_fds); //add stand input device
        int ret = select(remote_sockfd + 1, &read_fds, nullptr, nullptr, nullptr);
        if (ret < 0) {
            perror("select");
            break;
        }
        if (FD_ISSET(remote_sockfd, &read_fds))
        {
            if (recv(remote_sockfd, buf, MAX_DATA_SIZE, 0) == -1)
            {
                perror("recv");
                continue;
            } else {
                printf("%s\n",buf);
            }
        }
        if (FD_ISSET(0, &read_fds))
        {
            cout << "请输入你要说的话: ";
            cin.getline(buf, 200);
            if (strcmp(buf, "close") == 0)
            {
                cout << "退出聊天" << endl;
                if (send(remote_sockfd, buf, MAX_DATA_SIZE, 0) == -1)
                    perror("send");
                close(remote_sockfd);
                break;
            }
            if (send(remote_sockfd, buf, MAX_DATA_SIZE, 0) == -1)
                perror("send");
        }
        sleep(2);
    }
    return 0;
}
