NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3
MFLAGS = -ldl -lglfw -pthread -lm


SRC =	./src/main.c   \
		./src/1.init.c   \
		./src/2.initial_pov.c \
		./src/3.player_pov.c \
		./src/4.algorithm.c  \
		./src/5.copymap.c \
		./src/6.game.c    \
		./src/7.byebye.c     \
		./src/validate.c   \
		./src/validate_n_process.c   \
		./src/validate_utils.c   \
		./src/check_path.c   \
		#./src/check_colors.c   \


OBJ_DIR = obj

OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

LIBFT = ./libft/libft.a

MLX = ./MLX42/build/libmlx42.a -ldl -lglfw -pthread -lm

HEADERS	= -I ./include -I ./libft/include -I ./MLX42/include

all: libmlx $(NAME)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(@D)
	@$(CC) $(CFLAGS) -c $< -o $@ $(HEADERS)
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(MFLAGS) $(OBJ) $(HEADERS) $(LIBFT) $(MLX) -o $(NAME)
	@echo "Compilation complete!"

$(LIBFT):
	@make -C ./libft/

libmlx:
	@cmake -S ./MLX42 -B ./MLX42/build
	@cmake --build ./MLX42/build -j4

clean:
	@rm -rf $(OBJ_DIR) 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C ./libft/
	@echo "Cleaning completed!"

re: fclean all

.PHONY: all clean fclean re