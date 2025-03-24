#include "../../includes/execution.h"

void	send_error(char *arg, int errno_cpy)
{
	if (errno_cpy != -1)
		errno = errno_cpy;
	ft_putstr_fd("minishell: ", 2);
	ft_putstr_fd(arg, 2);
	ft_putstr_fd(": ", 2);
	ft_putendl_fd(strerror(errno), 2);
}
