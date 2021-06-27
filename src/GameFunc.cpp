#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>

#define FILE_LEN 33
#define LINE_LEN 7

int nb_col(char *av)
{
    int li = 0;
    int fd;
    char buf[1];
    int size;

    fd = open(av, O_RDONLY);
    for (int i = 0; read(fd, buf, 1) != 0; i++) {
        if (buf[0] == '\n')
            li++;
    }
    li++;
    close(fd);
    return (li);
}

int nb_lines(char *av)
{
    int co_size = 1;
    int co_save = 0;
    int fd;
    char buf[1];
    int size;

    fd = open(av, O_RDONLY);
    for (int i = 0; read(fd, buf, 1) != 0; i++) {
        co_size++;
        if (buf[0] == '\n') {
            co_size ++;
            if(co_size > co_save)
                co_save = co_size;
            co_size = 0;
        }
    }
    close(fd);
    return (co_save);
}

char **map_in_str(char *av)
{
    int li = nb_lines(av);
    int size_co = nb_col(av);
    int l = 0;
    int c = 0;
    char **lettre = malloc(sizeof(char *) * li + 1);
    int fd = open(av, O_RDONLY);
    char buf[1];

    for (l; l < li; l++)
        lettre[l] = malloc(sizeof(char) * size_co + 1);
    for (int l = 0; read(fd, buf, 1) != 0; c++) {
        lettre[l][c] = buf[0];
        if (lettre[l][c] == '\n') {
            c = -1;
            l++;
        }
    }
    close(fd);
    return (lettre); 
}

int verify_rooms(char **pos_file)
{
    int nb = 0;

    for (int y = 0; y != 4; y++) {
        if (pos_file[y][0] == '2')
            nb += 2;
        if (pos_file[y][0] == '3')
            nb += 3;
        if (pos_file[y][0] == '4')
            nb += 4;
        if (pos_file[y][0] == '4')
            nb += 5;
    }
    if (nb < 14 || nb > 14)
        return (84);
    else if (nb == 14)
        return (0);
}

int verify_boat_order(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (pos_file[y][2] > pos_file[y][5])
            return (84);
        if (pos_file[y][3] > pos_file[y][6])
            return (84);
    }
}

int verify_lenght(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (strlen(pos_file[y]) > 8 || strlen(pos_file[y]) < 6)
            return (84);
    }
    return (0);
}

int verify_x_y(char **pos_file)
{
    int nb = 0;

    for (int y = 0; y != 4; y++) {
        if (pos_file[y][2] >= 'A' && pos_file[y][2] <= 'H')
            nb++;
        if (pos_file[y][3] >= '1' && pos_file[y][3] <= '8')
            nb++;
        if (pos_file[y][5] >= 'A' && pos_file[y][5] <= 'H')
            nb++;
        if (pos_file[y][6] >= '1' && pos_file[y][6] <= '8')
            nb++;
    }
    if (nb > 16 || nb < 16)
        return (84);
    else if (nb == 16)
        return (0);
}



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
