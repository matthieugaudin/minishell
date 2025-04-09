/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_list.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:12 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:13 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

t_file	*new_file(t_data *data, char *name, enum e_token type, bool hdoc_quotes)
{
	t_file	*new;

	new = malloc(sizeof(t_file));
	if (!new)
		free_all(data, EXIT_FAILURE);
	new->name = name;
	new->type = type;
	new->expand = !hdoc_quotes;
	new->next = NULL;
	return (new);
}

void	add_file_back(t_file **head, t_file *new)
{
	t_file	*last;

	if (*head == NULL)
	{
		*head = new;
		return ;
	}
	last = *head;
	while (last->next)
	{
		last = last->next;
	}
	last->next = new;
}
