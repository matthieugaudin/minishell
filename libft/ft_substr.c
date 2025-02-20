/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 14:32:22 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/19 19:43:34 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	size_t	s_len;
	char	*ps;

	if (!s)
		return (NULL);
	s_len = ft_strlen(s);
	i = 0;
	while (i < len && start + i < s_len && s[start + i])
		i++;
	ps = (char *)ft_calloc((i + 1), sizeof(char));
	if (!ps)
		return (NULL);
	i = 0;
	while (i < len && start + i < s_len && s[start + i])
	{
		ps[i] = s[start + i];
		i++;
	}
	return (ps);
}
