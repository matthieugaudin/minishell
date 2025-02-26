/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_quotes.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:20 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 17:03:52 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
#include "../../includes/tokenizer.h"

static int	fill_subtab(char **tab, int pos, int len)
{
	tab[pos] = malloc((len + 1) * sizeof(char));
	if (!tab[pos])
	{
		while (pos >= 0)
		{
			free(tab[pos]);
			pos--;
		}
		free(tab);
		return (1);
	}
	tab[pos][len] = 0;
	return (0);
}

static int	fill_tab(char **tab, char *s, char c)
{
	int		len;
	int		pos;
	bool	inside_quotes;
	char	quote;

	pos = 0;
	quote = '\0';
	inside_quotes = false;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
			s++;
		while (*s && (*s != c || (*s == c && inside_quotes)))
		{
			if (quote && *s == quote)
			{
				inside_quotes = false;
				quote = '\0';
			}
			else if (!inside_quotes && (*s == '\'' || *s == '\"'))
			{
				inside_quotes = true;
				quote = *s;
			}
			len++;
			s++;
		}
		if (len > 0)
		{
			if (fill_subtab(tab, pos, len))
				return (1);
			ft_strlcpy(tab[pos], s - len, len + 1);
			pos++;
		}
	}
	return (0);
}

static bool	count_subtabs_loop(char *s, char *quote,
	bool *inside_quotes, bool *is_in_word)
{
	if (*quote && *s == *quote)
	{
		*inside_quotes = false;
		*quote = '\0';
	}
	else if (!*inside_quotes && (*s == '\'' || *s == '\"'))
	{
		*inside_quotes = true;
		*quote = *s;
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
			if (count_subtabs_loop(s, &quote, &inside_quotes, &is_in_word))
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
	if (fill_tab(tab, s, ' '))
		return (NULL);
	return (tab);
}
