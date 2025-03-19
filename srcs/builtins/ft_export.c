#include "../../includes/minishell.h"

int	ft_find_egal_pos(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
	{
		if (!is_posix_std(str[i]) && str[i] != '=')
			return (0);
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (1);
}

int	ft_export(t_data *data, char **args)
{
	size_t	i;
	size_t	egal_place;
	char	*name;
	char	*value;

	i = 0;
	while (args[i])
	{
		egal_place = ft_find_egal_pos(args[i]);
		if (egal_place == 1)
		{

		}
		else if (egal_place)
		{

		}
		i++;
	}
}
