#ifndef __TCP_SERVER_H__
#define __TCP_SERVER_H__


#include <iostream>
#include <unistd.h>
#include <cstdlib>
#include <string>
#include <cstdlib>
#include <cstring>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <signal.h>
#include <pthread.h>
#include "ThreadPool.hpp"
//using namespace std;

#define BACKLOG 5

class tcpServer{
    private:
        int port;
        int lsock; //监听套接字
        ThreadPool *tp;
    public:
        tcpServer(int _port)
            :port(_port), lsock(-1),tp(nullptr)
        {}
        void initServer()
        {
            signal(SIGCHLD, SIG_IGN);
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
            tp = new ThreadPool();
            tp->ThreadPoolInit();
        }
        //BUG
        static void service(int sock)
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
                else if(s == 0){
                    std::cout << "client quit ...." << std::endl;
                    break;
                }
                else {
                    std::cout << "recv client data error..." << std::endl;
                    break;
                }
            }
            close(sock);
        }
        static void *serviceRoutine(void *arg)
        {
            pthread_detach(pthread_self());
            std::cout << "create a new thread for IO" << std::endl;
            int *p = (int*)arg;
            int sock = *p;
            service(sock);
            delete p;
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
                std::string cli_info = inet_ntoa(endpoint.sin_addr);
                cli_info += ":";
                cli_info += std::to_string(ntohs(endpoint.sin_port));

                std::cout << "get a new link ..." << cli_info << " sock: " << sock <<std::endl;

                Task *t = new Task(sock);
                tp->Put(*t);
                //pthread_t tid;
                //int *p = new int(sock);
                //pthread_create(&tid, nullptr, serviceRoutine, (void*)p); //bug
               // pid_t id = fork();
               // if(id == 0){//child
               //     if(fork()> 0){
               //         exit(0);
               //     }
               //     close(lsock);
               //     service(sock);
               //     exit(0);
               // }

               // close(sock);
               // waitpid(id, NULL, 0); //?
               //pthread_join();
            }
        }
        ~tcpServer()
        {}
};


#endif






