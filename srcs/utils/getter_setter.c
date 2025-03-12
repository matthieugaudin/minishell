#include "../../includes/minishell.h"

static t_env	**ft_gset_handler(t_env **set, char *str)
{
	static	t_env	**env;
	static	t_env 	**exp;

	if (ft_strcmp(str, "env") == 0)
	{
		if (set)
			env = set;
		return (env);
	}
	else
	{
		if (set)
			exp = set;
		return (exp);
	}
}

void	ft_setter(t_env **set, char *str)
{
	ft_gset_handler(set, str);
}

void	**ft_getter(char *str)
{
	return (ft_gset_handler(NULL, str));
}
