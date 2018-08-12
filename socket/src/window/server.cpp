// Created by Ҧ�ķ� on 2018/8/4.
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
        // ��һ��������ʹ��Ĭ�ϵİ�ȫ�ԣ��ڶ���������ʹ������ú������߳���ͬ��ջ��С
        // �������������̺߳�����ڣ����ĸ����������ݸ��̵߳Ĳ���
        // ������������̴߳������������У����������������̵߳�ID
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
            // 1.�̺߳��߳̾����Handle������һ���������߳�����cpu�����е�.....��˵������ˣ����߳̾����һ���ں˶���
            // ���ǿ���ͨ������������̣߳������̵߳��������ں��߳̾�����������ڲ�һ���ġ�
            // �̵߳��������ھ����̺߳����ӿ�ʼִ�е�return���߳̾�������������Ǵ�CreateThread���ص���CloseHandle()��
            // 2.���е��ں˶��󣨰����߳�Handle������ϵͳ��Դ������Ҫ���ģ�Ҳ����˵�����һ��Ҫclosehandle�ر�֮��
            // �������ô������ϵͳ�ľ����Դ�ܿ���ù��ˡ�
            // 3.�����CreateThread�Ժ���Ҫ������߳���һЩ����������ı����ȼ����������̵߳ȴ���ǿ��TermateThread�ȣ�
            // ��Ҫ������������ʹ��������CloseHandle������㿪��һ���̣߳�������Ҫ����������θ�Ԥ��
            // CreateThread��ֱ��CloseHandle�����ˡ����� CloseHandel(ThreadHandle )��ֻ�ǹر���һ���߳̾������
            // ��ʾ�Ҳ���ʹ�øþ������������������Ӧ���߳����κθ�Ԥ�ˡ���û�н����̡߳�
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
//        char sendBuf[1024] = "\b������յ�����ոշ�����Ϣ\0";
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
//        cout << "���߳�ѭ����" <<(*p)-- << endl;
//        if (*p < 0)
//        {
//            cout << "���߳��Ƴ�"<< endl;
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

    char sendBuf[1024] = "\b������յ�����ոշ�����Ϣ\0";
    err = send(*p, sendBuf, strlen(sendBuf), 0);
    if (err == SOCKET_ERROR)
    {
        perror("send fail");
        exit(1);
    }
    delete lpParameter;
    return 0;
}