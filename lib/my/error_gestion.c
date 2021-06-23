/*
** EPITECH PROJECT, 2019
** PSU_my_sokoban_2018
** File description:
** error_gestion
*/

#include "../../include/my.h"

int error_gestion(char **argv, int argc)
{
    if (compare_str("-h", argv[1]) != 0) {
        if (argv[1][1] == 'h' && argv[1][0] == '-') {
            my_putstr("USAGE\n     ./navy [first_player_pid] navy_positi");
            my_putstr("ons\n");
            my_putstr("DESCRIPTION\n     first_player_pid:  only for");
            my_putstr(" the 2nd player.  pid of the first player.\n");
            my_putstr("     navy_positions:  file ");
            my_putstr("representing the positions of the ships.");
        }
        return (0);
    }
    return (1);
}