#pragma  once

#include <stdio.h>
#include <iostream>
#include <cstring>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

class UdpSvr
{
public:
    UdpSvr(){ _sock = -1;}
    ~UdpSvr(){}
    // Socket
    bool CreateSocket()
    {
       _sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
       if(_sock < 0)
       {
           perror("socket");
           return false;
       }
       return true;
    }

    // Bind
    bool Bind(std::string& ip, uint16_t port)
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        // inet_addr
        // 1.将点分十进制的ip转换成uint32
        // 2.将主机字节序转换为网络字节序
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
       int ret =  bind(_sock,(struct sockaddr*)&addr, sizeof(addr));
       if(ret < 0)
       {
           perror("bind");
           return false;
       }
       return true;
    }

    // send
    bool Send(std::string& data, struct sockaddr_in* destaddr)
    {
        int SendSize = sendto(_sock, data.c_str(), data.size(), 0, (struct sockaddr*)destaddr, sizeof(struct sockaddr_in));
        if(SendSize < 0)
        {
            perror("sendto");
            return false;
        }
        return true;
    }
    
    // Recv
    // buf:出参，返回给调用者接受到了什么数据
    // srcaddr:这条数据从哪里来的，地址信息是数据源端主机的地址信息
    bool Recv(std::string* buf, struct sockaddr_in* srcaddr)
    {
        char tmp[1024];
        memset(tmp,'\0',sizeof(tmp));
        socklen_t socklen = sizeof(struct sockaddr_in);
        // 如果接收缓冲区当中没有数据，则flags为0，则recvfrom会阻塞等待
        int RecvSize = recvfrom(_sock, tmp, sizeof(tmp) - 1, 0 , (struct sockaddr*)srcaddr, &socklen);
        if(RecvSize < 0)
        {
            perror("recvfrom");
            return false;
        }
        buf->assign(tmp, RecvSize);
        return true;
    }
    
    // Close
    void Close()
    {
        close(_sock);
        _sock = -1;
    }

private:
    int _sock;
};
