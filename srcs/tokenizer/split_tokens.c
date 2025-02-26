/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:28:54 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 17:51:47 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

static bool	special_char(char c)
{
	if (c == '<' || c == '>' || c == '|')
		return (true);
	else
		return (false);
}

/*
Count the number of strings that will be allocated.
*/
int	count_substr(char *str)
{
	int		i;
	int		count;
	bool	is_word;

	i = 0;
	count = 0;
	is_word = false;
	while (str[i])
	{
		if (!is_word && !special_char(str[i]))
		{
			count++;
			is_word = true;
		}
		else if (special_char(str[i]))
		{
			if (special_char(str[i + 1]) && str[i] == str[i + 1]
				&& (str[i] == '<' || str[i] == '>'))
				i++;
			count++;
			is_word = false;
		}
		i++;
	}
	return (count);
}

/*
Split the input line into several strings regarding the following rules. 
First, do not split inside quotes.
Split another time regarding sticked redirections and pipes.
*/
char	**split_tokens(char *s)
{
	char	**quoted_split;

	quoted_split = split_quotes(s);
}
