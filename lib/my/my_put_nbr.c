/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_put_nbr
*/

#include "../../include/my.h"
#include <unistd.h>

int my_put_nbr(int nb)
{
    if (nb > 9)
        my_put_nbr(nb / 10);
    else if (nb < 0) {
        nb *= -1;
        write(1, "-", 1);
        my_put_nbr(nb / 10);
    }
    my_putchar(nb % 10 + '0');
}
