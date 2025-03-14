#include "../../includes/minishell.h"

static void	ft_check_and_remove(char *str, t_env **head)
{
    t_env	*prev;
    t_env	*current;

    if (ft_strcmp((*head)->name, str) == 0)
    {
        current = *head;
        *head = (*head)->next;
        free_env_node(current);
        return ;
    }
    prev = *head;
    current = (*head)->next;
    while (current)
    {
        if (ft_strcmp(current->name, str) == 0)
        {
            prev->next = current->next;
            free_env_node(current);
            return ;
        }
        prev = current;
        current = current->next;
    }
}

int	ft_unset(char **args)
{
	size_t		i;
	t_env		**env;
	t_env		**exp;

	i = 0;
	env = ft_getter("env");
	exp = ft_getter("exp");
	while (args[i])
	{
		if (is_posix_std(args[i]))
		{
			if (*env)
				ft_check_and_remove(args[i], env);
			if (*exp)
				ft_check_and_remove(args[i], exp);
		}
		i++;
	}
	return (0);
}
