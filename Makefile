NAME = cub3D

CC = cc

FLAGS = -Wall -Wextra -Werror

SRC =	./main.c   \


OBJ_DIR = obj

OBJ = $(src:%.c=$(OBJ_DIR)/%.o)

HEADERS =

all: $(NAME)

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	@$(CC) $(FLAGS) -c $< -o $@ -g3 $(HEADERS)
	
$(NAME): $(OBJ)
	@$(CC) -g3 $(OBJ) $(HEADERS) -o $(NAME)
	@echo "Compilation complete!"

clean:
	@rm -rf $(OBJ_DIR) 

fclean: clean
	@rm -rf $(NAME)
	@echo "Cleaning completed!"

re: fclean all

.PHONY: all clean fclean re