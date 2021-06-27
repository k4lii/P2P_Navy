#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

class HandleTurns
{
    public:
        HandleTurns();
        ~HandleTurns();
        int read_error_gestion(char *buffer);
        void print_error_attack(char *choice);
        void attack(char *pid, char **enemy_map);
        void defense(char *pid, char **map);
        int player2(char *str, char **argv, char **map, char **enemy_map);
        int player1(char *str, int pid_j2, char **map, char **enemy_map);
        int win_lose(char **map, char **enemy_map);
        void print_latest_message(int value);
};