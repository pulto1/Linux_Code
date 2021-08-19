#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__


#include <iostream>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

//using namespace std;

#define BACKLOG 5

class tcpServer{
    private:
        int port;
        int lsock; //监听套接字
    public:
        tcpServer(int _port):port(_port), lsock(-1)
        {}
        void initServer()
        {
            lsock = socket(AF_INET, SOCK_STREAM, 0);
            if(lsock < 0){
                std::cerr << "socket error" << std::endl;
                exit(2);
            }
            struct sockaddr_in local;
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = htonl(INADDR_ANY);

            if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0){
                std::cerr << "bind error" << std::endl;
                exit(3);
            }

            if(listen(lsock, BACKLOG) < 0){
                std::cerr << "bind error" << std::endl;
                exit(4);
            }
        }
        void service(int sock)
        {
            char buffer[1024];
            while(true){
                //read or write -> ok!
                size_t s = recv(sock, buffer, sizeof(buffer)-1, 0);
                if(s > 0){
                    buffer[s] = 0;
                    std::cout << "client# " << buffer << std::endl;

                    send(sock, buffer, strlen(buffer), 0);
                }
            }
        }
        void start()
        {
            sockaddr_in endpoint;
            while(true){
                socklen_t len = sizeof(endpoint);
                int sock = accept(lsock, (struct sockaddr*)&endpoint, &len);
                if(sock < 0){
                    std::cerr << "accept error" << std::endl;
                    continue;
                }
                std::cout << "get a new link ..." <<std::endl;
                service(sock);
            }
        }
        ~tcpServer()
        {}
};


#endif






