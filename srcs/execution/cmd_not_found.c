#include "../../includes/execution.h"

void	cmd_not_found(t_data *data, char *arg)
{
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putendl_fd(": command not found", 2);
	free_all(data, 127);
}
