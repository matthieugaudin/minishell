/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:20 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 17:52:56 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

static bool	count_subtabs_loop(char **s, char *quote,
	bool *inside_quotes, bool *is_in_word)
{
	if (*quote && **s == *quote)
	{
		*inside_quotes = false;
		*quote = '\0';
	}
	else if (!*inside_quotes && (**s == '\'' || **s == '\"'))
	{
		*inside_quotes = true;
		*quote = **s;
	}
	if (!(*is_in_word))
	{
		*is_in_word = 1;
		return (true);
	}
	return (false);
}

static int	count_subtabs(char *s, char c)
{
	int		nb;
	bool	is_in_word;
	bool	inside_quotes;
	char	quote;

	nb = 0;
	quote = '\0';
	inside_quotes = false;
	while (*s)
	{
		is_in_word = 0;
		while (*s && *s == c)
			s++;
		while (*s && (*s != c || (*s == c && inside_quotes)))
		{
			if (count_subtabs_loop(&s, &quote, &inside_quotes, &is_in_word))
				nb++;
			s++;
		}
		is_in_word = 0;
	}
	return (nb);
}

/*
Split a string into several strings, delimited by a caracter.
The delimiter is not interpreted if it's inside quotes.
*/
char	**split_quotes(char *s)
{
	char	**tab;
	int		tab_len;

	if (!s)
		return (NULL);
	tab_len = count_subtabs(s, ' ');
	tab = malloc((tab_len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[tab_len] = 0;
	if (fill_tab(tab, s))
		return (NULL);
	return (tab);
}
