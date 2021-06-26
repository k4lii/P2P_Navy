/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** init_matrix
*/

#include <fcntl.h>
#include <unistd.h>
#include "init_boat.c"
#include "define.h"

int is_boat(int x, int y, char **map)
{
    x += 1;
    y *= 2;
    if (map[x][y] >= '1' && map[x][y] <= '8' || map[x][y] == 'x')
        return (1);
    return (0);
}

t_matrix init_matrix(int argc, char **argv, int player)
{
    t_matrix matrix;

    matrix.map = create_2d_str(argv, argc);
    matrix.enemy_map = create_2d_str(argv, argc);
    init_boat(argv[player], matrix.map);
    return (matrix);
}

char *convert_signum_to_norm(int nb)
{
    char *nb_str = malloc(sizeof(char) * 4);
    char *str;
    char *new_str = malloc(sizeof(char) * 4);

    str = my_itoa(nb, nb_str);
    new_str[0] += str[0] += 16;
    new_str[1] = str[1];
    return (new_str);
}

int convert_norm_to_signum(char *choice)
{
    char *nb_str = malloc(sizeof(char) * 4);
    int new_str = 0;

    new_str = (choice[0] - 64) * 10;
    new_str += choice[1] - 48;
    return (new_str);
}

void convert_sig_to_coordonate(int nb, int *x, int *y)
{
    char *nb_str = malloc(sizeof(char) * 4);
    char *str;

    *x = 0;
    *y = 0;
    str = my_itoa(nb, nb_str);
    *y = str[0] - 48;
    *x = str[1] - 48;
}