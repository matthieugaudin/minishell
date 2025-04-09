/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   value.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:31:09 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:31:10 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/builtins.h"

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
