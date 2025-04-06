#include "../../includes/parser.h"

static void	free_list(t_env **list)
{
	t_env	*current;
	t_env	*next;

	if (list && *list)
	{
		current = *list;
		while (current)
		{
			next = current->next;
			free_env_node(current);
			current = next;
		}
		*list = NULL;
	}
}

void	free_env_exp(t_env **env, t_env **exp)
{
	free_list(env);
	free_list(exp);
}
