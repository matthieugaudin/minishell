#include "../../includes/parser.h"

void	free_envp(char **envp)
{
	int	i;

	i = 0;
	if (!envp)
		return;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp);
}

static int	find_env_size(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

static char	*assign_envp_var(t_env	*current)
{
	char	*tmp;
	char	*str;

	tmp = ft_strjoin(current->name, "=");
	if (!tmp)
		return (NULL);
	str = ft_strjoin(tmp, current->value);
	free(tmp);
	if (!str)
		return (NULL);
	return (str);
}

char	**convert_env_to_envp(t_data *data, t_env *env)
{
	int		i;
	int		env_size;
	char	**envp;
	t_env	*current;

	env_size = find_env_size(env);
	envp = malloc(sizeof(char *) * (env_size + 1));
	if (!envp)
		free_all(data, EXIT_FAILURE);
	i = -1;
	current = env;
	while (current && ++i < env_size)
	{
		envp[i] = assign_envp_var(current);
		if (!envp[i])
		{
			while (--i >= 0)
				free(envp[i]);
			free(envp);
			free_all(data, EXIT_FAILURE);
		}
		current = current->next;
	}
	envp[++i] = NULL;
	return (envp);
}
