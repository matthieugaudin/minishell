#include "../../includes/builtins.h"

int	ft_cd_error_path(char *curpath)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putstr_fd(curpath, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
	return (1);
}

int	ft_cd_too_many_args(void)
{
	ft_putstr_fd("minishell: cd: ", 2);
	ft_putendl_fd("too many arguments", 2);
	return (1);
}
