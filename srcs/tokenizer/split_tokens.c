/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_tokens.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 18:16:20 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/24 21:27:07 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"


static size_t	fill_subtab(char **tab, int pos, size_t len)
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

static size_t	fill_tab(char **tab, char const *s, char c)
{
	size_t	len;
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
			else if (*s == '\'' || *s == '\"')
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

static bool	count_subtabs_loop(char const *s, char *quote, bool *inside_quotes, bool *is_in_word)
{
	if (*quote && *s == *quote)
	{
		*inside_quotes = false;
		*quote = '\0';
	}
	else if (*s == '\'' || *s == '\"')
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

static size_t	count_subtabs(char const *s, char c)
{
	size_t	nb;
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

char	**split_tokens(char const *s)
{
	char    **tab;
	size_t  tab_len;

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


/*
invalid tests : "<infile cat -e | ls '>>> outfile' ' okijoihi\"\" ' "
code to the norme
*/
int main(void)
{
	char **res;

	res = quote_split("<infile cat -e | ls '>>> outfile' ' okijoihi\"\" ' ");
	int i = 0;
	while (res[i])
	{
		printf("%s\n", res[i]);
		i++;
	}
}
