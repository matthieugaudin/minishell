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

static char	*find_path(t_env *env, char *name)
{
	char	*path;

	path = find_variable_value(env, name);
	if (!path)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(name, 2);
		ft_putendl_fd(" not set", 2);
		return (NULL);
	}
	return (path);
}

static void	update_pwd_var(t_env *list, char *name, char *value)
{
	t_env	*current;

	current = list;
	while (current)
	{
		if (ft_strcmp(name, current->name) == 0)
		{
			free(current->value);
			current->value = ft_strdup(value);
			return ;
		}
		current = current->next;
	}
}

static void	update_pwd(t_data *data)
{
	char	*old_pwd;
	char	new_pwd[PATH_MAX];

	old_pwd = find_variable_value(data->env, "PWD");
	if (old_pwd)
	{
		update_pwd_var(data->env, "OLDPWD", old_pwd);
		update_pwd_var(data->exp, "OLDPWD", old_pwd);
	}
	if (getcwd(new_pwd, PATH_MAX) != NULL)
	{
		update_pwd_var(data->env, "PWD", new_pwd);
		update_pwd_var(data->exp, "PWD", new_pwd);
	}
}

int	ft_cd(t_data *data, char **args, bool exit)
{
	char	*curpath;

	if (!args)
		curpath = find_path(data->env, "HOME");
	else if (args[1])
		return (value(data, ft_cd_too_many_args(), exit));
	else if (ft_strcmp(args[0], "-") == 0)
	{
		curpath = find_path(data->env, "OLDPWD");
		if (curpath)
			ft_putendl_fd(curpath, 1);
	}
	else
		curpath = args[0];
	if (!curpath)
		return (value(data, 1, exit));
	if (chdir(curpath) != 0)
		return (value(data, ft_cd_error_path(curpath), exit));
	update_pwd(data);
	return (value(data, 0, exit));
}
