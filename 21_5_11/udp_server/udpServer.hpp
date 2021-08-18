#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class udpServer{
    private:
        std::string ip;
        int port;
        int sock;
    public:
        udpServer(std::string _ip="127.0.0.1", int _port=8080)
            :ip(_ip), port(_port)
        {

        }
        void initServer()
        {
            sock = socket(AF_INET, SOCK_DGRAM, 0); //创建套接字
            std::cout << "sock: " << sock << std::endl;
            struct sockaddr_in local; //创建套接字的内核结构
            local.sin_family = AF_INET; //通信域
            local.sin_port = htons(port); //初始化端口号,要考虑大小端，主机序列转成网络序列
            local.sin_addr.s_addr = inet_addr(ip.c_str()); //把字符串地址转化成4字节网络IP地址

            if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){ //强转第二个参数
                std::cerr << "bind error!\n" << std::endl;
                exit(1);
            }
        }

        //echo server
        void start() //启动服务器
        {
            char msg[64];
            for(;;){
                msg[0] = '\0';
                struct sockaddr_in end_point;
                socklen_t len = sizeof(end_point);
                ssize_t s = recvfrom(sock, msg, sizeof(msg)-1,\
                        0, (struct sockaddr*)&end_point, &len);
                if(s > 0){
                    msg[s] = '\0';
                    std::cout <<"client# " << msg << std::endl;
                    std::string echo_string = msg;
                    echo_string += " [server echo!]";
                    sendto(sock, echo_string.c_str(), echo_string.size(), 0,\
                            (struct sockaddr*)&end_point, len);
                }
            }
        }
        ~udpServer()
        {
            close(sock);
        }
};

