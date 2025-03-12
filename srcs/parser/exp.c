#include "../../includes/minishell.h"

static t_env	*ft_last_node(t_env *exp)
{
	if (!exp)
		return (NULL);
	while (exp->next != NULL)
	{
		exp = exp->next;
	}
	return (exp);
}

static t_env	*ft_new_node(char *name, char *value)
{
	t_env	*new;

	new = (t_list *)malloc(sizeof(t_list));
	if (!new)
		return (NULL);
	new->name = name;
	new->value= value;
	new->next = NULL;
	return (new);
}

static void	ft_add_back(t_env **exp, t_env *new)
{
	t_env	*last;

	if (!exp)
		return ;
	if (!*exp)
	{
		*exp = new;
		return ;
	}
	last = ft_lstlast(*exp);
	last->next = new;
}

void	create_export(void)
{
	t_env	*cur_env;
	t_env	*cur_exp;
	t_env	**env;
	t_env	**exp;

	env = ft_getter("env");
	cur_env = *env;
	cur_exp = *exp;
	ft_add_back(exp, ft_new_node(cur_env->name, cur_env->value));
	while (cur_env->next)
	{
		cur_env = cur_env->next;
		while (cur_exp)
		{
			if (ft_strcmp(cur_exp->name, cur_env->name) > 0)
				ft_add_back(exp, ft_new_node(cur_env->name, cur_env->value));
			cur_exp = cur_exp->next;
		}
	}
	ft_setter(exp, "exp");
}
