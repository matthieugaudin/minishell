#include "../../includes/parser.h"

void free_env_node(t_env *node)
{
	if (!node)
		return;
	free(node->name);
	free(node->value);
	free(node);
}

static void handle_value(t_data *data, t_env *new, char *value)
{
	new->value = ft_strdup(value);
	if (!new->value)
	{
		free(new->name);
		free(new);
		free_all(data, EXIT_FAILURE);
	}
}

t_env *ft_new_node(t_data *data, char *name, char *value)
{
	t_env *new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		free_all(data, EXIT_FAILURE);
	new->name = NULL;
	new->value = NULL;
	if (name)
	{
		new->name = ft_strdup(name);
		if (!new->name)
		{
			free(new);
			free_all(data, EXIT_FAILURE);
		}
	}
	if (value)
		handle_value(data, new, value);
	new->next = NULL;
	return (new);
}

void ft_update_exp_node(t_env **exp, t_env *new_node)
{
	t_env *current;

	if (!exp || !new_node)
		return;
	if (*exp == NULL || ft_strcmp(new_node->name, (*exp)->name) < 0)
		return (change_head(exp, new_node));
	current = *exp;
	while (current->next && ft_strcmp(new_node->name, current->next->name) >= 0)
		current = current->next;
	if (ft_strcmp(new_node->name, current->name) == 0)
	{
		if (!new_node->value)
			return;
		free(current->value);
		current->value = ft_strdup(new_node->value);
		free_env_node(new_node);
		return;
	}
	new_node->next = current->next;
	current->next = new_node;
	return;
}

void create_export(t_data *data)
{
	t_env *cur_env;
	t_env *new_node;

	if (!data->env)
		free_all(data, EXIT_FAILURE);
	data->exp = NULL;
	cur_env = data->env;
	while (cur_env)
	{
		if (ft_strcmp(cur_env->name, "_") != 0)
		{
			new_node = ft_new_node(data, cur_env->name, cur_env->value);
			if (!new_node)
				free_all(data, EXIT_FAILURE);
			ft_update_exp_node(&data->exp, new_node);
		}
		cur_env = cur_env->next;
	}
	return;
}
