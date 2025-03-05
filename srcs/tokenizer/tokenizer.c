/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/19 11:53:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/03/03 13:34:00 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

bool	special_car(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

void	extract_token(char **s, int *len, int *i)
{
	while (**s && **s == ' ')
		(*s)++;
	while (**s && (**s != ' ' || (**s == ' ' && in_quotes(*s - *i, *i)))
		&& (!special_car(**s) || (special_car(**s) && in_quotes(*s - *i, *i))))
	{
		(*i)++;
		(*s)++;
		(*len)++;
	}
	if (*len == 0 && special_car(**s) && !in_quotes(*s - *i, *i))
	{
		(*i)++;
		(*s)++;
		(*len)++;
		if (special_car(**s) && **s == *(*s - 1)
			&& (**s == '<' || **s == '>'))
		{
			(*i)++;
			(*s)++;
			(*len)++;
		}
	}
}

bool	create_tokens(char *s, t_token **head)
{
	char	*value;
	int		len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		extract_token(&s, &len, &i);
		if (*s)
		{
			value = malloc((len + 1) * sizeof(char));
			ft_strlcat(value, s - len, len + 1);
			append_token_node(head, value);
		}
	}
	return (true);
}

t_token	*tokenizer(char *s)
{
	t_token	*head;

	head = NULL;
	check_unexpected(s);
	create_tokens(s, &head);
	return (head);
}

