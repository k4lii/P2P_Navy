#include "menu.hpp"
#include <ncurses.h>
#include <vector>
#include <string>

void print_menu(WINDOW *menu_win, int highlight, const std::vector<std::string> &choices);

int run_menu() {
    initscr();
    clear();
    noecho();
    cbreak();  // Disable line buffering
    curs_set(0);  // Hide cursor

    int height = 10;
    int width = 40;
    int start_y = (LINES - height) / 2;
    int start_x = (COLS - width) / 2;

    WINDOW *menu_win = newwin(height, width, start_y, start_x);
    keypad(menu_win, TRUE);
    refresh();

    std::vector<std::string> choices = {
        "Start as Server",
        "Start as Client",
        "Exit"
    };
    int choice;
    int highlight = 0;

    while (true) {
        print_menu(menu_win, highlight, choices);
        int c = wgetch(menu_win);
        switch (c) {
            case KEY_UP:
                highlight = (highlight == 0) ? choices.size() - 1 : highlight - 1;
                break;
            case KEY_DOWN:
                highlight = (highlight == choices.size() - 1) ? 0 : highlight + 1;
                break;
            case 10: // Enter key
                choice = highlight;
                break;
            default:
                break;
        }
        if (c == 10) { // Enter key
            break;
        }
    }

    clrtoeol();
    refresh();
    endwin();

    return choice + 1;
}

void print_menu(WINDOW *menu_win, int highlight, const std::vector<std::string> &choices) {
    int x = 2;
    int y = 2;
    box(menu_win, 0, 0);
    for (int i = 0; i < choices.size(); ++i) {
        if (highlight == i) {
            wattron(menu_win, A_REVERSE);
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
            wattroff(menu_win, A_REVERSE);
        } else {
            mvwprintw(menu_win, y, x, "%s", choices[i].c_str());
        }
        ++y;
    }
    wrefresh(menu_win);
}
