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
        void print_navy(char **map, char **enemy_map);//private
        int player_managment(int argc, char **map, char **enemy_map);
    private:
        Network net;
        InitMaps map;
        int win_lose(char **map, char **enemy_map);
        void defense(char **map);
        void attack(char **enemy_map);
        std::string user_entry_attack();
        int verify_user_choice_error(std::string choice);
};