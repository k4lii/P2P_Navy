#include "Network.hpp"

    // Network net;
    // if (argc == 2) {
    //     std::cout << net.Receive(9999);
    // } else if (argc == 3) {
    //     net.Send("salut", "127.0.0.1", 9999);
    // }


// #include <stdlib.h>
// #include <unistd.h>
// #include <sys/types.h>
// #include <fcntl.h>
// #include <signal.h>
// #include "struct.hpp"
// #include "init_matrix.cpp"
// #include "Gamefunctions.cpp"
// #include "turn_management.cpp"

// void print_latest_message(int value)
// {
//     if (value == 1)
//         my_putstr("\nEnemy won");
//     else if (value == 0)
//         my_putstr("\nI won");
// }

// int win_lose(char **map, char **enemy_map)
// {
//     int nb_map = 0;
//     int nb_enemy_map = 0;

//     for (int y = 2; y != 10; y++) {
//         for (int x = 2; x != 17; x++) {
//             if (map[y][x] == 'x')
//                 nb_map += 1;
//             if (enemy_map[y][x] == 'x')
//                 nb_enemy_map += 1;
//         }
//     }
//     if (nb_map == 14)
//         return (1);
//     if (nb_enemy_map == 14)
//         return (0);
//     return (2);
// }

// int player2(char *str, char **argv, char **map, char **enemy_map)
// {
//     int receive_value = 0;
//     int ret_value = 2;

//     print_pid(2);
//     usleep(100);
//     send_user(my_getnbr(my_itoa(getpid(), str)), argv[1]);
//     receive(&receive_value);
//     if (receive_value >= 1)
//         my_putstr("successfully connected\n");
//     print_navy(map, enemy_map);
//     while (ret_value > 1) {
//         defense(argv[1], map);
//         ret_value = win_lose(map, enemy_map);
//         if (ret_value == 1 || ret_value == 0) {
//             print_navy(map, enemy_map);
//             return (ret_value);
//         }
//         attack(argv[1], enemy_map);
//         print_navy(map, enemy_map);
//     }
// }

// int player1(char *str, int pid_j2, char **map, char **enemy_map)
// {
//     int receive_value = 0;
//     int ret_value = 2;

//     print_pid(1);
//     receive(&receive_value);
//     pid_j2 = receive_value;
//     if (receive_value >= 1)
//         my_putstr("\nenemy connected\n");
//     send_user(10, my_itoa(receive_value, str));
//     print_navy(map, enemy_map);
//     while (ret_value > 1) {
//         attack(my_itoa(pid_j2, str), enemy_map);
//         ret_value = win_lose(map, enemy_map);
//         if (ret_value == 1 || ret_value == 0) {
//             print_navy(map, enemy_map);
//             return (ret_value);
//         }
//         defense(my_itoa(pid_j2, str), map);
//         print_navy(map, enemy_map);
//     }
// }

// int main(int argc, char **argv)
// {
//     t_matrix matrix;
//     int ret_value;
//     int pid_j2;
//     char *str = (char *)malloc(sizeof(char) * 20);

//     if (error_gestion(argv, argc) == 0)
//         return (0);
//     if (verify_boats_file(argv, argc) == 84)
//         return (84);
//     if (argc == 2) {
//         matrix = init_matrix(argc, argv, 1);
//         ret_value = player1(str, pid_j2, matrix.map, matrix.enemy_map);
//         print_latest_message(ret_value);
//         return (ret_value);
//     } else if (argc == 3) {
//         matrix = init_matrix(argc, argv, 2);
//         ret_value = player2(str, argv, matrix.map, matrix.enemy_map);
//         print_latest_message(ret_value);
//         return (ret_value);
//     }
// }

int main(){
    return 0;
}