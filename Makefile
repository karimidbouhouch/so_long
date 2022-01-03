NAME = so_long

CFLAGS = -Wall -Wextra -Werror

FRAME = -lmlx -framework OpenGL -framework AppKit

SRC = src/so_long.c src/movement.c src/print_map.c src/check_map.c src/get_next_line.c src/get_next_line_utils.c
SRC_BONUS = bonus/so_long_bonus.c bonus/movement_bonus.c bonus/print_map_bonus.c bonus/check_map_bonus.c bonus/get_next_line_bonus.c bonus/get_next_line_utils_bonus.c bonus/ft_itoi_bonus.c

INC = so_long.h
INC_BONUS = so_long_bonus.h

OBJ = $(SRC:.c=.o)
OBJ_BONUS = $(SRC_BONUS:.c=.o)

all : $(NAME)
$(NAME) : $(OBJ) $(INC)
	gcc $(CFLAGS) $(FRAME) $(OBJ) -o $(NAME)

bonus : $(OBJ_BONUS) $(INC_BONUS)
	gcc $(CFLAGS) $(FRAME) $(OBJ_BONUS) -o $(NAME)

clean : 
	rm -rf $(OBJ) $(OBJ_BONUS)

fclean : clean
	rm -rf $(NAME)

re : fclean all