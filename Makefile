##
## EPITECH PROJECT, 2019
## PSU_navy_2018
## File description:
## Makefile
##


SRC    =    navy.c

LIB_FOLDER    =    ./lib/my

LIB_SHORT_NAME    =    my

BIN_NAME    =    navy

all: compil_lib compil_file clean

compil_lib:
	@make -C $(LIB_FOLDER)

compil_file:
	@gcc $(SRC) -o $(BIN_NAME) -lm -L $(LIB_FOLDER) -l $(LIB_SHORT_NAME)

clean:
	@rm -f $(OBJ)
	@make clean -C $(LIB_FOLDER)

fclean:
	@rm -f $(OBJ)
	@rm -f $(LIB_NAME)
	@rm -f $(BIN_NAME)
	@make fclean -C $(LIB_FOLDER)

re: fclean all
	@make re -C $(LIB_FOLDER)
