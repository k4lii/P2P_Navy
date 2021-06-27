#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "struct.hpp"

class InitMaps
{
    public:
        InitMaps();
        ~InitMaps();
        int is_boat(int x, int y, char **map);
        void fill_navy_str(char **map);
        char **create_2d_str(char **argv, int argc);
        t_matrix init_matrix(int argc, char **argv, int player);
        void draw_boat(char *line_buffer, char **map);
        int init_boat(char *filepath, char **map);
        int get_x(char c, char **map);
        int get_y(char c, char **map);
};