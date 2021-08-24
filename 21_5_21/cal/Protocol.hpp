#ifndef __PROTOCOL_HPP__
#define __PROTOCOL_HPP__

#include <iostream>

typedef struct request{
    int x; //left
    int y; //right
    char op; //+,-*/%
}request_t;

typedef struct response{
    int code; //0, 1 , 2, 3 
    int result;
}response_t;


#endif
