/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_executable.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:32:53 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:32:54 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/execution.h"

bool	is_executable(char *arg)
{
	int	i;

	if (arg[0] != '.')
		return (false);
	i = 1;
	while (arg[i])
	{
		if (arg[i] == '/')
			return (true);
		i++;
	}
	return (false);
}
