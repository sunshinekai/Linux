#pragma once

#include <stdio.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>

class TcpSvr
{
    // 创建套接字
    bool CreateSocket()
    {
        sockfd_ = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
        if(sockfd_ < 0)
        {
            perror("socket");
            return false;
        }
        return true;
    }
    // 绑定地址信息
    bool Bind(std::string& ip, uint16_t port)
    {
        struct sockaddr_in addr;
        addr.sin_family = AF_INET;
        addr.sin_port = htons(port);
        addr.sin_addr.s_addr = inet_addr(ip.c_str());
        int ret = bind(sockfd_, (struct sockaddr*)&addr,sizeof(addr));
        if(ret < 0)
        {
            perror("bind");
            return false;
        }
        return true;
    }
    // 监听
    bool Listen(int bocklog = 5)
    {
        int ret = listen(sockfd_, bocklog);
        if(ret < 0)
        {
            perror("listen");
            return true;
        }
        return false;
    }
    // 获取连接
    bool Accept()
    {
        return true;
    }
    // 发起连接(client)
    // 发送数据
    // 接收数据
    // 关闭套接字
private:
    int sockfd_;
};
