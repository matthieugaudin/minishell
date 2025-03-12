#include "../../includes/minishell.h"

void	ft_rm_env(char *str, t_env **head)
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

void	ft_rm_exp(char *str, t_export **head)
{
    t_export	*prev;
    t_export	*current;

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
	t_export	**exp;

	i = 0;
	env = ft_getter("env");
	exp = ft_getter("exp");
	while (args[i])
	{
		if (is_posix_std(args[i]))
		{
			if (*env)
				ft_rm_env(args[i], env);
			if (*exp)
				ft_rm_exp(args[i], exp);
		}
		i++;
	}
	return (0);
}
