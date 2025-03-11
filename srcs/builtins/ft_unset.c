#include "../../includes/minishell.h"

void	ft_check_and_remove(char *str)
{
	
}

int	ft_unset(char **args)
{
	size_t	i;

	i = 0;
	while (args[i])
	{
		if (is_posix_std(args[i]))
		{
			ft_check_and_remove(args[i]);
		}
		i++;
	}
}
