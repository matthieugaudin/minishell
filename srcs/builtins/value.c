/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:09 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:35:53 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

bool	threshold_exceeded(char *str, long long res, int sign, int i)
{
	if (((-res == (LLONG_MIN / 10) && str[i] > '8')
			|| (-res < (LLONG_MIN / 10) && str[i]))
		|| (sign != -1 && ((res == (LLONG_MAX / 10)
					&& str[i] > '7') || (res > (LLONG_MAX / 10) && str[i]))))
		return (true);
	else
		return (false);
}

int	value(t_data *data, int status, bool to_exit)
{
	if (to_exit)
	{
		free_all(data, status);
		return (1);
	}
	else
	{
		exit_code(status, true);
		return (0);
	}
}
