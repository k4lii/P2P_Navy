#include "VerifyBoatsFile.hpp"

VerifyBoatsFile::VerifyBoatsFile(){}
VerifyBoatsFile::~VerifyBoatsFile(){}

int VerifyBoatsFile::nb_col(char *av)
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

int VerifyBoatsFile::nb_lines(char *av)
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

char** VerifyBoatsFile::map_in_str(char *av)
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

int VerifyBoatsFile::verify_rooms(char **pos_file)
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

int VerifyBoatsFile::verify_boat_order(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (pos_file[y][2] > pos_file[y][5])
            return (84);
        if (pos_file[y][3] > pos_file[y][6])
            return (84);
    }
    return(0);
}

int VerifyBoatsFile::verify_lenght(char **pos_file)
{
    for (int y = 0; y != 4; y++) {
        if (strlen(pos_file[y]) > 8 || strlen(pos_file[y]) < 6)
            return (84);
    }
    return (0);
}

int VerifyBoatsFile::verify_x_y(char **pos_file)
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

int VerifyBoatsFile::verify_boats_file(char **argv, int argc) //generer des positions aleatoire
{
    if (argc == 2 || argc == 3) { //improve error gestion
      //  printf("%s\n", argv[0]); //prog name
       // printf("%s\n", argv[1]);
       // exit(0);
        char **pos_file = map_in_str(argv[1]);
        if (verify_rooms(pos_file) == 84)
            return (84);
        if (verify_lenght(pos_file) == 84)
            return (84);
        if (verify_x_y(pos_file) == 84)
            return (84);
        if (verify_boat_order(pos_file) == 84)
            return (84);
    }
    return (0);
}