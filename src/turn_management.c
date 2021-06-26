/*
** EPITECH PROJECT, 2019
** undefined
** File description:
** turn_management
*/

int read_error_gestion(char *buffer)
{
    buffer[2] = '\0';

    if (buffer[1] < '1' || buffer[1] > '8') {
        my_putstr("wrong position");
        return (4);
    }
    if (buffer[0] < 'A' || buffer[0] > 'H') {
        my_putstr("wrong position");
        return (4);
    }
    return (1);
}

void print_error_attack(char *choice)
{
    my_putstr("\nattack: ");
    read(0, choice, 100);
    while (read_error_gestion(choice) != 1) {
        my_putstr("\nattack: ");
        read(0, choice, 100);
    }
}

void attack(char *pid, char **enemy_map)
{
    int receive_value;
    char *choice = malloc(sizeof(char) * 100);
    int x;
    int y;

    print_error_attack(choice);
    usleep(100000);
    send_user(convert_norm_to_signum(choice), pid);
    my_putstr(choice);
    my_putstr(": ");
    receive(&receive_value);
    convert_sig_to_coordonate(convert_norm_to_signum(choice), &x, &y);
    if (receive_value >= 1) {
        my_putstr("hit\n");
        enemy_map[x + 1][(y *= 2)] = 'x';
    }
    else if (receive_value == 0) {
        my_putstr("missed\n");
        enemy_map[x + 1][y *= 2] = 'o';
    }
}

void defense(char *pid, char **map)
{
    int x;
    int y;
    int receive_value = 0;

    my_putstr("\nwaiting for enemy's attack...\n");
    receive(&receive_value);
    convert_sig_to_coordonate(receive_value, &x, &y);
    my_putstr(convert_signum_to_norm(receive_value));
    if (is_boat(x, y, map) == 1) {
        usleep(10000);
        send_user(10, pid);
        my_putstr(": hit\n");
        map[x + 1][y *= 2] = 'x';
    }
    else if (is_boat(x, y, map) == 0) {
        usleep(10000);
        send_user(0, pid);
        my_putstr(": missed\n");
        map[x + 1][y *= 2] = 'o';
    }
}