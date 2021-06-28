/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** init_matrix
*/

#include "InitMaps.hpp"

InitMaps::InitMaps(){}
InitMaps::~InitMaps(){}

int InitMaps::is_boat(int x, int y, char **map)
{
    x += 1;
    y *= 2;
    if ((map[x][y] >= '1' && map[x][y] <= '8') || (map[x][y] == 'x'))
        return (1);
    return (0);
}

void InitMaps::fill_navy_str(char **map)
{
    int var = 0;

    for (int y = 0; y != 10; y++) {
        for (int x = 0; x != 17; x++) {
            if (x % 2)
                map[y][x] = ' ';
            else
                map[y][x] = '.';
        }
    }
    map[0][0] = ' ';
    map[0][1] = '|';
    for (int x = 2; x != 18; x++) {
        map[0][x] = 65 + var;
        x++;
        map[0][x] = ' ';
        var += 1;
    }
    map[0][17] = '\0';


     var = 0; //-> pas convaincu
    for (int x = 0; x != 17; x++)
        map[1][x] = '-';
    map[1][1] = '+';
    for (int y = 2; y != 10; y++) {
        map[y][0] = 49 + var;
        var += 1;
        map[y][1] = '|';
    }
}

char** InitMaps::create_2d_str(int x_size, int y_size)
{
    char **map = (char **)malloc(sizeof(char *) * 10);

    for (int i = 0; i < y_size; i++)
        map[i] = (char *)malloc(sizeof(char) * x_size);
    fill_navy_str(map);
    return (map);
}

int InitMaps::init_boat(char *filepath, char **map)
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

void InitMaps::draw_boat(char *line_buffer, char **map)
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
//  std::cout << "before allocate create2d" << std::endl;
    matrix.map = create_2d_str(10, 18);
    matrix.enemy_map = create_2d_str(10, 18);
    // std::cout << "after allocate create2d" << std::endl;
    init_boat(path, matrix.map);
    //  std::cout << "after init boat" << std::endl;
    return (matrix);
}

int InitMaps::get_x(char c, char **map)
{
    for (int i = 0; i < 18; i++) {
        if (map[0][i] == c)
            return (i);
    }
    return -1;
}

int InitMaps::get_y(char c, char **map)
{
    for (int i = 0; i < 10; i++) {
        if (map[i][0] == c)
            return (i);
    }
    return -1;
}

// char *convert_signum_to_norm(int nb)
// {
//     char *nb_str = (char *)malloc(sizeof(char) * 4);
//     char *str;
//     char *new_str = (char *)malloc(sizeof(char) * 4);

//     str = my_itoa(nb, nb_str);
//     new_str[0] += str[0] += 16;
//     new_str[1] = str[1];
//     return (new_str);
// }

// int convert_norm_to_signum(char *choice)
// {
//     char *nb_str = (char *)malloc(sizeof(char) * 4);
//     int new_str = 0;

//     new_str = (choice[0] - 64) * 10;
//     new_str += choice[1] - 48;
//     return (new_str);
// }

// void convert_sig_to_coordonate(int nb, int *x, int *y)
// {
//     char *nb_str = (char *)malloc(sizeof(char) * 4);
//     char *str;

//     *x = 0;
//     *y = 0;
//     str = my_itoa(nb, nb_str);
//     *y = str[0] - 48;
//     *x = str[1] - 48;
// }