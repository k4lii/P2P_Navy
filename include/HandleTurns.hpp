#pragma once
#include <vector>
#include <string>
#include "Network.hpp"

class HandleTurns {
public:
    HandleTurns(bool is_server, Network& net);
    ~HandleTurns();
    void player_management(int argc, char** argv, std::vector<std::string>& myMatrix, std::vector<std::string>& enemyMatrix);

private:
    void attack(std::vector<std::string>& myMatrix, std::vector<std::string>& enemyMatrix, char** argv);
    void defense(std::vector<std::string>& myMatrix, std::vector<std::string>& enemyMatrix, char** argv);
    void print_boards(const std::vector<std::string>& myMatrix, const std::vector<std::string>& enemyMatrix);

    bool is_server;
    Network& net;
    bool is_my_turn;
};
