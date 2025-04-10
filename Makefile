NAME = minishell
CC = cc
CCFLAGS = -Wall -Wextra -Werror

LIBFT = libft.a
LIBFT_DIR = libs/libft

SRC =	srcs/main.c srcs/utils/is_space.c srcs/utils/is_redir.c srcs/utils/is_quotes.c srcs/utils/is_posix_std.c \
		srcs/utils/in_quotes.c srcs/utils/in_dbl_quotes.c srcs/utils/is_last_redir.c	srcs/tokenizer/tokenize_line.c \
		srcs/tokenizer/token_list.c srcs/tokenizer/syntax_error.c srcs/tokenizer/free_tokens.c srcs/tokenizer/check.c \
		srcs/parser/parse_tokens.c srcs/parser/remove_quotes.c srcs/parser/file_list.c \
		srcs/parser/expand_tokens.c srcs/parser/create_export.c srcs/parser/create_env.c srcs/parser/create_cmd.c \
		srcs/execution/execute_cmds.c srcs/execution/open_here_doc.c srcs/execution/open_files.c srcs/execution/create_pipes.c \
		srcs/execution/send_error.c srcs/execution/redirect_fds.c srcs/execution/wait_children.c srcs/execution/set_exec_path.c \
		srcs/builtins/ft_cd.c srcs/builtins/ft_echo.c srcs/builtins/ft_env.c srcs/builtins/ft_exit.c srcs/builtins/ft_export.c \
		srcs/builtins/ft_pwd.c srcs/builtins/ft_unset.c srcs/utils/exit_code.c srcs/utils/only_spaces.c srcs/utils/free.c \
		srcs/builtins/value.c srcs/execution/signals.c srcs/parser/env_to_envp.c srcs/builtins/error_messages.c \
		srcs/execution/s_syscalls.c srcs/execution/get_file_path.c srcs/execution/expand_hdoc.c srcs/execution/fill_here_doc.c \
		srcs/utils/is_builtin.c srcs/execution/close_hdoc_fds.c srcs/execution/handle_builtins.c srcs/utils/is_executable.c \
		srcs/execution/cmd_not_found.c srcs/parser/expand_digit_tkn.c srcs/utils/get_var_value.c

OBJ = $(SRC:.c=.o)

%.o: %.c
		$(CC) $(CCFLAGS) -o $@ -c $^

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

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
