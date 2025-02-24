/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/09 16:56:27 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/19 19:54:30 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	ldst;
	size_t	lsrc;

	ldst = ft_strlen(dst);
	lsrc = ft_strlen(src);
	if (size <= ldst)
		ldst = size;
	if (ldst == size)
		return (ldst + lsrc);
	if (ldst + lsrc < size)
		ft_memcpy(dst + ldst, src, lsrc + 1);
	else
	{
		ft_memcpy(dst + ldst, src, size - ldst - 1);
		dst[size - 1] = '\0';
	}
	return (ldst + lsrc);
}
