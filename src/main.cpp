#include "HandleTurns.hpp"
#include "InitMaps.hpp"
#include "Network.hpp"
#include <iostream>

int main(int argc, char **argv) {
    if (argc != 4) {
        std::cerr << "Usage: " << argv[0] << " <positions_file> <port> <ip>" << std::endl;
        return 1;
    }

    bool is_server = (std::string(argv[3]) == "127.0.0.1");

    Network netw;
    if (!netw.Start(argv[2], is_server)) {
        std::cerr << "Failed to start as client or server. Exiting..." << std::endl;
        return 1;
    }

    HandleTurns handleturns_obj(is_server, netw);

    InitMaps map_obj;
    t_matrix matrix = map_obj.init_matrix(argv[1]);

    if (matrix.empty()) {
        std::cerr << "Failed to initialize map from file: " << argv[1] << std::endl;
        return 1;
    }

    handleturns_obj.player_management(argc, argv, matrix);

    return 0;
}
