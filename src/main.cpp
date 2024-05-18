#include "HandleTurns.hpp"
#include "InitMaps.hpp"
#include "Network.hpp"
#include "VerifyBoatsFile.hpp"
#include <iostream>
#include <ncurses.h>

int main(int argc, char** argv) {
    if (argc != 5) {
        std::cerr << "Usage: " << argv[0] << " <positions_file> <port> <ip> <mode>" << std::endl;
        return 1;
    }

    bool is_server = (std::string(argv[4]) == "server");

    Network netw;
    if (!netw.Start(argv[2], is_server, argv[3])) {
        std::cerr << "Failed to start as client or server. Exiting..." << std::endl;
        return 1;
    }

    HandleTurns handleturns_obj(is_server, netw);

    InitMaps map_obj;
    std::vector<std::string> myMatrix = map_obj.init_matrix(argv[1]);
    std::vector<std::string> enemyMatrix(myMatrix.size(), std::string(myMatrix[0].size(), '.'));

    if (myMatrix.empty()) {
        std::cerr << "Failed to initialize map from file: " << argv[1] << std::endl;
        return 1;
    }

    handleturns_obj.player_management(argc, argv, myMatrix, enemyMatrix);

    return 0;
}
