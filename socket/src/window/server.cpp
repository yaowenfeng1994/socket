// Created by 姚文锋 on 2018/8/4.
//
#include "utility.h"
using namespace std;

// DWORD WINAPI ThreadProc(LPVOID lpParameter);
DWORD WINAPI threadClient(LPVOID lpParameter);

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
        // 第一个参数，使用默认的安全性；第二个参数，使用与调用函数的线程相同的栈大小
        // 第三个参数，线程函数入口；第四个参数，传递给线程的参数
        // 第五个参数，线程创建后，立即运行，第六个参数，新线程的ID
        // int threadTime = time;
        // HANDLE hThread1 = CreateThread(NULL, 0, ThreadProc, &threadTime, 0, NULL);

        int len = sizeof(struct sockaddr);
        SOCKET clientSocket = accept(listenerSocket, (struct sockaddr *) &clientAddress, &len);
        if (clientSocket == INVALID_SOCKET) {
            cout << WSAGetLastError() << endl;
            perror("accept fail");
            return 0;
        }
        printf("server: got connection from %s\n", inet_ntoa(clientAddress.sin_addr));
        if (clientSocket > 0)
        {
            SOCKET *newClientSocket = new SOCKET(clientSocket);
            cout << "clientSocket1: " << *newClientSocket << endl;
            // 1.线程和线程句柄（Handle）不是一个东西，线程是在cpu上运行的.....（说不清楚了），线程句柄是一个内核对象。
            // 我们可以通过句柄来操作线程，但是线程的生命周期和线程句柄的生命周期不一样的。
            // 线程的生命周期就是线程函数从开始执行到return，线程句柄的生命周期是从CreateThread返回到你CloseHandle()。
            // 2.所有的内核对象（包括线程Handle）都是系统资源，用了要还的，也就是说用完后一定要closehandle关闭之，
            // 如果不这么做，你系统的句柄资源很快就用光了。
            // 3.如果你CreateThread以后需要对这个线程做一些操作，比如改变优先级，被其他线程等待，强制TermateThread等，
            // 就要保存这个句柄，使用完了在CloseHandle。如果你开了一个线程，而不需要对它进行如何干预，
            // CreateThread后直接CloseHandle就行了。所以 CloseHandel(ThreadHandle )，只是关闭了一个线程句柄对象，
            // 表示我不再使用该句柄，即不对这个句柄对应的线程做任何干预了。并没有结束线程。
            HANDLE hThread1 = CreateThread(NULL, 0, threadClient, newClientSocket, 0, NULL);
            CloseHandle(hThread1);
        }

//        char buf[1024] = "\0";
//        int bufLen = recv(clientSocket, buf, BUF_SIZE, 0);
//        if (bufLen == SOCKET_ERROR) {
//            perror("recieve fail");
//            return 0;
//        }
//        cout << "server recieve data" << time++ << ": " << buf << endl;
//
//        char sendBuf[1024] = "\b服务端收到了你刚刚发的消息\0";
//        cout << sendBuf << endl;
//        iResult = send(clientSocket, sendBuf, strlen(sendBuf), 0);
//        if (iResult == SOCKET_ERROR)
//        {
//            perror("send fail");
//            exit(1);
//        }
    }
}

//DWORD WINAPI ThreadProc(LPVOID lpParameter)
//{
//    int *p = (int*)lpParameter;
//    while(1)
//    {
//        cout << "子线程循环中" <<(*p)-- << endl;
//        if (*p < 0)
//        {
//            cout << "子线程推出"<< endl;
//            break;
//        }
//        Sleep(1000);
//    }
//    return 0;
//}

DWORD WINAPI threadClient(LPVOID lpParameter)
{
    char buf[1024] = "\0";
    int err;
    SOCKET *p = (SOCKET*)lpParameter;
    cout << "clientSocket2: " << *p << endl;
    int bufLen = recv(*p, buf, BUF_SIZE, 0);
    if (bufLen == SOCKET_ERROR) {
        perror("recieve fail");
        return 0;
    }
    cout << "server recieve data: " << buf << endl;

    char sendBuf[1024] = "\b服务端收到了你刚刚发的消息\0";
    err = send(*p, sendBuf, strlen(sendBuf), 0);
    if (err == SOCKET_ERROR)
    {
        perror("send fail");
        exit(1);
    }
    delete lpParameter;
    return 0;
}