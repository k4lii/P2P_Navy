/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_revstr
*/

#include "../../include/my.h"

char *my_revstr(char *str)
{
    int i = 0;
    int count = 0;
    int trans = 0;

    while (str[count] != '\0')
        count++;
    count--;
    while (i < count) {
        trans = str[i];
        str[i] = str[count];
        str[count] = trans;
        i++;
        count--;
    }
    return (str);
}
