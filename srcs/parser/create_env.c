#include "../../includes/parser.h"

void	change_head(t_env **head, t_env *new_node)
{
	new_node->next = *head;
	*head = new_node;
}

void	ft_update_env_node(t_data *data, t_env **env, t_env *new_node)
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
			if (!current->value)
				free_all(data, EXIT_FAILURE);
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
char	*get_env_name(t_data *data, char *envp_str)
{
	char	*env_name;
	int		i;

	i = 0;
	while (is_posix_std(envp_str[i]))
		i++;
	env_name = malloc(sizeof(char) * (i + 1));
	if (!env_name)
		free_all(data, EXIT_FAILURE);
	ft_strlcpy(env_name, envp_str, i + 1);
	return (env_name);
}

static void	append_env_node(t_data *data, t_env **env, char *envp)
{
	t_env	*last_node;
	t_env	*node;

	node = malloc(sizeof(t_env));
	if (!node)
		free_all(data, EXIT_FAILURE);
	node->name = get_env_name(data, envp);
	if (!node->name)
		return ;
	node->value = ft_strdup(getenv(node->name));
	if (!node->value)
		free_all(data, EXIT_FAILURE);
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
	return ;
}

void	create_env(t_data *data, char **envp)
{
	data->env = NULL;
	while (*envp)
	{
		append_env_node(data, &data->env, *envp);
		envp++;
	}
	return ;
}
