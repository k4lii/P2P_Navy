/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** function2
*/

int verify_rooms(char **pos_file)
{
    int nb = 0;

    for (int y = 0; y != 4; y++) {
        if (pos_file[y][0] == '2')
            nb += 2;
        if (pos_file[y][0] == '3')
            nb += 3;
        if (pos_file[y][0] == '4')
            nb += 4;
        if (pos_file[y][0] == '4')
            nb += 5;
    }
    if (nb < 14 || nb > 14)
        return (84);
    else if (nb == 14)
        return (0);
}

int verify_boat_order(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (pos_file[y][2] > pos_file[y][5])
            return (84);
        if (pos_file[y][3] > pos_file[y][6])
            return (84);
    }
}

int verify_lenght(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (my_strlen(pos_file[y]) > 8 || my_strlen(pos_file[y]) < 6)
            return (84);
    }
    return (0);
}

int verify_x_y(char **pos_file)
{
    int nb = 0;

    for (int y = 0; y != 4; y++) {
        if (pos_file[y][2] >= 'A' && pos_file[y][2] <= 'H')
            nb++;
        if (pos_file[y][3] >= '1' && pos_file[y][3] <= '8')
            nb++;
        if (pos_file[y][5] >= 'A' && pos_file[y][5] <= 'H')
            nb++;
        if (pos_file[y][6] >= '1' && pos_file[y][6] <= '8')
            nb++;
    }
    if (nb > 16 || nb < 16)
        return (84);
    else if (nb == 16)
        return (0);
}
