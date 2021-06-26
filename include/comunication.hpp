#pragma once
#include <iostream>
#include <sstream>
#include <string.h>


class P2P_ClientServer
{
    public:
        P2P_ClientServer();
        ~P2P_ClientServer();
        void receive(int *valeur);
        void send(int nb_value, std::string *pid);   
    private:
        int status;
};
