/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/11 17:24:32 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/19 19:44:35 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_is_set(char c, char const *set)
{
	size_t	i;

	i = 0;
	while (set[i])
	{
		if (set[i++] == c)
			return (1);
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	int		s;
	int		e;
	int		i;
	char	*str;

	if (!s1)
		return (NULL);
	s = 0;
	while (s1[s] && ft_is_set(s1[s], set))
		s++;
	e = ft_strlen(s1) - 1;
	while (e > s && ft_is_set(s1[e], set))
		e--;
	str = (char *)ft_calloc(e - s + 2, sizeof(char));
	if (!str)
		return (str);
	i = 0;
	while (s1[s + i] && s + i - 1 < e)
	{
		str[i] = s1[s + i];
		i++;
	}
	return (str);
}
