/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenize_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:34 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:35 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

static bool	special_car(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

static void	extract_token(char **s, int *len, int *i)
{
	while (**s && is_space(**s))
	{
		(*s)++;
		(*i)++;
	}
	while (**s && (!is_space(**s) || (is_space(**s) && in_quotes(*s - *i, *i)))
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

static void	create_tokens(t_data *data, char *s, t_token **head)
{
	char	*value;
	int		len;
	int		i;

	i = 0;
	while (*s)
	{
		len = 0;
		extract_token(&s, &len, &i);
		if (*s || len > 0)
		{
			value = malloc((len + 1) * sizeof(char));
			if (!value)
				free_all(data, EXIT_FAILURE);
			ft_strlcpy(value, s - len, len + 1);
			append_token_node(data, head, value);
		}
	}
}

t_token	*tokenize_line(t_data *data, char *s)
{
	char	quote;
	char	line;

	quote = check_quotes(s);
	line = check_line(s, "<>&");
	if (quote != '\0')
	{
		syntax_error(data, quote);
		return (NULL);
	}
	else if (line != '\0')
	{
		syntax_error(data, line);
		return (NULL);
	}
	create_tokens(data, s, &data->tokens);
	return (data->tokens);
}
