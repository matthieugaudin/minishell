/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 08:28:54 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 10:20:52 by mgaudin          ###   ########.fr       */
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

int	count_substr(char *str)
{
	int	i;
	int	count;
	bool  is_word;

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
			if (pecial_char(str[i + 1]) && str[i] == str[i + 1]
				&& (str[i] == '<' || str[i] == '>'))
				i++;
			count++;
			is_word = false;
		}
		i++;
	}
	return (count);
}

int	main(void)
{
	char *line;
	
	line = "<<infile";
	printf("%d", count_substr(line));
}
