#include "../../includes/builtins.h"

char	*find_home_path(t_env *env)
{
	while (env)
	{
		if (ft_strcmp(env->name, "HOME") == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

int	ft_cd(t_data *data, char *args)
{
	char	*curpath;

	if (!args)
		curpath = find_home_path(data->env);
	else
	{
		if (ft_strcmp(args[0], '-') == 0)
	}
}
