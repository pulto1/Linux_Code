#ifndef __SERVER_HPP__
#define __SERVER_HPP__

#include <iostream>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "Protocol.hpp"

using namespace std;

class server{
    private:
        int port;
        int lsock;
    public:
        server(int _p):port(_p),lsock(-1)
        {}
        void initServer()
        {
            lsock = socket(AF_INET, SOCK_STREAM, 0);
            if( lsock < 0 )
            {
                cerr << "socket error " << endl;
                exit(2);
            }
            struct sockaddr_in local;
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = INADDR_ANY;

            if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0){
                cerr << "bind error!" << endl;
                exit(3);
            }

            if(listen(lsock, 5) < 0){
                cerr << "listen error!\n" << endl;
            }
        }

        void cal(int sock)
        {
            //短连接来完成对应的计算!
            request_t rq;
            response_t rsp={4, 0};
            ssize_t s = recv(sock, &rq, sizeof(rq), 0); //BUG
            if(s > 0){
                rsp.code = 0;
                switch(rq.op){
                    case '+':
                        rsp.result = rq.x + rq.y;
                        break;
                    case '-':
                        rsp.result = rq.x - rq.y;
                        break;
                    case '*':
                        rsp.result = rq.x * rq.y;
                        break;
                    case '/':
                        if(rq.y != 0){
                            rsp.result = rq.x / rq.y;
                        }
                        else{
                            rsp.code = 1;
                        }
                        break;
                    case '%':
                        if(rq.y != 0){
                            rsp.result = rq.x + rq.y;
                        }
                        else{
                            rsp.code = 2;
                        }
                        break;
                    default:
                        rsp.code = 3;
                        break;
                }
            }
            send(sock, &rsp, sizeof(rsp), 0);
            close(sock);
        }
        void start()
        {
            struct sockaddr_in peer;
            for(;;){
                socklen_t len = sizeof(peer);
                int sock = accept(lsock, (struct sockaddr*)&peer,&len);
                if( sock < 0 ){
                    cerr << "accept error!" << endl;
                    continue;
                }
                if(fork() == 0){
                    if(fork() > 0){
                        exit(0);
                    }
                    //孙子
                    close(lsock);
                    //todo
                    cal(sock);
                    exit(0);
                }
                close(sock);
                waitpid(-1, nullptr, 0);
            }
        }
        ~server()
        {
            close(lsock);
        }
};

#endif





