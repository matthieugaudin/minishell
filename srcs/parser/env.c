#include "../../includes/minishell.h"

bool is_posix_std(char c)
{
	if (ftisalnum(c) || c == '_')
		return (true);
	else
		return (false);
}

char *get_var_name(char *env_var)
{
	char *var_name;
	int i;

	i = 0;
	while (is_posix_std(env_var[i]))
		i++;
	var_name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(var_name, env_var, i + 1);
	return (var_name);
}

void append_env_node(t_env **env, char *str)
{
	t_env *node;

	node = malloc(sizeof(t_env));
	if (*env == NULL)
		*env = node;
	node->name = get_var_name(str);
	node->value = get_var_value(str);
	// set the prev node next to the new one
	node->next = NULL;
}

void parse_envp(char **envp)
{
	size_t i;
	t_env *env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		append_env_node(&env, envp[i]);
		i++;
	}
}
