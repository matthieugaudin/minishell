/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <mgaudin@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/10 10:26:08 by mgaudin           #+#    #+#             */
/*   Updated: 2024/10/11 11:40:01 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	size_t	i;
	size_t	l_len;

	l_len = ft_strlen(little);
	if (l_len == 0)
		return ((char *)big);
	i = 0;
	while (big[i] && i < len)
	{
		if (ft_strncmp(big + i, little, l_len) == 0 && l_len + i <= len)
			return ((char *)(big + i));
		i++;
	}
	return (NULL);
}
