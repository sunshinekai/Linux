#include "udpsvr.hpp"

int main(int argc, char* argv[])
{

    // ./svr [ip] [port]
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    if(argc != 3)
    {
        printf("Use this process, please \"./svr [ip][port]\"");
        return 0;
    }

    UdpSvr us;
    if(!us.CreateSocket())
    {
        return 0;
    }

    if(!us.Bind(ip, port))
    {
        return 0;
    }
    while(1)
    {
        // 接收数据
        std::string buf;
        // peeraddr 对端地址信息
        struct sockaddr_in peeraddr;
        us.Recv(&buf, &peeraddr);
        printf("cli say: %s\n",buf.c_str());
        // 发送数据
        printf("server say: ");
        fflush(stdout);
        std::cin >> buf;
        us.Send(buf, &peeraddr);
    }

    us.Close();
    return 0;
}
