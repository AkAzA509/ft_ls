NAME	:= ft_ls
CC		:= cc
FLG		:= -Wall -Wextra -Werror -g3 -02 -fsanitize=address,leak
SRC		:= main.c

OBJ_DIR	:= obj/
OBJ		:=$(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)
	@$(CC) -o $(NAME) $(OBJ)

$(NAME): $(OBJ)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLG) -c $< -o $@

clean:
	@rm -rf $(OBJ_DIR)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re