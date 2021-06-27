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
};