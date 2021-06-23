/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_strlen_int
*/

int my_strlen_int(int nb)
{
    int nb_size = 1;
    int nb_tempo = nb;

    while (nb_tempo >= 10) {
        nb_tempo = nb_tempo / 10;
        nb_size++;
    }
    return (nb_size);
}
