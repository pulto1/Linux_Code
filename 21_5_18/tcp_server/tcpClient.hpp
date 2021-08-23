#ifndef __TCP_CLIENT_H__
#define __TCP_CLIENT_H__

#include <iostream>
#include <string>
#include <cstring>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>



class tcpClient{
    private:
        std::string svr_ip;
        int svr_port;
        int sock;
    public:
        tcpClient(std::string _ip="127.0.0.1", int _port = 8080)
            :svr_ip(_ip),svr_port(_port)
        {}
        void initClient()
        {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if(sock < 0){
                std::cerr << "socket error" << std::endl;
                exit(2);
            }
            struct sockaddr_in svr;
            svr.sin_family = AF_INET;
            svr.sin_port = htons(svr_port);
            svr.sin_addr.s_addr = inet_addr(svr_ip.c_str());//htonl(INADDR_ANY);

            if(connect(sock, (struct sockaddr*)&svr, sizeof(svr)) != 0){
                std::cerr << "connect error" << std::endl;
            }
            //connect success;
        }
        void start()
        {
            char msg[64];
            //while(true){
                std::cout << "Please Enter Message# ";
                fflush(stdout);
                size_t s = read(0, msg, sizeof(msg)-1);
                if(s > 0){
                    msg[s-1] = 0;
                    send(sock, msg, strlen(msg), 0);
                    size_t ss = recv(sock, msg, sizeof(msg)-1, 0);
                    if(ss > 0){
                        msg[ss] = 0;
                        std::cout << "server echo # " << msg << std::endl;
                    }
                    else if(ss == 0){
                        //break;
                    }
                    else{
                        //break;
                    }
                }
            //}
        }
        ~tcpClient()
        {
            close(sock);
        }
};

#endif






