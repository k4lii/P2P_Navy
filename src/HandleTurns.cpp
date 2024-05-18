#include "HandleTurns.hpp"
#include "colors.hpp"
#include <iostream>
#include <regex>

HandleTurns::HandleTurns(bool is_server, Network &net)
    : is_server(is_server), net(net), is_my_turn(is_server) {
    std::cout << "HandleTurns initialized. Is server: " << std::boolalpha << is_server << std::endl;
}

HandleTurns::~HandleTurns() {
    std::cout << "HandleTurns destroyed" << std::endl;
}

void HandleTurns::player_management(int argc, char **argv, std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix) {
    std::cout << "Player management started" << std::endl;
    while (true) {
        if (is_my_turn) {
            attack(myMatrix, enemyMatrix, argv);
        } else {
            std::cout << "Waiting for enemy's attack..." << std::endl;
            defense(myMatrix, enemyMatrix, argv);
        }
        is_my_turn = !is_my_turn;
    }
    std::cout << "Player management ended" << std::endl;
}

void HandleTurns::attack(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv) {
    std::string user_choice;
    std::regex position_regex("^[A-H][1-8]$"); // Valid input format

    while (true) {
        print_boards(myMatrix, enemyMatrix);
        std::cout << "[ATTACK] (format: A1, B2, etc.) = ";
        std::cin >> user_choice;

        if (!std::regex_match(user_choice, position_regex)) {
            std::cerr << "Invalid input. Please enter a valid position (e.g., A1, B2, etc.)." << std::endl;
            continue;
        }

        if (!net.is_connected()) {
            std::cerr << "No connection available to send message" << std::endl;
            is_my_turn = true;
            return;
        }

        net.send_message(user_choice);
        std::string response;
        if (net.is_connected()) {
            response = net.receive_message();
            int row = user_choice[1] - '1';
            int col = 2 * (user_choice[0] - 'A');
            if (response == "1") {
                std::cout << user_choice << " : hit!" << std::endl;
                enemyMatrix[row][col] = 'X';
            } else if (response == "0") {
                std::cout << user_choice << " : missed" << std::endl;
                enemyMatrix[row][col] = 'o';
            } else {
                std::cerr << "Invalid response from server" << std::endl;
            }
            break;  // Correct placement of break
        } else {
            std::cerr << "No connection available to receive message" << std::endl;
            is_my_turn = true;
            return;
        }
    }
}

void HandleTurns::defense(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv) {
    if (!net.is_connected()) {
        std::cerr << "No connection available to receive message" << std::endl;
        return;
    }

    std::string attack_pos = net.receive_message();
    if (!attack_pos.empty()) {
        int row = attack_pos[1] - '1';
        int col = 2 * (attack_pos[0] - 'A');
        if (row < 0 || row >= myMatrix.size() || col < 0 || col >= myMatrix[0].size()) {
            net.send_message("error");
            std::cerr << "Invalid position at " << attack_pos << std::endl;
            return;
        }

        char &cell = myMatrix[row][col];
        if (cell == '.' || cell == 'o') {
            cell = 'o';
            std::cout << "Miss at " << attack_pos << std::endl;
            net.send_message("0");
        } else {
            cell = 'X';
            std::cout << "Hit at " << attack_pos << std::endl;
            net.send_message("1");
        }
        print_boards(myMatrix, enemyMatrix);
    }
}

void HandleTurns::print_boards(const std::vector<std::string> &myMatrix, const std::vector<std::string> &enemyMatrix) {
    auto print_board = [](const std::vector<std::string> &matrix, const std::string &title) {
        std::cout << title << std::endl;
        std::cout << " | A B C D E F G H" << std::endl;  // Headers for columns
        std::cout << "-+----------------" << std::endl;
        for (int i = 0; i < matrix.size(); ++i) {
            std::cout << i + 1 << (i < 9 ? " " : ""); // Adjust space for single digit
            std::cout << "|";
            for (int j = 0; j < matrix[i].length(); ++j) {
                if (j % 2 != 0) continue; // Skipping spaces between columns

                char displayChar = matrix[i][j];
                switch (displayChar) {
                    case 'X':
                        std::cout << RED << displayChar << RESET;
                        break;
                    case 'o':
                        std::cout << BLUE << displayChar << RESET;
                        break;
                    default:
                        std::cout << displayChar;
                        break;
                }
                std::cout << " "; // Ensuring a space after each character for consistent spacing
            }
            std::cout << std::endl;
        }
    };

    print_board(myMatrix, "My Positions:");
    std::cout << std::endl;
    print_board(enemyMatrix, "Enemy's Positions:");
}
