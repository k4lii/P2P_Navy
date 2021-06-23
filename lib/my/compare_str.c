/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** compare_str
*/

#include "../../include/my.h"
#include <stdlib.h>

int compare_str(char *argv1, char *argv2)
{
    int nb = 0;
    int size_str1 = my_strlen(argv1);
    int x = 0;
    int y = 0;

    for (x; argv2[x] != '\0'; x++) {
        if (argv2[x] == argv1[y]) {
            nb++;
            y++;
        }
    }
    if (nb != size_str1)
        return (0);
    else if (nb == size_str1)
        return (1);
    return (0);
}
