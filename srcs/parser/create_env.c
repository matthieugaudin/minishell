#include "../../includes/parser.h"

void	change_head(t_env **head, t_env *new_node)
{
	new_node->next = *head;
	*head = new_node;
}

void	ft_update_env_node(t_env **env, t_env *new_node)
{
	t_env	*current;

	if (!env || !new_node)
		return ;
	if (*env == NULL)
		return (change_head(env, new_node));
	current = *env;
	while (current)
	{
		if (ft_strcmp(new_node->name, current->name) == 0)
		{
			if (!new_node->value)
				return ;
			free(current->value);
			current->value = ft_strdup(new_node->value);
			free_env_node(new_node);
			return ;
		}
		if (!current->next)
			break ;
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
	return ;
}

/*
Takes an environment variable from envp and returns its name.
*/
char	*get_env_name(char *envp_str)
{
	char	*env_name;
	int		i;

	i = 0;
	while (is_posix_std(envp_str[i]))
		i++;
	env_name = malloc(sizeof(char) * (i + 1));
	if (!env_name)
		return (NULL);
	ft_strlcpy(env_name, envp_str, i + 1);
	return (env_name);
}

static int	append_env_node(t_env **env, char *envp)
{
	t_env	*last_node;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		return (0);
	node->name = get_env_name(envp);
	if (!node->name)
		return (0);
	node->value = ft_strdup(getenv(node->name));
	if (!node->value)
		return (0);
	node->next = NULL;
	if (*env == NULL)
	{
		*env = node;
		return (1);
	}
	last_node = *env;
	while (last_node->next)
		last_node = last_node->next;
	last_node->next = node;
	return (1);
}

void	create_env(t_data *data, char **envp)
{
	data->env = NULL;
	while (*envp)
	{
		if (!append_env_node(&data->env, *envp));
			free_all(data);
		envp++;
	}
	return ;
}
