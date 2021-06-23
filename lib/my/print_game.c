/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** print_game
*/

#include "../../include/my.h"

void print_navy(char **map, char **enemy_map)
{
    my_putstr("\nmy positions:\n");
    for (int y = 0; y != 10 ; y++) {
        my_putstr(map[y]);
        my_putchar('\n');
    }
    my_putstr("\nenemy's positions:\n");
    for (int y = 0; y != 10 ; y++) {
        my_putstr(enemy_map[y]);
        my_putchar('\n');
    }
}