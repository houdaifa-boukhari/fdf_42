NAME = fdf
NAME_BONUS = fdf_bonus
HEADER = ./MANDATORY/fdf.h
HEADER_BONUS = ./BONUS/fdf_bonus.h
SRC_BONUS= ./BONUS/fdf_bonus.c ./BONUS/controle_keys_bonus.c ./BONUS/get_coords_bonus.c ./BONUS/tools.list_bonus.c ./BONUS/draw_utilize_bonus.c \
	./BONUS/rotation_utlize_bonus.c ./BONUS/get_coords2_bonus.c ./BONUS/extra_bonus.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
SRC = ./MANDATORY/fdf.c ./MANDATORY/controle_keys.c ./MANDATORY/get_coords.c ./MANDATORY/tools.list.c ./MANDATORY/draw_utilize.c \
	./MANDATORY/rotation_utlize.c get_next_line/get_next_line.c get_next_line/get_next_line_utils.c
OBJS = $(SRC:.c=.o)
OBJS_BONUS = $(SRC_BONUS:.c=.o)
CC = clang
CFLAGS = -I/usr/include -I/minilibx-linux 
CFLAGS1 = -g -L/minilibx-linux -L/usr/lib  -lXext -lX11 -lm -lz
LIBS = -L./libft -lft -L./minilibx-linux -lmlx_Linux -lXext -lX11 -lm -lz

all : libft $(NAME)

$(NAME) : $(OBJS)
	@$(CC) $(CFLAGS1) $(OBJS) -o $(NAME) $(LIBS)
%.o : %.c $(HEADER)
	@$(CC) $(CFLAGS) -c $< -o $@

libft:
	@make -C ./libft all
	@make -C ./libft bonus

bonus : libft $(NAME_BONUS)
$(NAME_BONUS) : $(OBJS_BONUS)
		@$(CC) $(CFLAGS1) $(OBJS_BONUS) -o $(NAME_BONUS) $(LIBS)
%.o : %.c $(HEADER_BONUS)
		@$(CC) $(CFLAGS) -c $< -o $@
clean :
	@rm -f $(OBJS)
	@rm -f $(OBJS_BONUS)
	@make clean -C ./libft

fclean : clean
	@rm -f $(NAME)
	@rm -f $(NAME_BONUS)
	@make fclean -C ./libft

re : fclean all

.PHONY: all clean fclean re libft bonus
