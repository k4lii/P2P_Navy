#include "VerifyBoatsFile.hpp"
#include <iostream>
#include <fcntl.h>
#include <unistd.h>
#include <cstring>
#include <cstdlib>

VerifyBoatsFile::VerifyBoatsFile() {}
VerifyBoatsFile::~VerifyBoatsFile() {}

int VerifyBoatsFile::nb_col(const char *filename) {
    int lines = 0;
    int fd = open(filename, O_RDONLY);
    char buf[1];

    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    while (read(fd, buf, 1)) {
        if (buf[0] == '\n')
            lines++;
    }
    close(fd);
    return lines + 1;
}

int VerifyBoatsFile::nb_lines(const char *filename) {
    int max_col_size = 1;
    int current_col_size = 0;
    int fd = open(filename, O_RDONLY);
    char buf[1];

    if (fd == -1) {
        perror("Error opening file");
        return -1;
    }

    while (read(fd, buf, 1)) {
        current_col_size++;
        if (buf[0] == '\n') {
            if (current_col_size > max_col_size)
                max_col_size = current_col_size;
            current_col_size = 0;
        }
    }
    close(fd);
    return max_col_size + 1;
}

char** VerifyBoatsFile::map_in_str(const char *filename) {
    int rows = nb_lines(filename);
    int cols = nb_col(filename);
    char **letters = (char **)malloc(sizeof(char *) * (rows + 1));
    int fd = open(filename, O_RDONLY);
    char buf[1];

    if (fd == -1) {
        perror("Error opening file");
        return nullptr;
    }

    for (int i = 0; i < rows; i++) {
        letters[i] = (char *)malloc(sizeof(char) * (cols + 1));
    }

    int row = 0;
    int col = 0;
    while (read(fd, buf, 1)) {
        letters[row][col++] = buf[0];
        if (buf[0] == '\n') {
            letters[row][col] = '\0';
            row++;
            col = 0;
        }
    }
    close(fd);
    return letters;
}

int VerifyBoatsFile::verify_rooms(char **pos_file) {
    int total_rooms = 0;

    for (int i = 0; i < 4; i++) {
        switch (pos_file[i][0]) {
            case '2': total_rooms += 2; break;
            case '3': total_rooms += 3; break;
            case '4': total_rooms += 4; break;
            case '5': total_rooms += 5; break;
            default: return 84;
        }
    }

    return (total_rooms == 14) ? 0 : 84;
}

int VerifyBoatsFile::verify_boat_order(char **pos_file) {
    for (int i = 0; i < 4; i++) {
        if (pos_file[i][2] > pos_file[i][5] || pos_file[i][3] > pos_file[i][6])
            return 84;
    }
    return 0;
}

int VerifyBoatsFile::verify_length(char **pos_file) { // Corrected function name
    for (int i = 0; i < 4; i++) {
        if (strlen(pos_file[i]) < 6 || strlen(pos_file[i]) > 8)
            return 84;
    }
    return 0;
}

int VerifyBoatsFile::verify_x_y(char **pos_file) {
    int valid_count = 0;

    for (int i = 0; i < 4; i++) {
        if (pos_file[i][2] >= 'A' && pos_file[i][2] <= 'H') valid_count++;
        if (pos_file[i][3] >= '1' && pos_file[i][3] <= '8') valid_count++;
        if (pos_file[i][5] >= 'A' && pos_file[i][5] <= 'H') valid_count++;
        if (pos_file[i][6] >= '1' && pos_file[i][6] <= '8') valid_count++;
    }

    return (valid_count == 16) ? 0 : 84;
}

int VerifyBoatsFile::verify_boats_file(char **argv, int argc) {
    if (argc == 2 || argc == 3) {
        char **pos_file = map_in_str(argv[1]);
        if (!pos_file) return 84;

        if (verify_rooms(pos_file) == 84 ||
            verify_length(pos_file) == 84 || // Corrected function call
            verify_x_y(pos_file) == 84 ||
            verify_boat_order(pos_file) == 84) {
            return 84;
        }
    }
    return 0;
}
