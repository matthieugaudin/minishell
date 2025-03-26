#include "../../includes/builtins.h"

static char	*find_variable_value(t_env *env, char *name)
{
	while (env)
	{
		if (ft_strcmp(env->name, name) == 0)
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

char	*find_path(t_env *env, char *name)
{
	char	*path;

	path = find_variable_value(env, name);
	if (!path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(" not set", 2 );
		return (NULL);
	}
	return (path);
}

int	ft_cd(t_data *data, char *args)
{
	char	*curpath;

	if (!args)
		curpath = find_path(data->env, "HOME");
	else
	{
		if (ft_strcmp(args, "-") == 0)
			curpath = find_path(data->env, "OLDPWD");
		else
			curpath = args;
	}
	chdir(curpath);
}
