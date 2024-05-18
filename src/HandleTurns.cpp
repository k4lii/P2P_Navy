#include "HandleTurns.hpp"
#include "colors.hpp"
#include <iostream>
#include <regex>

HandleTurns::HandleTurns(bool is_server, Network &net)
    : is_server(is_server), net(net), is_my_turn(is_server) {
    initscr();             // Start ncurses mode
    cbreak();              // Disable line buffering
    keypad(stdscr, TRUE);  // Enable F1, F2 etc.
    echo();                // Enable echoing of typed characters
    curs_set(0);           // Hide the cursor
    start_color();         // Start color functionality
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);

    printw("HandleTurns initialized. Is server: %s\n", is_server ? "true" : "false");
    refresh();
}

HandleTurns::~HandleTurns() {
    endwin();  // End ncurses mode
    std::cout << "HandleTurns destroyed" << std::endl;
}

void HandleTurns::player_management(int argc, char **argv, std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix) {
    while (true) {
        if (is_my_turn) {
            attack(myMatrix, enemyMatrix, argv);
        } else {
            printw("Waiting for enemy's attack...\n");
            refresh();
            defense(myMatrix, enemyMatrix, argv);
        }
        is_my_turn = !is_my_turn;
    }
}

void HandleTurns::attack(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv) {
    std::string user_choice;
    std::regex position_regex("^[A-H][1-9]$");

    while (true) {
        print_boards(myMatrix, enemyMatrix);
        printw("[ATTACK] (format: A1, B2, etc.) = ");
        refresh();
        char input[3];
        getnstr(input, 3);
        user_choice = input;

        if (!std::regex_match(user_choice, position_regex)) {
            show_error_popup("Invalid input. Please enter a valid position (e.g., A1, B2, etc.).");
            continue;
        }

        if (!net.is_connected()) {
            show_error_popup("No connection available to send message.");
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
                printw("%s : hit!\n", user_choice.c_str());
                enemyMatrix[row][col] = 'X';
            } else if (response == "0") {
                printw("%s : missed\n", user_choice.c_str());
                enemyMatrix[row][col] = 'o';
            } else {
                show_error_popup("Invalid response from server.");
            }
            break;
        } else {
            show_error_popup("No connection available to receive message.");
            is_my_turn = true;
            return;
        }
    }
}

void HandleTurns::defense(std::vector<std::string> &myMatrix, std::vector<std::string> &enemyMatrix, char **argv) {
    if (!net.is_connected()) {
        show_error_popup("No connection available to receive message.");
        return;
    }

    std::string attack_pos = net.receive_message();
    if (!attack_pos.empty()) {
        int row = attack_pos[1] - '1';
        int col = 2 * (attack_pos[0] - 'A');
        if (row < 0 || row >= myMatrix.size() || col < 0 || col >= myMatrix[0].size()) {
            net.send_message("error");
            show_error_popup("Invalid position at " + attack_pos);
            return;
        }

        char &cell = myMatrix[row][col];
        if (cell == '.' || cell == 'o') {
            cell = 'o';
            printw("Miss at %s\n", attack_pos.c_str());
            net.send_message("0");
        } else {
            cell = 'X';
            printw("Hit at %s\n", attack_pos.c_str());
            net.send_message("1");
        }
        print_boards(myMatrix, enemyMatrix);
    }
}

void HandleTurns::print_boards(const std::vector<std::string> &myMatrix, const std::vector<std::string> &enemyMatrix) {
    auto print_board = [](const std::vector<std::string> &matrix, const std::string &title) {
        printw("%s\n", title.c_str());
        printw(" | A B C D E F G H\n");
        printw("-+----------------\n");
        for (int i = 0; i < 9; ++i) { // Display up to the 9th row only
            printw("%d|", i + 1);
            for (int j = 0; j < matrix[i].length(); j += 2) {
                char displayChar = matrix[i][j];
                if (displayChar == 'X') {
                    attron(COLOR_PAIR(1));
                    printw("%c ", displayChar);
                    attroff(COLOR_PAIR(1));
                } else if (displayChar == 'o') {
                    attron(COLOR_PAIR(2));
                    printw("%c ", displayChar);
                    attroff(COLOR_PAIR(2));
                } else {
                    printw("%c ", displayChar);
                }
            }
            printw("\n");
        }
    };

    clear();
    print_board(myMatrix, "My Positions:");
    printw("\n");
    print_board(enemyMatrix, "Enemy's Positions:");
    refresh();
}

void HandleTurns::show_error_popup(const std::string &message) {
    int height = 5;
    int width = message.length() + 4;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *popup_win = newwin(height, width, start_y, start_x);
    box(popup_win, 0, 0);
    mvwprintw(popup_win, 2, 2, "%s", message.c_str());
    wrefresh(popup_win);
    wgetch(popup_win); // Wait for user to press a key
    delwin(popup_win);
}
