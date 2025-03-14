#include "../../includes/minishell.h"

/*
Verifies that a character follows the posix standards,
meaning that it's an uppercase/lowercase letter, a digit,
or an underscore.
*/
bool	is_posix_std(char c)
{
	if (ft_isalnum(c) || c == '_')
		return (true);
	else
		return (false);
}

/*
Takes an environment variable from envp and returns its name.
*/
static char	*get_env_name(char *envp_str)
{
	char	*env_name;
	int		i;

	i = 0;
	while (is_posix_std(envp_str[i]))
		i++;
	env_name = malloc(sizeof(char) * (i + 1));
	ft_strlcpy(env_name, envp_str, i + 1);
	return (env_name);
}

<<<<<<< HEAD
char	*get_env_value(char *name)
{
	char	*env_value;
	int		i;
	int		j;

	i = 0;
	while (is_posix_std(name[i]))
		i++;
	i++;
	j = 0;
	while (name[i + j])
		j++;
	env_value = malloc(sizeof(char) * (j + 1));
	ft_strlcpy(env_value, name + i, j + 1);
	return (env_value);
}

void	append_env_node(t_env **env, char *envp)
=======
static void	append_env_node(t_env **env, char *envp)
>>>>>>> doley
{
	t_env	*last_node;
	t_env	*node;

	node = malloc(sizeof(t_env));
	node->name = get_env_name(envp);
	node->value = getenv(node->name);
	node->next = NULL;
	if (*env == NULL)
	{
		*env = node;
		return ;
	}
	last_node = *env;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = node;
}

void	create_env(t_data *data, char **envp)
{
	data->env = NULL;
	while (*envp)
	{
		append_env_node(&data->env, *envp);
		envp++;
	}
	create_export(data);
}


