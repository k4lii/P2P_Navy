/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** fill_navy_str
*/

#include "../../include/my.h"

void fill_navy_str(char **map)
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
    fill_navy_str_2(map);
}