#ifndef VERIFYBOATSFILE_HPP
#define VERIFYBOATSFILE_HPP

#include <string>

class VerifyBoatsFile {
public:
    VerifyBoatsFile();
    ~VerifyBoatsFile();

    int nb_col(const char *filename);
    int nb_lines(const char *filename);
    char** map_in_str(const char *filename);
    int verify_rooms(char **pos_file);
    int verify_boat_order(char **pos_file);
    int verify_length(char **pos_file); // Updated declaration
    int verify_x_y(char **pos_file);
    int verify_boats_file(char **argv, int argc);
};

#endif // VERIFYBOATSFILE_HPP
