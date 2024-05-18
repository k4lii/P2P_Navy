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
    for (int x = 0; x != 10; x++) {
        for (int y = 0; y != 17; y++) {
            if (y % 2)
                map[x].at(y) = ' ';
            else
                map[x].at(y) = '.';
        }
    }
    map[0].at(0) = ' ';
    map[0].at(1) = '|';
    for (int y = 2; y != 18; y += 2) {
        map[0].at(y) = 65 + (y / 2) - 1;
        map[0].at(y + 1) = ' ';
    }

    for (int y = 0; y != 17; y++)
        map[1].at(y) = '-';
    map[1].at(1) = '+';
    for (int y = 2; y != 10; y++) {
        map[y].at(0) = 49 + (y - 2);
        map[y].at(1) = '|';
    }
    for (int x = 0; x != 10; x++)
        map[x].pop_back();
}

int InitMaps::init_boat(const char *filepath, t_matrix &map) {
    int fd = open(filepath, O_RDONLY);
    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    char *file_buffer = (char *)malloc(FILE_LEN);
    char *line_buffer = (char *)malloc(LINE_LEN);
    int line_buffer_i = 0;

    ssize_t bytes_read = read(fd, file_buffer, FILE_LEN);
    if (bytes_read < 0) {
        perror("Error reading file");
        close(fd);
        free(file_buffer);
        free(line_buffer);
        return -1;
    }
    close(fd);

    for (int i = 0; i < bytes_read; i++) {
        if (file_buffer[i] == '\n') {
            line_buffer[line_buffer_i] = '\0';
            line_buffer_i = 0;
            draw_boat(line_buffer, map);
            continue;
        }
        line_buffer[line_buffer_i++] = file_buffer[i];
    }
    draw_boat(line_buffer, map);
    free(file_buffer);
    free(line_buffer);
    return 0;
}

void InitMaps::draw_boat(const char *line_buffer, t_matrix &map) { // Updated to const char*
    int x1 = get_x(line_buffer[2], map);
    int y1 = get_y(line_buffer[3], map);
    int x2 = get_x(line_buffer[5], map);
    int y2 = get_y(line_buffer[6], map);

    if (x1 == x2) {
        for (; y1 < y2; y1++)
            map[y1][x1] = line_buffer[0];
    } else if (y1 == y2) {
        for (; x1 < x2; x1++) {
            if (x1 % 2 == 0)
                map[y1][x1] = line_buffer[0];
        }
    }
    map[y1][x1] = line_buffer[0];
}

t_matrix InitMaps::init_matrix(const char *path) {
    t_matrix matrix(10, std::string(18, ' '));
    fill_navy_str(matrix);

    if (init_boat(path, matrix) != 0) {
        std::cerr << "Failed to initialize map from file: " << path << std::endl;
    }
    return matrix;
}

int InitMaps::get_x(char c, const t_matrix &map) {
    for (int i = 0; i < 18; i++) {
        if (map[0][i] == c)
            return i;
    }
    return -1;
}

int InitMaps::get_y(char c, const t_matrix &map) {
    for (int i = 0; i < 10; i++) {
        if (map[i][0] == c)
            return i;
    }
    return -1;
}
