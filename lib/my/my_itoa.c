/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_itoa
*/

#include "../../include/my.h"

char *my_itoa(int nb, char *str)
{
    int x;
    int sign;

    if ((sign = nb) < 0)
        nb = -nb;
    x = 0;
    do {
        str[x++] = nb % 10 + '0';
    } while ((nb /= 10) > 0);
    if (sign < 0)
        str[x++] = '-';
    str[x] = '\0';
    return (my_revstr(str));
}
