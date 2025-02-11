NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror -g

SRC =	./src/main.c   \
		./src/validate.c   \
		./src/algorithm.c  \
		./src/math.c     \


OBJ_DIR = obj

OBJ = $(SRC:./src/%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH = ./libft/
LIBFT = $(LIBFT_PATH)/libft.a

HEADERS	= -I ./include -I $(LIBFT_PATH)/include

all: $(NAME)

$(LIBFT):
	@make -C $(LIBFT_PATH)

$(OBJ_DIR)/%.o: ./src/%.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@ $(HEADERS)
	
$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(OBJ) $(HEADERS) $(LIBFT) -o $(NAME)
	@echo "Compilation complete!"

clean:
	@rm -rf $(OBJ_DIR) 

fclean: clean
	@rm -rf $(NAME)
	@make fclean -C $(LIBFT_PATH)
	@echo "Cleaning completed!"

re: fclean all

.PHONY: all clean fclean re