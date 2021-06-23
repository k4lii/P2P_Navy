/*
** EPITECH PROJECT, 2019
** PSU_my_sokoban_2018
** File description:
** biggest_nb
*/

#include <stdlib.h>

int biggest_nb_2d(int **tab, int argc)
{
    int nb = 0;

    for (int y = 0; y != argc - 1; y++) {
        if (tab[y][0] >= nb)
            for (nb; nb != tab[y][0]; nb++);
    }
    return (nb);
}
