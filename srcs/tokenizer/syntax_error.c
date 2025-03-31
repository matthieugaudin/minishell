#include "../../includes/tokenizer.h"

void	syntax_error(t_token *tokens, char c)
{
	free_tokens(tokens, false);
	ft_putstr_fd("minishell: syntax error near unexepected token '", 2);
	write(2, &c, 1);
	ft_putstr_fd("'\n", 2);
	exit_code(2, true);
}
