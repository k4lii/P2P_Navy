/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** receive
*/
#include <stdlib.h>
#include <unistd.h>
#include "include/my.h"
#include <sys/types.h>
#include <signal.h>
#include <fcntl.h>

int status = 0;

void test2(int a)
{
    status = 1;
}

void test(int a)
{
    status = 2;
}

void receive(int *valeur)
{
    *valeur = 0;
    status = 0;
    while (1) {
        signal(SIGUSR1, test);
        signal(SIGUSR2, test2);
        if (status == 2) {
            *valeur += 1;
            status = 0;
        }
        if (status == 1)
            break;
    }
}

void send_user(int nb_value, char *pid)
{
    int x = 0;

    while (x != nb_value) {
        kill(my_getnbr(pid), SIGUSR1);
        usleep(100);
        x++;
    }
    kill(my_getnbr(pid), SIGUSR2);
}

void print_pid(int player)
{
    my_putstr("my_pid : ");
    my_put_nbr(getpid());
    my_putchar('\n');
    if (player == 1)
        my_putstr("waiting for enemy connection...\n");
}