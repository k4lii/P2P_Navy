#pragma once
#include <string.h>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

class VerifyBoatsFile
{
    public:
        VerifyBoatsFile();
        ~VerifyBoatsFile();
        int verify_boats_file(char **argv, int argc);
    private:
        char **map_in_str(char *av);
        int verify_rooms(char **pos_file);
        int verify_boat_order(char **pos_file);
        int verify_lenght(char **pos_file);
        int verify_x_y(char **pos_file);
        int nb_col(char *av);
        int nb_lines(char *av);
        
};