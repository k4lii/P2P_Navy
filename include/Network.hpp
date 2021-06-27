#pragma once
#include <string.h>
#include <iostream>
#include <boost/asio.hpp>

using namespace boost::asio;
using namespace boost::asio::ip;

class Network
{
    public:
        Network();
        ~Network();
        void Send(std::string message, std::string ip, int port);
        std::string Receive(int port);
};