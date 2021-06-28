#include "HandleTurns.hpp"
#include "InitMaps.hpp"
#include "VerifyBoatsFile.hpp"

int main(int argc, char **argv)
{
    t_matrix matrix;
    HandleTurns handleturns_obj;
    InitMaps map_obj;
    VerifyBoatsFile verifboatfile_obj;

    // if (error_gestion(argv, argc) == 0)
    //     return (0);
    if (verifboatfile_obj.verify_boats_file(argv, argc) == 84) {
        std::cout << "Incorrect boat file" << std::endl;
        return (84);
    }
    matrix = map_obj.init_matrix(argv[1]);
    handleturns_obj.print_navy(matrix.map, matrix.enemy_map);
    
    // handleturns_obj.player_managment(int argc, matrix.map, matrix.enemy_map);
    return 0;
}