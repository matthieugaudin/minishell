/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 16:23:50 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/28 17:57:23 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

/*
Check if there are unexpected tokens because some caracters are sticked together
*/
bool	check_line(char *str, char *set)
{
	int	i;
	int	nb_car;

	while (*set)
	{
		i = 0;
		nb_car = 0;
		while (str[i])
		{
			if (!in_quotes(str, i) && str[i] == *set)
				nb_car++;
			else if (!in_quotes(str, i) && nb_car > 0 && str[i] != *set)
				nb_car = 0;
			if (((*set == '<' || *set == '>') && nb_car > 2)
				|| (*set == '|' && nb_car > 1)
				|| (*set == '&' && nb_car > 0))
				return (false);
			i++;
		}
		set++;
	}
	return (true);
}

/*
Check if the line entered has closed quotes in the good sequence.
*/
bool	check_quotes(char *str)
{
	bool	quotes_open;
	char	quote;
	int		i;

	i = 0;
	quotes_open = false;
	while (str[i])
	{
		if (!quotes_open && (str[i] == '\'' || str[i] == '\"'))
		{
			quotes_open = true;
			quote = str[i];
		}
		else if (quotes_open && str[i] == quote)
		{
			quotes_open = false;
		}
		i++;
	}
	return (!quotes_open);
}

void	check_unexpected(char *s)
{
	if (!check_quotes(s))
	{
		printf("minishell: unclosed quotes");
		exit(0);
	}
	if (!check_line(s, "<>|&"))
	{
		printf("minishell: syntax error near unexpected token `<'");
		exit(0);
	}
}