NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3
MFLAGS = -ldl -lglfw -pthread -lm


SRC =	./src/main.c   \
		./src/1.init.c \
		./src/2.game.c  \
		./src/3.key_data.c  \
		./src/4.key_data_utils.c  \
		./src/5.algorithm.c  \
		./src/6.algorithm_utils.c  \
		./src/7.byebye.c  \
		./src/validate.c   \
		./src/validate_n_process.c   \
		./src/validate_utils.c   \
		./src/check_path.c   \
		./src/check_colors.c   \
		./src/get_map.c   \
		./src/check_map.c   \
		./src/check_walls.c   \
		./src/map_utils.c \

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
	@$(CC) $(CFLAGS) $(MFLAGS) $(OBJ) $(HEADERS) $(LIBFT) $(MLX) -o $(NAME) -g
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

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.sup_mlx.supp ./cub3D ./maps/map3.cub