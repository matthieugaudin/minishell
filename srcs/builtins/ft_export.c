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
	size_t	i_egal;
	char	*name;
	char	*value;

	i = 0;
	while (args[i])
	{
		i_egal = ft_find_egal_pos(args[i]);
		if (i_egal == 1)
		{
			
		}
		else if (i_egal)
		{

		}
		i++;
	}
}
