#include <ncurses.h>
#undef timeout  // Undefine the timeout macro to avoid conflicts with Boost
#include <boost/asio.hpp>
#include "HandleTurns.hpp"
#include "colors.hpp"
#include <iostream>
#include <regex>

HandleTurns::HandleTurns(bool is_server, Network &net)
    : is_server(is_server), net(net), is_my_turn(is_server) {
    initscr();
    cbreak();
    keypad(stdscr, TRUE);
    echo();
    curs_set(1);
    start_color();
    init_pair(1, COLOR_RED, COLOR_BLACK);
    init_pair(2, COLOR_BLUE, COLOR_BLACK);
    init_pair(3, COLOR_CYAN, COLOR_BLACK);
}

HandleTurns::~HandleTurns() {
    endwin();
}

void HandleTurns::draw_borders(WINDOW* win, int start_row, int start_col, int num_rows, int num_cols) {
    wattron(win, COLOR_PAIR(3));
    box(win, 0, 0);
    mvwprintw(win, 0, (num_cols - strlen(" My Positions ")) / 2, " My Positions ");
    wattroff(win, COLOR_PAIR(3));

    for (int row = start_row; row < start_row + num_rows; ++row) {
        for (int col = start_col; col < start_col + num_cols; ++col) {
            mvwaddch(win, row, col, (row == start_row || row == start_row + num_rows - 1) ? ACS_HLINE : (col == start_col || col == start_col + num_cols - 1) ? ACS_VLINE : ' ');
        }
    }
    wrefresh(win);
}

void HandleTurns::print_char_by_type(char displayChar, int y, int x) {
    switch (displayChar) {
        case 'X':
            attron(COLOR_PAIR(1));
            mvprintw(y, x, "%c ", displayChar);
            attroff(COLOR_PAIR(1));
            break;
        case 'o':
            attron(COLOR_PAIR(2));
            mvprintw(y, x, "%c ", displayChar);
            attroff(COLOR_PAIR(2));
            break;
        default:
            mvprintw(y, x, "%c ", displayChar);
            break;
    }
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
        mvprintw(LINES - 2, 0, "[ATTACK] (format: A1, B2, etc.) = ");
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
                mvprintw(LINES - 1, 0, "%s : hit!", user_choice.c_str());
                enemyMatrix[row][col] = 'X';
            } else if (response == "0") {
                mvprintw(LINES - 1, 0, "%s : missed", user_choice.c_str());
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
            mvprintw(LINES - 1, 0, "Miss at %s", attack_pos.c_str());
            net.send_message("0");
        } else {
            cell = 'X';
            mvprintw(LINES - 1, 0, "Hit at %s", attack_pos.c_str());
            net.send_message("1");
        }
        print_boards(myMatrix, enemyMatrix);
    }
}


void HandleTurns::print_boards(const std::vector<std::string> &myMatrix, const std::vector<std::string> &enemyMatrix) {
    clear();
    int left_margin = 10;  // Starting margin for the board
    int top_margin = 3;  // Top margin for headers
    int column_spacing = 4;  // Spacing between columns, increase if more space is needed

    // Calculate the width based on column spacing and the number of columns
    int board_width = column_spacing * 8 + 2; // 8 columns plus some padding, adjust the +2 if more space is needed at the edges

    // Calculate enemy board starting position
    int enemy_left_margin = left_margin + board_width + 10;  // Space between boards

    // Print column headers
    for (int i = 0; i < 8; ++i) {
        mvprintw(top_margin - 2, left_margin + i * column_spacing + 2, "%c", 'A' + i);
        mvprintw(top_margin - 2, enemy_left_margin + i * column_spacing + 2, "%c", 'A' + i);
    }

    // Print the board titles
    mvprintw(top_margin - 1, left_margin, "My Positions:");
    mvprintw(top_margin - 1, enemy_left_margin, "Enemy's Positions:");

    // Draw the borders for each board
    draw_borders(stdscr, top_margin, left_margin, 11, board_width);  // Increase height from 11 if needed
    draw_borders(stdscr, top_margin, enemy_left_margin, 11, board_width);

    // Print the grids
    for (int i = 0; i < 9; ++i) {
        mvprintw(top_margin + i, left_margin - 3, "%d", i + 1);
        mvprintw(top_margin + i, enemy_left_margin - 3, "%d", i + 1);
        for (int j = 0; j < 8; ++j) {
            print_char_by_type(myMatrix[i][2 * j], top_margin + i, left_margin + j * column_spacing + 2);
            print_char_by_type(enemyMatrix[i][2 * j], top_margin + i, enemy_left_margin + j * column_spacing + 2);
        }
    }

    refresh();
}





void HandleTurns::show_error_popup(const std::string &message) {
    int height = 5;
    int width = message.length() + 4;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *popup_win = newwin(height, width, start_y, start_x);
    wattron(popup_win, COLOR_PAIR(4));
    box(popup_win, 0, 0);
    wattroff(popup_win, COLOR_PAIR(4));
    mvwprintw(popup_win, 2, 2, "%s", message.c_str());
    wrefresh(popup_win);
    wgetch(popup_win); // Wait for user to press a key
    delwin(popup_win);
}
