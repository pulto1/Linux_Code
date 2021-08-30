#pragma once

#include <iostream>
#include <string>
#include <signal.h>
#include <strings.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <stdlib.h>
#include <unistd.h>

#define BACKLOG 5

using namespace std;

class HttpServer{
    private:
        int port;
        int lsock;
    public:
        HttpServer(int _p):port(_p), lsock(-1)
        {}

        void InitServer()
        {
            signal(SIGCHLD, SIG_IGN);
            lsock = socket(AF_INET, SOCK_STREAM, 0);
            if(lsock < 0){
                cerr << "socket error" << endl;
                exit(2);
            }
            struct sockaddr_in local;
            bzero(&local, sizeof(local));
            local.sin_family = AF_INET;
            local.sin_port = htons(port);
            local.sin_addr.s_addr = INADDR_ANY;

            if(bind(lsock, (struct sockaddr*)&local, sizeof(local)) < 0){
                cerr << "socket bind error" << endl;
                exit(3);
            }

            if(listen(lsock, BACKLOG) < 0){
                cerr << " listen error" << endl;
                exit(4);
            }
        }

        void EchoHttp(int sock)
        {
            char request[2048];
            size_t s = recv(sock, request, sizeof(request), 0); //bug!
            if(s > 0){
                request[s] = 0;
                cout << request << endl;


                string response = "HTTP/1.0 200 Found\r\n";
                response += "Content-type: text/html\r\n";
                //response += "location: https://www.baidu.com";
                response += "\r\n";
                //response += "\
                    <!DOCTYPE html>\
                    <html>\
                    <head>\
                    <title>比特科技</title>\
                    </head>\
                    <body>\
                    <h1>Welcome</h1>\
                    <p>helloworld</p>\
                    </body>\
                    </html>\
                    ";
                send(sock, response.c_str(), response.size(), 0);
            }
            close(sock);
        }
        void Start()
        {
            struct sockaddr_in peer;
            for(;;){
                socklen_t len = sizeof(peer);
                int sock = accept(lsock, (struct sockaddr*)&peer, &len);
                if(sock < 0){
                    cerr << "accept error "<<endl;
                    continue;
                }

                cout << "get a new connect ... done" << endl;

                if(fork() == 0){
                    //child
                    close(lsock);
                    EchoHttp(sock);
                    exit(0);
                }
                close(sock);
            }
        }
        ~HttpServer()
        {
            if(lsock != -1){
                close(lsock);
            }
        }
};








