/*
** EPITECH PROJECT, 2019
** PSU_navy_2018
** File description:
** my_getnbr
*/

int is_num(char const *str)
{
    if (str[0] == '-' && (str[1] >= '0' && str[1] <= '9'))
        return (1);
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= '0' && str[i] <= '9'))
            return (0);
    }
    return (1);
}

int my_getnbr(char const *str)
{
    int num = 0;

    if ((is_num(str))) {
        for (int i = 0; str[i] != '\0'; i++) {
            if (str[i] != '-') {
                num *= 10;
                num += str[i] - '0';
            }
        }
        if (str[0] == '-')
            num *= -1;
        return (num);
    }
}