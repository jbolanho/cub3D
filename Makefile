NAME = cub3D

CC = cc

CFLAGS = -Wall -Wextra -Werror -g3
MFLAGS = -ldl -lglfw -pthread -lm


SRC =	./src/1.main.c   \
		./src/2.validate.c   \
		./src/3.check_header.c   \
		./src/4.h_check_path.c   \
		./src/5.h_check_colors.c   \
		./src/6.check_map.c   \
		./src/7.m_check_walls.c   \
		./src/8.m_check_player.c \
		./src/9.init.c \
		./src/10.game.c  \
		./src/11.key_data.c  \
		./src/12.key_data_utils.c  \
		./src/13.algorithm.c  \
		./src/14.algorithm_utils.c  \
		./src/15.byebye.c  \
		./src/AVALIAR.c   \
		./src/utils.c 


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

# valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --suppressions=.sup_mlx.supp --log-file=log ./cub3D ./maps/map6.cub