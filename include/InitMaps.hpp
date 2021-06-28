#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include "struct.hpp"

#define FILE_LEN 33
#define LINE_LEN 7

class InitMaps
{
    public:
        InitMaps();
        ~InitMaps();
        int is_boat(int x, int y, char **map);
        t_matrix init_matrix(int argc, char **argv, int player);
    private:
        void draw_boat(char *line_buffer, char **map);
        int init_boat(char *filepath, char **map);
        int get_x(char c, char **map);
        int get_y(char c, char **map);
        void fill_navy_str(char **map);
        char **create_2d_str(char **argv, int argc);
};