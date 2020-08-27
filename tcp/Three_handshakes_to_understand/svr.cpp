#include <stdio.h>
#include <unistd.h>
#include <iostream>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main()
{
    // 创建套接字
    int sockfd = socket(AF_INET,SOCK_STREAM, IPPROTO_TCP);
    if(sockfd < 0)
    {
        perror("socket");
        return 0;
    }
    printf("sockfd = %d\n", sockfd);
    // 绑定地址信息
    struct sockaddr_in addr;
    addr.sin_family = AF_INET;
    addr.sin_port = htons(19999);
    addr.sin_addr.s_addr = inet_addr("192.168.187.137");
    int ret = bind(sockfd,(struct sockaddr*)&addr,sizeof(addr));
    if(ret < 0)
    {
        perror("bind");
        return 0;
    }
    // 监听
    // 已完成连接队列的大小可以认为是同一时间最大能连收连接的数量
    ret = listen(sockfd, 5);
    if(ret < 0)
    {
        perror("listen");
        return 0;
    }
    // 获取连接
    int serverfd = accept(sockfd, NULL, NULL);
    printf("serverfd = %d\n",serverfd);
    while(1)
    {
        sleep(1);
    }
    // 收发数据
    // 关闭套接字
}
