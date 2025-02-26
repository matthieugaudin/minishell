/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_tab.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 17:52:37 by mgaudin           #+#    #+#             */
/*   Updated: 2025/02/26 17:54:15 by mgaudin          ###   ########.fr       */
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

static void	fill_tab_loop(char **s, char *quote, bool *inside_quotes, int *len)
{
	while (**s && **s == ' ')
		(*s)++;
	while (**s && (**s != ' ' || (**s == ' ' && *inside_quotes)))
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
		(*len)++;
		(*s)++;
	}
}

int	fill_tab(char **tab, char *s)
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
		fill_tab_loop(&s, &quote, &inside_quotes, &len);
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
