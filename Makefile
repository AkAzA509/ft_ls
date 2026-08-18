NAME		:= ft_ls
CC			:= cc
CFLAGS		:= -Wall -Wextra -Werror -O2 -fsanitize=address,leak
SRC_PATH	:= src/
SRC			:= $(SRC_PATH)main.c \
			   ${SRC_PATH}parser.c \
			   $(SRC_PATH)print.c \
			   $(SRC_PATH)listing.c

INC			:= -Iinclude -Isrc/libft/include
LIBFT_DIR	:= src/libft
LIBFT		:= $(LIBFT_DIR)/libft.a

OBJ_DIR		:= obj/
OBJ			:=$(SRC:%.c=$(OBJ_DIR)%.o)

all: $(NAME)

$(NAME): libft $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)

$(OBJ_DIR)%.o : %.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(INC) -c $< -o $@

libft:
	$(MAKE) -C $(LIBFT_DIR)

clean:
	$(MAKE) -C $(LIBFT_DIR) clean
	rm -rf $(OBJ_DIR)

fclean: clean
	$(MAKE) -C $(LIBFT_DIR) fclean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re