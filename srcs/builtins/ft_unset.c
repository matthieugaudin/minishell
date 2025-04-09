/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:07 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:08 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

static void	ft_check_and_remove(char *str, t_env **head)
{
	t_env	*prev;
	t_env	*current;

	if (!head || !*head)
		return ;
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

int	ft_unset(t_data *data, char **args, bool exit)
{
	size_t	i;
	int		ret;

	if (!args || !args[0])
		return (value(data, 0, exit));
	i = 0;
	ret = 0;
	while (args[i])
	{
		if (data->env)
			ft_check_and_remove(args[i], &data->env);
		if (data->exp)
			ft_check_and_remove(args[i], &data->exp);
		i++;
	}
	return (value(data, ret, exit));
}
