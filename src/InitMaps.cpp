/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** init_matrix
*/

#include "InitMaps.hpp"

InitMaps::InitMaps(){}
InitMaps::~InitMaps(){}

int InitMaps::is_boat(int x, int y, std::vector<std::string> map)
{
    x += 1;
    y *= 2;
    if ((map[x].at(y) >= '1' && map[x].at(y) <= '8') || (map[x].at(y) == 'x'))
        return (1);
    return (0);
}

void InitMaps::fill_navy_str(std::vector<std::string> &map)
{
    int var = 0;

    for (int x = 0; x != 10; x++) {
        for (int y = 0; y != 17; y++) {
            if (y % 2)
                map[x].at(y) = ' ';
            else
                map[x].at(y) = '.';
        }
    }
    map[0].at(0) = ' ';
    map[0].at(0) = '|';
    for (int y = 2; y != 18; y++) {
        map[0].at(y) = 65 + var;
        y++;
        map[0].at(y) = ' ';
        var += 1;
    }
    map[0].at(17) = '\0';

    var = 0;
    for (int y = 0; y != 17; y++)
        map[1].at(y) = '-';
    map[1].at(1) = '+';
    for (int y = 2; y != 10; y++) {
        map[y].at(0) = 49 + var;
        var += 1;
        map[y].at(1) = '|';
    }
    for (int x = 0; x != 10; x++)
        map[x].pop_back();
}

int InitMaps::init_boat(char *filepath, std::vector<std::string> &map)
{
    
    int fd = open(filepath, O_RDONLY);
    char *file_buffer = (char *) malloc(sizeof(char) * FILE_LEN);
    char *line_buffer = (char *) malloc(sizeof(char) * LINE_LEN);
    int line_buffer_i = 0;

    read(fd, file_buffer, FILE_LEN);
    close(fd);
    for (int i = 0; file_buffer[i]; i++) {
        if (file_buffer[i] == '\n') {
            line_buffer_i = 0;
            // std::cout << file_buffer[i] << std::endl;
            draw_boat(line_buffer, map);
            continue;
        }
        line_buffer[line_buffer_i] = file_buffer[i];
        line_buffer_i++;
    }
    // std::cout << "after fd " << std::endl;
    draw_boat(line_buffer, map);
    return (0);
}

void InitMaps::draw_boat(char *line_buffer, std::vector<std::string> &map)
{
    int x1 = get_x(line_buffer[2], map);
    int y1 = get_y(line_buffer[3], map);
    int x2 = get_x(line_buffer[5], map);
    int y2 = get_y(line_buffer[6], map);

    if (x1 == x2) {
        for (; y1 < y2; y1++)
            map[y1][x1] = line_buffer[0];
    }
    else if (y1 == y2) {
        for (; x1 < x2; x1++) {
            if (x1 % 2 == 0)
                map[y1][x1] = line_buffer[0];
        }
    }
    map[y1][x1] = line_buffer[0];
}

t_matrix InitMaps::init_matrix(char *path)
{
    t_matrix matrix;
    for (int x = 0; x != 10; x++) {
        matrix.map.push_back("..................");
        matrix.enemy_map.push_back("..................");
    }
    fill_navy_str(matrix.map);
    fill_navy_str(matrix.enemy_map);
    init_boat(path, matrix.map);
    return (matrix);
}

int InitMaps::get_x(char c, std::vector<std::string> map)
{
    for (int i = 0; i < 18; i++) {
        if (map[0][i] == c)
            return (i);
    }
    return -1;
}

int InitMaps::get_y(char c, std::vector<std::string> map)
{
    for (int i = 0; i < 10; i++) {
        if (map[i][0] == c)
            return (i);
    }
    return -1;
}