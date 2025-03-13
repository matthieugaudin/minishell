#include "../../includes/minishell.h"

static t_env	*ft_new_node(char *name, char *value)
{
	t_env	*new;

	new = (t_env *)malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->name = name;
	new->value= value;
	new->next = NULL;
	return (new);
}

void	ft_insert_node(t_env **exp, t_env *new_node)
{
	t_env	*current;

	if (!exp || !new_node)
		return;
	if (*exp == NULL || strcmp(new_node->name, (*exp)->name) < 0)
	{
		new_node->next = *exp;
		*exp = new_node;
		return;
	}
	current = *exp;
	while (current->next && strcmp(new_node->name, current->next->name) > 0)
	{
		current = current->next;
	}
	new_node->next = current->next;
	current->next = new_node;
}

void	create_export(void)
{
	t_env	*exp;
	t_env	*cur_env;
	t_env	*new_node;
	t_env	**env;

	env = ft_getter("env");
	if (!env)
		return ;
	cur_env = *env;
	while (cur_env)
	{
		new_node = ft_new_node(cur_env->name, cur_env->value);
		if (new_node)
			return ;
		ft_insert_node(&exp, new_node);
		cur_env = cur_env->next;
	}
	ft_setter(&exp, "exp");
}
