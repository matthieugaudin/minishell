/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 12:00:30 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/10 18:41:24 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	size_t	i;
	char	*ps;

	ps = (char *)malloc(sizeof(char) * (ft_strlen(s) + 1));
	if (!ps)
		return (ps);
	i = 0;
	while (s[i])
	{
		ps[i] = s[i];
		i++;
	}
	ps[i] = 0;
	return (ps);
}
