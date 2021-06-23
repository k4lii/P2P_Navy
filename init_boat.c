/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** init_boat
*/

int verify_boats_file(char **argv, int argc)
{
    char **pos_file;

    if (argc == 2)
        pos_file = map_in_str(argv[1]);
    else if (argc == 3)
        pos_file = map_in_str(argv[2]);
    if (verify_rooms(pos_file) == 84)
        return (84);
    if (verify_lenght(pos_file) == 84)
        return (84);
    if (verify_x_y(pos_file) == 84)
        return (84);
    if (verify_boat_order(pos_file) == 84)
        return (84);
    return (0);
}

int get_x(char c, char **map)
{
    for (int i = 0; i < 18; i++) {
        if (map[0][i] == c)
            return (i);
    }
}

int get_y(char c, char **map)
{
    for (int i = 0; i < 10; i++) {
        if (map[i][0] == c)
            return (i);
    }
}

void draw_boat(char *line_buffer, char **map)
{
    int x1 = get_x(line_buffer[2], map);
    int y1 = get_y(line_buffer[3], map);
    int x2 = get_x(line_buffer[5], map);
    int y2 = get_y(line_buffer[6], map);

    if (x1 == x2) {
        for (y1; y1 < y2; y1++)
            map[y1][x1] = line_buffer[0];
    }
    else if (y1 == y2) {
        for (x1; x1 < x2; x1++) {
            if (x1 % 2 == 0)
                map[y1][x1] = line_buffer[0];
        }
    }
    map[y1][x1] = line_buffer[0];
}

int init_boat(char *filepath, char **map)
{
    int fd = open(filepath, O_RDONLY);
    char *file_buffer = (char *) malloc(sizeof(char) * FILE_LEN);
    char *line_buffer = (char *) malloc(sizeof(char) * LINE_LEN);
    int line_buffer_i = 0;

    read(fd, file_buffer, FILE_LEN);
    close(fd);
    for (int i = 0; file_buffer[i]; i++) {
        if (file_buffer[i] == '\n') {
            line_buffer_i = 0;
            draw_boat(line_buffer, map);
            continue;
        }
        line_buffer[line_buffer_i] = file_buffer[i];
        line_buffer_i++;
    }
    draw_boat(line_buffer, map);
    return (0);
}
