#include "GameFunc.hpp"

GameFunc::GameFunc(){}
GameFunc::~GameFunc(){}

int GameFunc::nb_col(char *av)
{
    int li = 0;
    int fd;
    char buf[1];

    fd = open(av, O_RDONLY);
    for (int i = 0; read(fd, buf, 1) != 0; i++) {
        if (buf[0] == '\n')
            li++;
    }
    li++;
    close(fd);
    return (li);
}

int GameFunc::nb_lines(char *av)
{
    int co_size = 1;
    int co_save = 0;
    int fd;
    char buf[1];

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

char** GameFunc::map_in_str(char *av)
{
    int li = nb_lines(av);
    int size_co = nb_col(av);
    int c = 0;
    char **lettre = (char **)malloc(sizeof(char *) * li + 1);
    int fd = open(av, O_RDONLY);
    char buf[1];

    for (int l = 0; l < li; l++)
        lettre[l] = (char *)malloc(sizeof(char) * size_co + 1);
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

int GameFunc::verify_rooms(char **pos_file)
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
    return(0);
}

int GameFunc::verify_boat_order(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (pos_file[y][2] > pos_file[y][5])
            return (84);
        if (pos_file[y][3] > pos_file[y][6])
            return (84);
    }
    return(0);
}

int GameFunc::verify_lenght(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (strlen(pos_file[y]) > 8 || strlen(pos_file[y]) < 6)
            return (84);
    }
    return (0);
}

int GameFunc::verify_x_y(char **pos_file)
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
    return(0);
}



int GameFunc::verify_boats_file(char **argv, int argc)
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