#include "../../includes/builtins.h"

int	ft_env(t_data* data, t_env *env, char **args, bool exit)
{
	if (args && args[1])
	{
		ft_putstr_fd("minishell: env: '", 2);
		ft_putstr_fd(args[1], 2);
		ft_putendl_fd("': No such file or directory", 2);
		return (value(data, 127, exit));
	}
	while (env)
	{
		ft_putstr_fd(env->name, 1);
		ft_putstr_fd("=", 1);
		if (env->value)
			ft_putendl_fd(env->value, 1);
		else
			ft_putchar_fd('\n', 1);
		env = env->next;
	}
	return (value(data, 0, exit));
}
