/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_strlen
*/

int my_strlen(char const *str)
{
    int i = 0;

    while (str[i] != '\0')
        i++;
    return (i);
}
