#ifndef HANDLE_TURNS_HPP
#define HANDLE_TURNS_HPP

#include <ncurses.h>  // Include the ncurses library
#include "Network.hpp"
#include <vector>
#include <string>

class HandleTurns {
public:
    HandleTurns(bool is_server, Network &net);
    ~HandleTurns();
    void player_management(int argc, char **argv, std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix);
    void print_boards(const std::vector<std::string> &myMatrix, const std::vector<std::string> &enemyMatrix);
    void attack(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv);
    void defense(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv);
    void show_error_popup(const std::string &message);
    void draw_borders(WINDOW* win, int start_row, int start_col, int num_rows, int num_cols);
    void print_char_by_type(char displayChar, int y, int x);
private:
    bool is_server;
    bool is_my_turn;
    Network &net;
};

#endif // HANDLETURNS_HPP
