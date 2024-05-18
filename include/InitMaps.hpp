#ifndef INITMAPS_HPP
#define INITMAPS_HPP

#include <vector>
#include <string>
#include "types.hpp"

class InitMaps {
public:
    InitMaps();
    ~InitMaps();
    
    int is_boat(int x, int y, t_matrix map);
    void fill_navy_str(t_matrix &map);
    int init_boat(char *filepath, t_matrix &map);
    void draw_boat(char *line_buffer, t_matrix &map);
    t_matrix init_matrix(char *path);
    int get_x(char c, t_matrix map);
    int get_y(char c, t_matrix map);
};

#endif // INITMAPS_HPP
