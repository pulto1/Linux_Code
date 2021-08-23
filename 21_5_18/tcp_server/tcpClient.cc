#include "tcpClient.hpp"

void Usage(std::string proc)
{
    std::cout << "Usage: \n" << "\t";
    std::cout << proc << " svr_ip svr_port" << std::endl;
}

//./tcpClient svr_ip svr_port
int main(int argc, char *argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        exit(1);
    }
    tcpClient *tc = new tcpClient(argv[1], atoi(argv[2]));

    tc->initClient();
    tc->start();

    delete tc;
    return 0;
}
