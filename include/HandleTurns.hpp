#ifndef HANDLETURNS_HPP
#define HANDLETURNS_HPP

#include "Network.hpp"
#include <vector>
#include <string>
#include <ncurses.h>

class HandleTurns {
public:
    HandleTurns(bool is_server, Network &net);
    ~HandleTurns();
    void player_management(int argc, char **argv, std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix);
    void attack(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv);
    void defense(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv);
    void print_boards(const std::vector<std::string> &myMatrix, const std::vector<std::string> &enemyMatrix);
    void show_error_popup(const std::string &message);
private:
    bool is_server;
    bool is_my_turn;
    Network &net;
};

#endif // HANDLETURNS_HPP
