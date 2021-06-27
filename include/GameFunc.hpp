#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "struct.hpp"

#define FILE_LEN 33
#define LINE_LEN 7

class GameFunc
{
    public:
        GameFunc();
        ~GameFunc();
        int nb_col(char *av);
        int nb_lines(char *av);
        char **map_in_str(char *av);
        int verify_rooms(char **pos_file);
        int verify_boat_order(char **pos_file);
        int verify_boats_file(char **argv, int argc);
        int verify_lenght(char **pos_file);
        int verify_x_y(char **pos_file);
    private:
        
};