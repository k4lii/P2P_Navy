#ifndef INITMAPS_HPP
#define INITMAPS_HPP

#include "types.hpp"
#include <string>  // Make sure to include this for std::string

class InitMaps {
public:
    InitMaps();
    ~InitMaps();

    int is_boat(int x, int y, t_matrix map);
    void fill_navy_str(t_matrix &map);
    int init_boat(const std::string& filepath, t_matrix &map);  // Changed to std::string
    t_matrix init_matrix(const std::string& path);
    int get_x(char c); // Updated
    int get_y(char c); // Updated
    void draw_boat(const std::string& line_buffer, t_matrix &map); // Changed to std::string
};

#endif // INITMAPS_HPP
