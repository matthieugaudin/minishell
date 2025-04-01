#include "../includes/parser.h"

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

char	**convert_env_to_envp(t_env *env)
{
	int		i;
	int		env_size;
	char	**envp;

	env_size = find_env_size(env);
	envp = malloc(sizeof(char *) * env_size + 1);
	if (!envp)
		return (NULL);
	i = 0;
	while (i < env_size)
	{
		
	}
}
