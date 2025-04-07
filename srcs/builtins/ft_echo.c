#include "../../includes/builtins.h"

static bool	is_n_option(char *str)
{
	size_t	i;

	i = 0;
	if (!str || str[i] != '-')
		return (false);
	i = 1;
	if (!str[i])
		return (false);
	while (str[i] && str[i] == 'n')
		i++;
	return (str[i] == '\0');
}

int	ft_echo(char **args, bool exit)
{
	size_t	i;
	bool	is_n;

	if (!args || !args[0])
	{
		ft_putstr_fd("\n", 1);
		return (value(0, exit));
	}
	i = 1;
	is_n = false;
	while (args[i] && is_n_option(args[i]))
	{
		is_n = true;
		i++;
	}
	while (args[i])
	{
		ft_putstr_fd(args[i], 1);
		if (args[i + 1])
			ft_putstr_fd(" ", 1);
		i++;
	}
	if (!is_n)
		ft_putstr_fd("\n", 1);
	return (value(0, exit));
}
