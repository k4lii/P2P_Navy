#include "HandleTurns.hpp"

HandleTurns::HandleTurns(){}
HandleTurns::~HandleTurns(){}

int HandleTurns::verify_user_choice_error(std::string choice)
{
    if (choice.size() > 2 ) {
        std::cout << "forbidden position" << std::endl;
        return (0);
    }
    if (choice.at(1) < '1' || choice.at(1) > '8') {
        std::cout << "forbidden position" << std::endl;
        return (0);
    }
    if (choice.at(0) < 'A' || choice.at(0) > 'H') {
        std::cout << "forbidden position" << std::endl;
        return (0);
    }
    return (1);
}

std::string HandleTurns::user_entry_attack()
{
    std::string user_choice;
    do {
        user_choice.clear();
        std::cout << "[ATTACK]=";
        std::cin >> user_choice;
        } while (verify_user_choice_error(user_choice) != 1);
    return(user_choice);
}

t_pos HandleTurns::data_to_position(std::string data, std::vector<std::string> map)
{
    t_pos pos = {0,0,0};

    for(long unsigned int x = 2; x != map[0].size(); x++) {
        if(map[0].at(x) == data.at(0)) {
            pos.x = x;
            for(long unsigned int y = 2; y != map.size(); y++) {
                if(map[y].at(0) == data.at(1)){
                    pos.y = y;
                    pos.status = 1;
                }
            }
        }
    }
    return (pos);
}

void HandleTurns::attack(std::vector<std::string> &enemy_map, char **argv)
{
    std::string receive;
    std::string user_choice;
    std::string ip(argv[3]);

    user_choice = user_entry_attack(); //std::cin and verify if positions are corrects
    t_pos pos = data_to_position(user_choice, enemy_map);// get posx and poxy from user choice
    usleep(100000); //wait to let initialize server/client
    this->net.Send(user_choice, ip, atoi(argv[2])); //send to server
    usleep(100000);
    receive = this->net.Receive(atoi(argv[2])); //receive data -> receive if attack hit or not 1 or 0
    if (receive == "1") {
        std::cout << "hit" << std::endl;
        enemy_map[pos.y].at(pos.x) = 'x';
    } else if (receive == "0") {
        std::cout << user_choice << " : missed" << std::endl;
        enemy_map[pos.y].at(pos.x) = 'o';
    }
}

void HandleTurns::defense(std::vector<std::string> &map, char **argv)
{
    std::string receive;
    std::string ip(argv[3]);
    
    std::cout << "waiting for enemy's attack..." << std::endl;
    receive = this->net.Receive(atoi(argv[2]));
    usleep(100000);

    t_pos pos = data_to_position(receive, map);//get receive posx and posy
    if (this->map.is_boat(pos.x, pos.y, map) == 1) {
        usleep(10000);
        net.Send("1", ip, atoi(argv[2]));
        std::cout << receive << " : hit" << std::endl;
        map[pos.y].at(pos.x) = 'x';
    } else if (this->map.is_boat(pos.x, pos.y, map) == 0) {
        usleep(10000);
        net.Send("0", ip, atoi(argv[2]));
        std::cout << receive << " : missed" << std::endl;
        map[pos.y].at(pos.x) = 'o';
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
        return(1);
    }
    if (nb_enemy_map == 14) {
        std::cout << "You win" << std::endl;
        return(1);
    }
    return 0;
}

int HandleTurns::player_managment(int argc, char **argv, t_matrix matrix)
{
    //verifier si la connexion est bien etablie
    print_navy(matrix);
    while (1) {
        if(argc == 5){ // if player 1 -> attack
            attack(matrix.enemy_map, argv);
            defense(matrix.map, argv);
        } else if (argc == 4) { // if player 2 -> defense
            defense(matrix.map, argv);
            attack(matrix.enemy_map, argv);
        }
        if(win_lose(matrix) == 1)
            return 0;
        print_navy(matrix);
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