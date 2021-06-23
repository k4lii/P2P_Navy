/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** fill_navy_str_2
*/

void fill_navy_str_2(char **map)
{
    int var = 0;
    for (int x = 0; x != 17; x++)
        map[1][x] = '-';
    map[1][1] = '+';
    for (int y = 2; y != 10; y++) {
        map[y][0] = 49 + var;
        var += 1;
        map[y][1] = '|';
    }
}