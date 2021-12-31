NAME = so_long

CFLAGS = -Wall -Wextra -Werror

FRAME = -lmlx -framework OpenGL -framework AppKit

SRC = src/so_long.c src/movement.c src/print_map.c src/check_map.c src/get_next_line.c src/get_next_line_utils.c

INC = so_long.h

OBJ = $(SRC:.c=.o)

all : $(NAME)
$(NAME) : $(OBJ) $(INC)
	gcc $(CFLAGS) $(FRAME) $(OBJ) -o $(NAME)

clean : 
	rm -rf $(OBJ)

fclean : clean
	rm -rf $(NAME)

re : fclean all