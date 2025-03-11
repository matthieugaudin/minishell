#include "../../includes/minishell.h"

static void	**ft_gset_handler(void **set, char *str)
{
	static	t_env		**env;
	static	t_export 	**export;

	if (ft_strcmp(str, "env") == 0)
	{
		if (set)
			env = set;
		return (env);
	}
	else
	{
		if (set)
			export = set;
		return (export);
	}
}

void	ft_setter(void **set, char *str)
{
	ft_gset_handler(set, str);
}

void	**ft_getter(char *str)
{
	return (ft_gset_handler(NULL, str));
}
