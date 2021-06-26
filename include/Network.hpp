#pragma once
#include <iostream>
#include <string.h>
#include <boost/array.hpp>
#include <boost/asio.hpp>

class Network
{
    public:
        Network();
        ~Network();
        std::string receive(std::string str);
        void send(std::string str);   
    private:
        int status;
};
