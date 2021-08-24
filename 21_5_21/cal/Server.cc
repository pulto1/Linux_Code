#include "Server.hpp"

void Menu(string proc)
{
    cout << "usage: \n\t";
    cout << proc << " port" << endl;
}

int main(int argc, char *argv[])
{
    if(argc != 2){
        Menu(argv[0]);
        exit(1);
    }

    server *sp = new server(atoi(argv[1]));
    sp->initServer();
    sp->start();

    return 0;
}
