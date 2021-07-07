#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "Network.hpp"
#include "InitMaps.hpp"

typedef struct pos {
    int status;
    int x;
    int y;
} t_pos;

class HandleTurns
{
    public:
        HandleTurns();
        ~HandleTurns();
        int player_managment(int argc, char **argv, t_matrix matrix);
    private:
        Network net;
        InitMaps map;
        t_pos data_to_position(std::string data, std::vector<std::string> map);
        void print_navy(t_matrix matrix);
        int win_lose(t_matrix matrix);
        void defense(std::vector<std::string> &map, char **argv);
        void attack(std::vector<std::string> &enemy_map, char **argv);
        std::string user_entry_attack();
        int verify_user_choice_error(std::string choice);
};