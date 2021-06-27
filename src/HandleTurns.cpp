#include "HandleTurns.hpp"

HandleTurns::HandleTurns(){}
HandleTurns::~HandleTurns(){}

int HandleTurns::read_error_gestion(char *buffer)
{
    buffer[2] = '\0';

    if (buffer[1] < '1' || buffer[1] > '8') {
        std::cout << "wrong position" << std::endl;
        return (4);
    }
    if (buffer[0] < 'A' || buffer[0] > 'H') {
        std::cout << "wrong position" << std::endl;
        return (4);
    }
    return (1);
}

void HandleTurns::print_error_attack(char *choice)
{
    std::cout << "\nattack: " << std::endl;
    read(0, choice, 100);
    while (read_error_gestion(choice) != 1) {
        std::cout << "attack: " << std::endl;
        read(0, choice, 100);
    }
}

void HandleTurns::attack(char *pid, char **enemy_map)
{
    int receive_value;
    char *choice = (char *)malloc(sizeof(char) * 100);
    int x;
    int y;

    print_error_attack(choice);
    usleep(100000);
    send_user(convert_norm_to_signum(choice), pid);
    std::cout << choice << ": " << std::endl;
    receive(&receive_value);
    convert_sig_to_coordonate(convert_norm_to_signum(choice), &x, &y);
    if (receive_value >= 1) {
        std::cout << "hit" << std::endl;
        enemy_map[x + 1][(y *= 2)] = 'x';
    }
    else if (receive_value == 0) {
        std::cout << "missed" << std::endl;
        enemy_map[x + 1][y *= 2] = 'o';
    }
}

void HandleTurns::defense(char *pid, char **map)
{
    int x;
    int y;
    int receive_value = 0;

    std::cout << "waiting for enemy's attack..." << std::endl;
    receive(&receive_value);
    convert_sig_to_coordonate(receive_value, &x, &y);
    my_putstr(convert_signum_to_norm(receive_value));
    if (is_boat(x, y, map) == 1) {
        usleep(10000);
        send_user(10, pid);
        std::cout << ": hit" << std::endl;
        map[x + 1][y *= 2] = 'x';
    }
    else if (is_boat(x, y, map) == 0) {
        usleep(10000);
        send_user(0, pid);
        std::cout << ": missed" << std::endl;
        map[x + 1][y *= 2] = 'o';
    }
}

void HandleTurns::print_latest_message(int value)
{
    if (value == 1)
        my_putstr("\nEnemy won");
    else if (value == 0)
        my_putstr("\nI won");
}

int HandleTurns::win_lose(char **map, char **enemy_map)
{
    int nb_map = 0;
    int nb_enemy_map = 0;

    for (int y = 2; y != 10; y++) {
        for (int x = 2; x != 17; x++) {
            if (map[y][x] == 'x')
                nb_map += 1;
            if (enemy_map[y][x] == 'x')
                nb_enemy_map += 1;
        }
    }
    if (nb_map == 14)
        return (1);
    if (nb_enemy_map == 14)
        return (0);
    return (2);
}

int HandleTurns::player2(char *str, char **argv, char **map, char **enemy_map)
{
    int receive_value = 0;
    int ret_value = 2;

    usleep(100);
    send_user(my_getnbr(my_itoa(getpid(), str)), argv[1]);
    receive(&receive_value);
    if (receive_value >= 1)
        my_putstr("successfully connected\n");
    print_navy(map, enemy_map);
    while (ret_value > 1) {
        defense(argv[1], map);
        ret_value = win_lose(map, enemy_map);
        if (ret_value == 1 || ret_value == 0) {
            print_navy(map, enemy_map);
            return (ret_value);
        }
        attack(argv[1], enemy_map);
        print_navy(map, enemy_map);
    }
}

int HandleTurns::player1(char *str, int pid_j2, char **map, char **enemy_map)
{
    int receive_value = 0;
    int ret_value = 2;

    // print ip and port
    // receive(&receive_value);
    pid_j2 = receive_value;
    if (receive_value >= 1)
        my_putstr("\nenemy connected\n");
    send_user(10, my_itoa(receive_value, str));
    print_navy(map, enemy_map);
    while (ret_value > 1) {
        attack(my_itoa(pid_j2, str), enemy_map);
        ret_value = win_lose(map, enemy_map);
        if (ret_value == 1 || ret_value == 0) {
            print_navy(map, enemy_map);
            return (ret_value);
        }
        defense(my_itoa(pid_j2, str), map);
        print_navy(map, enemy_map);
    }
}
