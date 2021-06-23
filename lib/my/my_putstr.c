/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_putstr
*/

#include "../../include/my.h"

int my_putstr(char const *str)
{
    int i = 0;

    while (str[i] != '\0') {
        my_putchar(str[i]);
        i++;
    }
}
