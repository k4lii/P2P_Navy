#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#include <vector>

typedef struct matrix {
    std::vector<std::string> map;
    std::vector<std::string> enemy_map;
} t_matrix;

#define FILE_LEN 33
#define LINE_LEN 7

class InitMaps
{
    public:
        InitMaps();
        ~InitMaps();
        int is_boat(int x, int y, std::vector<std::string> map);
        t_matrix init_matrix(char *path);
    private:
        void draw_boat(char *line_buffer, std::vector<std::string> &map);
        int init_boat(char *filepath, std::vector<std::string> &map);
        int get_x(char c, std::vector<std::string> map);
        int get_y(char c, std::vector<std::string> map);
        void fill_navy_str(std::vector<std::string> &map);
        char **create_2d_str(int x_size, int y_size);
};