#include "Client.hpp"

void Menu(string proc)
{
    cout << "usage: \n\t";
    cout << proc << " svr_ip svr_port" << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 3){
        Menu(argv[0]);
        exit(1);
    }

    client *cp = new client(argv[1], atoi(argv[2]));
    cp->initClient();
    cp->start();

    return 0;
}
