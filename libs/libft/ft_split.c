/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 11:07:44 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/15 12:26:27 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_subtabs(char const *s, char c)
{
	size_t	nb;
	int		is_in_word;

	nb = 0;
	while (*s)
	{
		is_in_word = 0;
		while (*s && *s == c)
		{
			s++;
		}
		while (*s && *s != c)
		{
			if (!is_in_word)
			{
				is_in_word = 1;
				nb++;
			}
			s++;
		}
		is_in_word = 0;
	}
	return (nb);
}

static size_t	ft_fill_subtab(char **tab, int pos, size_t len)
{
	tab[pos] = (char *)malloc((len + 1) * sizeof(char));
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

static size_t	ft_fill_tab(char **tab, char const *s, char c)
{
	size_t	len;
	int		pos;

	pos = 0;
	while (*s)
	{
		len = 0;
		while (*s && *s == c)
		{
			s++;
		}
		while (*s && *s != c)
		{
			len++;
			s++;
		}
		if (len > 0)
		{
			if (ft_fill_subtab(tab, pos, len))
				return (1);
			ft_strlcpy(tab[pos], s - len, len + 1);
			pos++;
		}
	}
	return (0);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;
	size_t	tab_len;

	if (!s)
		return (NULL);
	tab_len = ft_count_subtabs(s, c);
	tab = (char **)malloc((tab_len + 1) * sizeof(char *));
	if (!tab)
		return (NULL);
	tab[tab_len] = 0;
	if (ft_fill_tab(tab, s, c))
		return (NULL);
	return (tab);
}
