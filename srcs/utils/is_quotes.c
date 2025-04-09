/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_quotes.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:59 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:33:00 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

bool	is_quotes(t_token *node)
{
	int	i;

	i = 0;
	while (node->value[i])
	{
		if (node->value[i] == '\'' || node->value[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}
