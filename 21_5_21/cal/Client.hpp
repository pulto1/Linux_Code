#ifndef __CLIENT_HPP__
#define __CLIENT_HPP__

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/wait.h>
#include "Protocol.hpp"

using namespace std;

class client{
    private:
        int port;
        string ip;
        int sock;
    public:
        client(string _ip, int _p)
            :ip(_ip), port(_p),sock(-1)
        {}
        void initClient()
        {
            sock = socket(AF_INET, SOCK_STREAM, 0);
            if( sock < 0 )
            {
                cerr << "socket error " << endl;
                exit(2);
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
            struct sockaddr_in server;
            server.sin_family = AF_INET;
            server.sin_port = htons(port);
            server.sin_addr.s_addr = inet_addr(ip.c_str());

            if(connect(sock, (struct sockaddr*)&server, sizeof(server)) < 0){
                cerr << "connect error!" << endl;
                exit(2);
            }

            response_t rsp;
            request_t rq;
            cout << "data1# ";
            cin >> rq.x;
            cout << "data2# ";
            cin >> rq.y;
            cout << "op# ";
            cin >> rq.op;

            send(sock, &rq, sizeof(rq), 0);
            recv(sock, &rsp, sizeof(rsp), 0);

            cout << "code : " << rsp.code << endl;
            cout << "result: " << rsp.result << endl;

        }
        ~client()
        {
            close(sock);
        }
};

#endif





