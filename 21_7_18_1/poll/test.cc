#include <iostream>
#include <stdio.h>
#include <unistd.h>
#include <poll.h>

using namespace std;

int main()
{
    struct pollfd rfds[1];
    rfds[0].fd = 1;
    rfds[0].events = POLLOUT;
    rfds[0].revents = 0;

    char buf[1024] = {0};

    cout << "poll begin..." << endl;
    while(true){
        switch(poll(rfds, 1, 1000)){
            case 0:
                cout << "time out ..." << endl;
                break;
            case -1:
                cout << "poll error" << endl;
                break;
            default:
                cout << "events happen!" << endl;
                //HandlerEvents(rfds);
                if(rfds[0].fd == 1 && (rfds[0].revents & POLLOUT)){
                    cout << "hello world";
                    ssize_t s = read(0, buf, sizeof(buf));
                    buf[s] = 0;
                    cout <<"echo# "<< buf <<endl;
                }
                break;
        }
    }
    return 0;
}
