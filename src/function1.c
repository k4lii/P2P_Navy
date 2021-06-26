/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** little_function
*/

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

int nb_col(char *av)
{
    int li = 0;
    int fd;
    char buf[1];
    int size;

    fd = open(av, O_RDONLY);
    for (int i = 0; read(fd, buf, 1) != 0; i++) {
        if (buf[0] == '\n')
            li++;
    }
    li++;
    close(fd);
    return (li);
}

int nb_lines(char *av)
{
    int co_size = 1;
    int co_save = 0;
    int fd;
    char buf[1];
    int size;

    fd = open(av, O_RDONLY);
    for (int i = 0; read(fd, buf, 1) != 0; i++) {
        co_size++;
        if (buf[0] == '\n') {
            co_size ++;
            if(co_size > co_save)
                co_save = co_size;
            co_size = 0;
        }
    }
    close(fd);
    return (co_save);
}

char **map_in_str(char *av)
{
    int li = nb_lines(av);
    int size_co = nb_col(av);
    int l = 0;
    int c = 0;
    char **lettre = malloc(sizeof(char *) * li + 1);
    int fd = open(av, O_RDONLY);
    char buf[1];

    for (l; l < li; l++)
        lettre[l] = malloc(sizeof(char) * size_co + 1);
    for (int l = 0; read(fd, buf, 1) != 0; c++) {
        lettre[l][c] = buf[0];
        if (lettre[l][c] == '\n') {
            c = -1;
            l++;
        }
    }
    close(fd);
    return (lettre); 
}