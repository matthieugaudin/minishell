#include "../../includes/builtins.h"

int	ft_pwd(bool exit)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (value(1, exit));
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (value(0, exit));
}
