#include <ncurses.h>
#undef timeout
#include "HandleTurns.hpp"
#include "InitMaps.hpp"
#include "Network.hpp"
#include "VerifyBoatsFile.hpp"
#include "menu.hpp"  // Include the header file for run_menu
#include <iostream>

void start_game(const char* positions_file, const char* port, const char* ip, const char* mode) {
    bool is_server = (std::string(mode) == "server");

    initscr();
    noecho();
    cbreak();              // Disable line buffering
    keypad(stdscr, TRUE);  // Enable F1, F2 etc.
    curs_set(0);           // Hide the cursor

    mvprintw(0, 0, "Starting as %s on port %s with IP %s...", mode, port, ip);
    refresh();

    Network netw;
    if (!netw.Start(port, is_server, ip)) {
        mvprintw(1, 0, "Failed to start as client or server. Exiting...");
        refresh();
        getch();
        endwin();
        return;
    }

    mvprintw(1, 0, "Successfully started as %s on port %s with IP %s", mode, port, ip);
    refresh();

    HandleTurns handleturns_obj(is_server, netw);

    InitMaps map_obj;
    std::vector<std::string> myMatrix = map_obj.init_matrix(positions_file);
    std::vector<std::string> enemyMatrix(myMatrix.size(), std::string(myMatrix[0].size(), '.'));

    if (myMatrix.empty()) {
        mvprintw(2, 0, "Failed to initialize map from file: %s", positions_file);
        refresh();
        getch();
        endwin();
        return;
    }

    handleturns_obj.player_management(0, nullptr, myMatrix, enemyMatrix);

    endwin();  // End ncurses mode when done
}

int main(int argc, char** argv) {
    if (argc == 5) {
        start_game(argv[1], argv[2], argv[3], argv[4]);
        return 0;
    }

    int choice = run_menu();

    if (choice == 1) {
        start_game("pos/pos1", "1227", "127.0.0.1", "server");
    } else if (choice == 2) {
        start_game("pos/pos1", "1227", "127.0.0.1", "client");
    }

    return 0;
}
