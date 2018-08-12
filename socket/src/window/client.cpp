//
// Created by 姚文锋 on 2018/8/11.
//
#include "utility.h"

using namespace std;

int clientTest() {
    WSADATA wsaData;
    WORD sockVersion = MAKEWORD(2, 2);
    int iResult;
    iResult = WSAStartup(sockVersion, &wsaData);
    if (iResult != 0) {
        printf("WSAStartup failed: %d\n", iResult);
    } else {
        printf("WSAStartup success: %d\n", iResult);
    }

    SOCKET connectSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (connectSocket == INVALID_SOCKET) {
        perror("clientSocket create fail");
        exit(-1);
    }
    sockaddr_in clientAddress;

    clientAddress.sin_family = AF_INET;
    clientAddress.sin_port = htons(SERVER_PORT);
    clientAddress.sin_addr.s_addr = inet_addr(SERVER_IP);
    bzero(&(clientAddress.sin_zero), 8);
    if(connect(connectSocket,(struct sockaddr *)&clientAddress,sizeof(struct sockaddr)) == INVALID_SOCKET) {
        perror("connect");
        exit(1);
    }

    char buf[1024] = "\0";
    cout << "input data: ";
    cin >> buf;
    iResult = send(connectSocket, buf, strlen(buf), 0);
    if (iResult == SOCKET_ERROR)
    {
        perror("send fail");
        exit(1);
    }

    char recvBuf[1024] = "\0";
    int bufLen = recv(connectSocket, recvBuf, BUF_SIZE, 0);
    if (bufLen == SOCKET_ERROR) {
        perror("recieve fail");
        return 0;
    }
    cout << "client recieve data: " << recvBuf << endl;
    return 0;
}
