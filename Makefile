NAME = minishell
CC = cc -g
CCFLAGS = -Wall -Wextra -Werror

LIBFT = libft.a
LIBFT_DIR = libs/libft

SRC =	srcs/main.c srcs/tokenizer/tokenizer.c srcs/tokenizer/check.c srcs/tokenizer/in_quotes.c \
		srcs/tokenizer/token_list.c srcs/parser/command.c srcs/parser/env.c srcs/parser/expansions.c \
		 srcs/parser/parser.c

OBJ = $(SRC:.c=.o)

%.o: %.c
		$(CC) $(CCFLAGS) -o $@ -c $^

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) bonus

$(NAME): $(OBJ)
		$(CC) $(CCFLAGS) $(OBJ) -o $(NAME) $(LIBFT_DIR)/$(LIBFT) -lreadline

clean:
	rm -rf $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean

fclean: clean
	rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
