/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_strcpy
*/

void my_strcpy(char *dest, char const *src)
{
    int i = 0;

    while (src[i] != '\0') {
        dest[i] = src[i];
        i++;
    }
}
