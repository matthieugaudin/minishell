/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:17 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:18 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	parse_tokens(t_data *data, t_token *token)
{
	while (token)
	{
		if (is_redir(token->type)
			&& (!token->next || token->next->type != FILE_T))
		{
			syntax_error(data, token->value[0]);
			return (false);
		}
		else if (token->type == PIPE
			&& (!token->prev || !token->next
				|| token->next->type == PIPE))
		{
			syntax_error(data, '|');
			return (false);
		}
		token = token->next;
	}
	return (true);
}
