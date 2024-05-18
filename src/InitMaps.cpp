#include "InitMaps.hpp"
#include <fstream>
#include <sstream>
#include <iostream>
#include <unistd.h>
#include <fcntl.h>
#include <cstdlib>

#define FILE_LEN 1024
#define LINE_LEN 256

InitMaps::InitMaps() {}

InitMaps::~InitMaps() {}

int InitMaps::is_boat(int x, int y, t_matrix map) {
    if ((map[y].at(x) >= '1' && map[y].at(x) <= '8') || (map[y].at(x) == 'x'))
        return 1;
    return 0;
}

void InitMaps::fill_navy_str(t_matrix &map) {
    // Resize the matrix to 10 rows if not already, each with a length of 18 characters.
    map.resize(10);  // Ensure there are 10 rows.
    
    for (int x = 0; x < 10; x++) {
        map[x].resize(18, ' ');  // Ensure each row is 18 characters long, filled with spaces.
        
        for (int y = 0; y < 18; y++) {
            if (y % 2 == 0) {
                map[x][y] = '.';  // Place dots at even indices to represent water.
            } else {
                map[x][y] = ' ';  // Place spaces at odd indices for visual separation.
            }
        }
    }
}

int InitMaps::init_boat(const std::string& filepath, t_matrix& map) {
    std::ifstream file(filepath);
    if (!file.is_open()) {
        std::cerr << "Error opening file: " << filepath << std::endl;
        return -1;
    }

    std::string line;
    while (getline(file, line)) {
        if (!line.empty()) {
            draw_boat(line, map);
        }
    }
    return 0;
}

void InitMaps::draw_boat(const std::string& line_buffer, t_matrix& map) {
    int x1 = get_x(line_buffer[2]);
    int y1 = get_y(line_buffer[3]);
    int x2 = get_x(line_buffer[5]);
    int y2 = get_y(line_buffer[6]);

    if (x1 == x2) {
        for (int y = std::min(y1, y2); y <= std::max(y1, y2); y++) {
            map[y][x1] = line_buffer[0];
        }
    } else if (y1 == y2) {
        for (int x = std::min(x1, x2); x <= std::max(x1, x2); x++) {
            map[y1][x] = line_buffer[0];
        }
    }
}

t_matrix InitMaps::init_matrix(const std::string& path) {
    t_matrix matrix(10, std::string(18, ' '));
    fill_navy_str(matrix);

    if (init_boat(path, matrix) != 0) {
        std::cerr << "Failed to initialize map from file: " << path << std::endl;
    }
    return matrix;
}

int InitMaps::get_x(char c) {
    return (c - 'A') * 2 + 2; // Assuming the board's columns start at index 2 in the matrix
}

int InitMaps::get_y(char c) {
    return (c - '1') + 2; // Assuming the board's rows start at index 2 in the matrix
}
