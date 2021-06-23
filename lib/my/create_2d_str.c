/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** create_2d_str
*/

#include <stdlib.h>
#include "../../include/my.h"

char **create_2d_str(char **argv, int argc)
{
    char **map = malloc(sizeof(char *) * 10);

    for (int i = 0; i < 10; i++)
        map[i] = malloc(sizeof(char) * 18);
    fill_navy_str(map);
    return (map);
}