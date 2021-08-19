#pragma once

#include <iostream>
#include <string>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

class udpClient{
    private:
        std::string ip;
        int port;
        int sock;
    public:
        //ip,port? server ip,port!!!
        udpClient(std::string _ip="127.0.0.1", int _port=8080)
            :ip(_ip), port(_port)
        {

        }
        void initClient()
        {
            sock = socket(AF_INET, SOCK_DGRAM, 0);
            std::cout << "sock: " << sock << std::endl;
           // struct sockaddr_in local;
           // local.sin_family = AF_INET;
           // local.sin_port = htons(port);
           // local.sin_addr.s_addr = inet_addr(ip.c_str());

           // if(bind(sock, (struct sockaddr*)&local, sizeof(local)) < 0){
           //     std::cerr << "bind error!\n" << std::endl;
           //     exit(1);
           // }
        }

        //echo server
        void start()
        {
          //  char msg[64];
            std::string msg;
            struct sockaddr_in peer;
            peer.sin_family = AF_INET;
            peer.sin_port = htons(port);
            peer.sin_addr.s_addr = inet_addr(ip.c_str());

            for(;;){
                std::cout << "Please Enter# ";
                std::cin >> msg;
                if(msg == "quit"){
                    break;
                }

                sendto(sock, msg.c_str(), msg.size(), 0, (struct sockaddr*)&peer, sizeof(peer));

                char echo[128];
                ssize_t s = recvfrom(sock, echo, sizeof(echo)-1, 0, nullptr, nullptr);
                if(s >0){
                    echo[s] = 0;
                    std::cout << "server# " << echo << std::endl;
                }

          //      msg[0] = '\0';
          //      struct sockaddr_in end_point;
          //      socklen_t len = sizeof(end_point);
          //      ssize_t s = recvfrom(sock, msg, sizeof(msg)-1,\
          //              0, (struct sockaddr*)&end_point, &len);
          //      if(s > 0){
          //          msg[s] = '\0';
          //          std::cout <<"client# " << msg << std::endl;
          //          std::string echo_string = msg;
          //          echo_string += " [server echo!]";
          //          sendto(sock, echo_string.c_str(), echo_string.size(), 0,\
          //                  (struct sockaddr*)&end_point, len);
          //      }
            }
        }
        ~udpClient()
        {
            close(sock);
        }
};














