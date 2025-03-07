#include "../../includes/minishell.h"

int	ft_pwd(void)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (1);
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (0);
}
