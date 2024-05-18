#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

class VerifyBoatsFile {
public:
    VerifyBoatsFile();
    ~VerifyBoatsFile();

    int nb_col(char *av);
    int nb_lines(char *av);
    char** map_in_str(char *av);
    int verify_rooms(char **pos_file);
    int verify_boat_order(char **pos_file);
    int verify_lenght(char **pos_file);
    int verify_x_y(char **pos_file);
    int verify_boats_file(char **argv, int argc);
};
