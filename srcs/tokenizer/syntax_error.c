#include "../../includes/tokenizer.h"

void	syntax_error(t_data *data, char c)
{
	ft_putstr_fd("minishell: syntax error near unexepected token '", 2);
	write(2, &c, 1);
	ft_putstr_fd("'\n", 2);
	free_all(data, -2);
	exit_code(2, true);
}
