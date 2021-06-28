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

void HandleTurns::attack(std::vector<std::string> &enemy_map)
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
        enemy_map[receive.at(0)].at(receive.at(1)) = 'x';
    }
    else if (receive == "0\n") {
        std::cout << "missed" << std::endl;
        enemy_map[receive.at(0)].at(receive.at(1)) = 'o';
    }
}

void HandleTurns::defense(std::vector<std::string> &map)
{
    std::string receive;

    std::cout << "waiting for enemy's attack..." << std::endl;
    receive = this->net.Receive(9999);
    std::cout << "receive->"<< receive << std::endl;
    if (this->map.is_boat(receive.at(0), receive.at(1), map) == 1) {
        usleep(10000);
        net.Send("1\n", "127.0.0.1", 9999);
        std::cout << ": hit" << std::endl;
        map[receive.at(0)].at(receive.at(1)) = 'x';
        // map[receive.at(0) + 1][receive.at(1) *= 2] = 'x';
    }
    else if (this->map.is_boat(receive.at(0), receive.at(1), map) == 0) {
        usleep(10000);
        net.Send("0\n", "127.0.0.1", 9999);
        std::cout << ": missed" << std::endl;
        map[receive.at(0)].at(receive.at(1)) = 'o';
        //  map[receive.at(0) + 1][receive.at(1) *= 2] = 'o';
    }
}

int HandleTurns::win_lose(t_matrix matrix)
{
    int nb_map = 0;
    int nb_enemy_map = 0;

    for (int y = 2; y != 10; y++) {
        for (int x = 2; x != 17; x++) {
            if (matrix.map[y].at(x) == 'x')
                nb_map += 1;
            if (matrix.enemy_map[y].at(x) == 'x')
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

int HandleTurns::player_managment(int argc, t_matrix matrix)
{
    print_navy(matrix);
    while (1) {
        //verifier si la connexion est bien etablie
        if(argc == 3){ // if player 1 -> attack
            attack(matrix.enemy_map);
            defense(matrix.map);
        } else if (argc == 2) { // if player 2 -> defense
            defense(matrix.map);
            attack(matrix.enemy_map);
        }
        print_navy(matrix);
        win_lose(matrix);
    }
    return 0;
}

void HandleTurns::print_navy(t_matrix matrix)
{
    std::cout << "\nmy positions:\n" << std::endl;
    for (long unsigned int y = 0; y != matrix.map.size() ; y++){
        std::cout << matrix.map[y] << std::endl;
    }
    std::cout << "\nenemy's positions:\n" << std::endl;
    for (long unsigned int y = 0; y != matrix.enemy_map.size() ; y++){
        std::cout << matrix.enemy_map[y] << std::endl;
    }
}