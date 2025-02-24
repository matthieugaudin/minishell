/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 17:39:56 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/15 12:31:18 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_byte;

	s_byte = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (s_byte[i] == (unsigned char)c)
			return (s_byte + i);
		i++;
	}
	return (NULL);
}
