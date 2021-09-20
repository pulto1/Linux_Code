#pragma once

#include "Sock.hpp"


#define DFL_PORT 8080 //端口号
#define NUM (sizeof(fd_set)*8) //位图大小*8文件打开文件描述符数目
#define DFL_FD -1 //辅助数组初始值

class SelectServer{
    private:
        int lsock; //listen sock
        int port;
        int fd_array[NUM]; //辅助数组，保存已经打开的文件描述符
    public:
        SelectServer(int _p = DFL_PORT):port(_p)
        {}
        void InitServer()
        {
            for(int i = 0 ; i < NUM; i++){
                fd_array[i] = DFL_FD;
            }
            lsock = Sock::Socket(); //静态方法，直接用类名访问
            Sock::Setsockopt(lsock); //端口号复用
            Sock::Bind(lsock, port);
            Sock::Listen(lsock);

            fd_array[0] = lsock;
        }
        void AddFd2Array(int sock)
        {
            int i = 0;
            for( ; i < NUM; i++){
                if(fd_array[i] == DFL_FD){
                    break;
                }
            }
            if(i >= NUM) //辅助数组满了，文件描述符处理不了了
            {
                cerr << "fd array is full, close sock" << endl;
                close(sock);
            }
            else{
                fd_array[i] = sock;
                cout << "fd: " << sock << " add to select ..." << endl;
            }
        }
        void DefFdFromArray(int index)
        {
            if(index >=0 && index < NUM){
                fd_array[index] = DFL_FD;
            }
        }
        void HandlerEvents(fd_set *rfds)
        {
            for(int i = 0; i < NUM; i++){
                if(fd_array[i] == DFL_FD){
                    continue;
                }

                //下标为i的文件描述符是有效的
                if(FD_ISSET(fd_array[i], rfds)) //检测fd_array[i]文件描述符在不在rfds中
                {
                    //read ready
                    if(fd_array[i] == lsock){
                        //link event
                        int sock = Sock::Accept(lsock);
                        if(sock >= 0){
                            //sock ok
                            cout << "get a new link ..." << endl;
                            AddFd2Array(sock); //把获取到的文件描述符添加到辅助数组中
                        }
                    }
                    else{
                        //data ready event
                        //bug!
                        char buf[10240];
                        ssize_t s= recv(fd_array[i], buf, sizeof(buf), 0);
                        if(s>0){
                            buf[s] = 0;
                            cout << "client# " << buf << endl;
                        }
                        else if(s == 0){ //对端关闭链接了
                            cout << "clien quit" << endl;
                            close(fd_array[i]); //我这边也关闭链接
                            DefFdFromArray(i); //把文件描述符从辅助数组中删掉
                        }
                        else{ //报错
                            //TODO
                        }
                    }
                }
                //if(FD_ISSE(fd, wfds)){ 检测写事件
                //}
            }
        }
        void Start()
        {
            int maxfd = DFL_FD;
            for(;;){
                //select
                fd_set rfds;
                FD_ZERO(&rfds); //清空位图
                cout << "fd_array: ";
                //每次检测时，把辅助数组里面的文件描述符设置进位图中（这里是一个巧妙的地方，因为参数234是输入输出型参数）
                for(int i = 0; i < NUM; i++){
                    if(fd_array[i] != DFL_FD){
                        cout << fd_array[i] << " ";
                        FD_SET(fd_array[i], &rfds);
                        if(maxfd < fd_array[i]){
                            maxfd = fd_array[i];
                        }
                    }
                }
                cout << endl;
                cout << "begin select ..." << endl;
                //struct timeval timeout = {5, 0}; //如果等待时间到后事件未就绪，timeout就会被设置为0.所以下一次检测时要重新设置
                switch(select(maxfd+1, &rfds, nullptr, nullptr, /*&timeout)*/nullptr)){
                    case 0:
                        cout << "timeout ..." << endl;
                        break;
                    case -1:
                        cerr << "select error!" << endl;
                        break;
                    default:
                        //success
                        //有文件描述符已经准备就绪
                        HandlerEvents(&rfds); //处理文件描述符
                        break;
                }
            
            }
        }
        ~SelectServer()
        {}
};


