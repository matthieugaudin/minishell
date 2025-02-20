/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 08:18:27 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/10 12:14:41 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*s_byte;

	i = 0;
	s_byte = (unsigned char *)s;
	while (i < n)
	{
		s_byte[i++] = (unsigned char)c;
	}
	return (s);
}
