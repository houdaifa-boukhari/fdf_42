NAME = fdf
HEADER = fdf.h
SRC = ./mandatory/fdf.c ./mandatory/controle_keys.c ./mandatory/get_coords.c ./mandatory/tools.list.c ./mandatory/draw_utilize.c \
	get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
CC = cc
CFLAGS = -Wall -Wextra -Werror -Imlx -fsanitize=address
LIBS = -L./libft -lft -L./printf -lftprintf

all : libft printf $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS) -lmlx -framework OpenGL -framework AppKit $(OBJS) -o $(NAME) $(LIBS)
%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@make -C ./libft all
	@make -C ./libft bonus

printf:
	@make -C ./printf

clean :
	@rm -f $(OBJS)
	@make clean -C ./libft
	@make clean -C ./printf

fclean : clean
	@rm -f $(NAME)
	@make fclean -C ./libft
	@make fclean -C ./printf

re : fclean all

.PHONY: all clean fclean re libft printf