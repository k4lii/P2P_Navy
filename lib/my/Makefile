##
## EPITECH PROJECT, 2019
## CPE_solostumper_4_2018
## File description:
## Makefile
##


SRC 	= 	*.c

OBJ 	= 	$(SRC:.c=.o)

LIB_NAME	 = 		libmy.a

all: compil_lib clean

compil_lib:
	@gcc -c $(SRC)
	@ar rc $(LIB_NAME) $(OBJ)

clean:
	@rm -f $(OBJ)

fclean:
	@rm -f $(OBJ)
	@rm -f $(LIB_NAME)

re: fclean all