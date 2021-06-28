#include "HandleTurns.hpp"

HandleTurns::HandleTurns(){}
HandleTurns::~HandleTurns(){}

int HandleTurns::verify_user_choice_error(std::string choice)
{
    if (choice.at(1) < '1' || choice.at(1) > '8') {
        std::cout << "wrong position" << std::endl;
        return (4);
    }
    if (choice.at(0) < 'A' || choice.at(0) > 'H') {
        std::cout << "wrong position" << std::endl;
        return (4);
    }
    return (1);
}

std::string HandleTurns::user_entry_attack()
{
    std::string user_choice;
    do {
        user_choice.clear();
        std::cout << "attack: " << std::endl;
        std::cin >> user_choice;
        } while (verify_user_choice_error(user_choice) != 1);
    return(user_choice);
}

void HandleTurns::attack(char **enemy_map)
{
    std::string receive_value;
    std::string user_choice;

    user_choice = user_entry_attack(); //std::cin and verify if positions are corrects
    usleep(100000); //wait to let initialize server/client
    net.Send(user_choice, "127.0.0.1", 9999); //send to server
    receive_value = net.Receive(); //receive data -> give if attack hit or not
    std::cout << receive_value << ": " << std::endl;
    if (receive_value >= 1) {
        std::cout << "hit" << std::endl;
        enemy_map[receive_value.at(0) + 1][(receive_value.at(1) *= 2)] = 'x';
    }
    else if (receive_value == 0) {
        std::cout << "missed" << std::endl;
        enemy_map[x + 1][y *= 2] = 'o';
    }
}

void HandleTurns::defense(char **map)
{
    int x;
    int y;
    std::strind receive;
    int receive_value = 0;

    std::cout << "waiting for enemy's attack..." << std::endl;
    receive = net.Receive()
    // receive(&receive_value);
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
        std::cout << "Enemy win" << std::endl;
        exit(0);
    if (nb_enemy_map == 14)
        std::cout << "You win" << std::endl;
        exit(0);
    return 0;
}

int HandleTurns::player(int argc, char **map, char **enemy_map)
{
    int receive_value = 0;

    print_navy(map, enemy_map);
    while (1) {
        if(argc == 3){ // if player 1 -> attack
            attack(enemy_map);
        } else if (argc == 2) { // if player 2 -> defense
            defense(map);
        }
        print_navy(map, enemy_map);
        win_lose(map, enemy_map);
    }
}