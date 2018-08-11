// Created by 姚文锋 on 2018/8/4.
//
#include "utility.h"
using namespace std;

int serverTest() {
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(2, 2);
    int iResult;
    iResult = WSAStartup(sockVersion, &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    } else {
        printf("WSAStartup success: %d\n", iResult);
    }

    sockaddr_in serverAddress;
    sockaddr_in clientAddress;

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_port = htons(SERVER_PORT);
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    bzero(&(serverAddress.sin_zero), 8);

    SOCKET listenerSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    if (listenerSocket == INVALID_SOCKET) {
        perror("listenerSocket create fail");
        exit(-1);
    }
    printf("listenerSocket %d create success\n", listenerSocket);

    if (bind(listenerSocket, (struct sockaddr *) &serverAddress, sizeof(struct sockaddr)) < 0) {
        perror("listenerSocket bind fail");
        exit(1);
    }

    if (listen(listenerSocket, BACKLOG) == -1) {
        perror("listenerSocket listen fail");
        exit(1);
    }

    int time = 1;
    while (1) {
        int len = sizeof(struct sockaddr);
        SOCKET clientSocket = accept(listenerSocket, (struct sockaddr *) &clientAddress, &len);
        if (clientSocket == INVALID_SOCKET) {
            cout << WSAGetLastError() << endl;
            perror("accept fail");
            return 0;
        }
        printf("server: got connection from %s\n", inet_ntoa(clientAddress.sin_addr));

        char buf[1024] = "\0";
        int buflen = recv(clientSocket, buf, BUF_SIZE, 0);
        if (buflen == SOCKET_ERROR) {
            perror("recv fail");
            return 0;
        }
        cout << "recieve data" << time++ << ": " << buf << endl;
    }
}