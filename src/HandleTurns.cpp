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