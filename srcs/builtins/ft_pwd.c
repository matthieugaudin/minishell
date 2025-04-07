#include "../../includes/builtins.h"

int	ft_pwd(t_data* data, bool exit)
{
	char	*path;

	path = getcwd(NULL, 0);
	if (!path)
	{
		perror("pwd");
		return (value(data, 1, exit));
	}
	ft_putendl_fd(path, 1);
	free(path);
	return (value(data, 0, exit));
}
