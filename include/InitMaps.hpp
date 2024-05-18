#ifndef INITMAPS_HPP
#define INITMAPS_HPP

#include "types.hpp"

class InitMaps {
public:
    InitMaps();
    ~InitMaps();

    int is_boat(int x, int y, t_matrix map);
    void fill_navy_str(t_matrix &map);
    int init_boat(const char *filepath, t_matrix &map);
    t_matrix init_matrix(const char *path);
    int get_x(char c, const t_matrix &map);
    int get_y(char c, const t_matrix &map);
    void draw_boat(const char *line_buffer, t_matrix &map); // Updated to const char*
};

#endif // INITMAPS_HPP
