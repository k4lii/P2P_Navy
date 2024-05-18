#include "HandleTurns.hpp"
#include <iostream>

HandleTurns::HandleTurns(bool is_server, Network &net) : is_server(is_server), net(net) {
    std::cout << "HandleTurns initialized. Is server: " << std::boolalpha << is_server << std::endl;
}

HandleTurns::~HandleTurns() {
    std::cout << "HandleTurns destroyed" << std::endl;
}

void HandleTurns::player_management(int argc, char **argv, std::vector<std::string> &matrix) {
    std::cout << "Player management started" << std::endl;
    if (is_server) {
        defense(matrix, argv);
    } else {
        attack(matrix, argv);
    }
    std::cout << "Player management ended" << std::endl;
}

void HandleTurns::attack(std::vector<std::string> &matrix, char **argv) {
    std::string user_choice;
    while (true) {
        std::cout << "[ATTACK] (format: A1, B2, etc.) =";
        std::cin >> user_choice;
        if (net.is_connected()) {
            net.send_message(user_choice);
        } else {
            std::cerr << "No connection available to send message" << std::endl;
        }

        std::string receive;
        if (net.is_connected()) {
            receive = net.receive_message();
        } else {
            std::cerr << "No connection available to receive message" << std::endl;
        }

        if (receive == "1") {
            std::cout << user_choice << " : hit!" << std::endl;
        } else if (receive == "0") {
            std::cout << user_choice << " : missed" << std::endl;
        } else {
            std::cerr << "Invalid response" << std::endl;
        }
    }
}

void HandleTurns::defense(std::vector<std::string> &matrix, char **argv) {
    std::string receive;
    while (true) {
        if (net.is_connected()) {
            receive = net.receive_message();
        } else {
            std::cerr << "No connection available to receive message" << std::endl;
        }

        if (receive.empty()) {
            continue;
        }

        int row = receive[1] - '1';
        int col = receive[0] - 'A';
        if (matrix[row][col] == '.') {
            matrix[row][col] = '0';
            std::cout << "Miss!" << std::endl;
            if (net.is_connected()) {
                net.send_message("0");
            } else {
                std::cerr << "No connection available to send message" << std::endl;
            }
        } else if (matrix[row][col] >= '1' && matrix[row][col] <= '9') {
            matrix[row][col] = 'X';
            std::cout << "Hit!" << std::endl;
            if (net.is_connected()) {
                net.send_message("1");
            } else {
                std::cerr << "No connection available to send message" << std::endl;
            }
        } else {
            std::cerr << "Invalid position" << std::endl;
        }
    }
}
