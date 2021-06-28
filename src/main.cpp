#include "HandleTurns.hpp"
#include "InitMaps.hpp"
#include "GameFunc.hpp"

int main(int argc, char **argv)
{
    t_matrix matrix;
    HandleTurns handleturns_obj;
    InitMaps map_obj;
    GameFunc gamefunc;


    // if (error_gestion(argv, argc) == 0)
    //     return (0);
    if (gamefunc.verify_boats_file(argv, argc) == 84)
        return (84);
    
    // matrix = map_obj.init_matrix(argc, argv, 1);
    // handleturns_obj.player_managment(int argc, matrix.map, matrix.enemy_map);
    return 0;
}