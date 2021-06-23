/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_strcat
*/

void my_strcat(char *dest, char const *src)
{
    int dest_lenght = 0;

    for (dest_lenght = 0; dest[dest_lenght] != '\0'; dest_lenght++);
        for (int i = 0; src[i] != '\0'; i++, dest_lenght++)
            dest[dest_lenght] = src[i];
    dest[dest_lenght] = '\0';
}
