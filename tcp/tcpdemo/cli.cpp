#include "tcpsvr.hpp"

// 从命令行当中获取连接服务端的ip和port
int main(int argc, char* argv[])
{
    if(argc != 3)
    {
        printf("Start Client: ./cli[server ip] [server port]\n");
        return 0;
    }
    std::string ip = argv[1];
    uint16_t port = atoi(argv[2]);
    TcpSvr ts;
    if(!ts.CreateSocket())
    {
        return 0;
    }
    if(!ts.Connect(ip, port))
    {
        return 0;
    }
    while(1)
    {
        printf("please enter msg to server:");
        fflush(stdout);
        std::string buf;
        std::cin >> buf;
        ts.Send(buf);
        ts.Recv(&buf);
        printf("Server say: %s\n", buf.c_str());
    }
    ts.Close();
    return 0;
}
