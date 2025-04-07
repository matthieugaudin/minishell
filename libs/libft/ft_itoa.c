/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: doley <doley@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/14 12:47:45 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/08 00:26:03 by doley            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	ft_count_digit(int n)
{
	size_t	nb;

	if (n < 0)
		n = -n;
	nb = 1;
	while (n >= 10)
	{
		nb++;
		n /= 10;
	}
	return (nb);
}

char	*ft_itoa(int n)
{
	size_t	nb_digits;
	size_t	i;
	char	*res;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	nb_digits = ft_count_digit(n) + (n < 0);
	res = (char *)ft_calloc((nb_digits + 1), sizeof(char));
	if (!res)
		return (NULL);
	if (n < 0)
	{
		res[0] = '-';
		n = -n;
	}
	i = 1;
	while (n > 0)
	{
		res[nb_digits - i] = (n % 10) + '0';
		n /= 10;
		i++;
	}
	return (res);
}
