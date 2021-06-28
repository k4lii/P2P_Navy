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
    std::string receive;
    std::string user_choice;

    user_choice = user_entry_attack(); //std::cin and verify if positions are corrects
    usleep(100000); //wait to let initialize server/client
    this->net.Send(user_choice, "127.0.0.1", 9999); //send to server
    receive = this->net.Receive(9999); //receive data -> give if attack hit or not
    //receive receive 1 or 2 from defense if hit or not to update ennemy map
    std::cout << "receive->"<< receive << std::endl;
    if (receive == "1\n") {
        std::cout << "hit" << std::endl;
        enemy_map[receive.at(0) + 1][receive.at(1) *= 2] = 'x';
    }
    else if (receive == "0\n") {
        std::cout << "missed" << std::endl;
        enemy_map[receive.at(0) + 1][receive.at(1) *= 2] = 'o';
    }
}

void HandleTurns::defense(char **map)
{
    std::string receive;

    std::cout << "waiting for enemy's attack..." << std::endl;
    receive = this->net.Receive(9999);
    std::cout << "receive->"<< receive << std::endl;
    if (this->map.is_boat(receive.at(0), receive.at(1), map) == 1) {
        usleep(10000);
        net.Send("1\n", "127.0.0.1", 9999);
        std::cout << ": hit" << std::endl;
        map[receive.at(0) + 1][receive.at(1) *= 2] = 'x';
    }
    else if (this->map.is_boat(receive.at(0), receive.at(1), map) == 0) {
        usleep(10000);
        net.Send("0\n", "127.0.0.1", 9999);
        std::cout << ": missed" << std::endl;
        map[receive.at(0) + 1][receive.at(1) *= 2] = 'o';
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
    if (nb_map == 14) {
        std::cout << "Enemy win" << std::endl;
        exit(0);
    }
    if (nb_enemy_map == 14) {
        std::cout << "You win" << std::endl;
        exit(0);
    }
    return 0;
}

int HandleTurns::player_managment(int argc, char **map, char **enemy_map)
{
    print_navy(map, enemy_map);
    while (1) {
        //verifier si la connexion est bien etablie
        if(argc == 3){ // if player 1 -> attack
            attack(enemy_map);
            defense(map);
        } else if (argc == 2) { // if player 2 -> defense
            defense(map);
            attack(enemy_map);
        }
        print_navy(map, enemy_map);
        win_lose(map, enemy_map);
    }
}

void HandleTurns::print_navy(char **map, char **enemy_map)
{
    std::cout << "\nmy positions:\n" << std::endl;
    for (int y = 0; y != 10 ; y++)
        std::cout << map[y] << std::endl;
    std::cout << "\nenemy's positions:\n" << std::endl;
    for (int y = 0; y != 10 ; y++)
        std::cout << enemy_map[y] << std::endl;
}