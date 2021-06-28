#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "Network.hpp"
#include "InitMaps.hpp"

class HandleTurns
{
    public:
        HandleTurns();
        ~HandleTurns();
        int player_managment(int argc, t_matrix matrix);
    private:
        Network net;
        InitMaps map;
        void print_navy(t_matrix matrix);
        int win_lose(t_matrix matrix);
        void defense(std::vector<std::string> &map);
        void attack(std::vector<std::string> &enemy_map);
        std::string user_entry_attack();
        int verify_user_choice_error(std::string choice);
};