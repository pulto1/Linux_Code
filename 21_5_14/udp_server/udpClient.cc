#include "udpClient.hpp"

void Usage(std::string proc)
{
    std::cout <<"Usage: "<< proc << " svr_ip svr_port" << std::endl;
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        Usage(argv[0]);
        exit(1);
    }
    udpClient uc(argv[1], atoi(argv[2]));
    uc.initClient();
    uc.start();

    return 0;
}
