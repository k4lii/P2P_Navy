#ifndef HANDLETURNS_HPP
#define HANDLETURNS_HPP

#include <vector>
#include <string>
#include "Network.hpp"

class HandleTurns {
public:
    HandleTurns(bool is_server, Network &net);
    ~HandleTurns();

    void player_management(int argc, char **argv, std::vector<std::string> &matrix);

private:
    void attack(std::vector<std::string> &matrix, char **argv);
    void defense(std::vector<std::string> &matrix, char **argv);

    bool is_server;
    Network &net;
};

#endif // HANDLETURNS_HPP
