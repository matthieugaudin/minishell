/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   only_spaces.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:33:06 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:33:07 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/parser.h"

bool	only_spaces(char *line)
{
	while (*line)
	{
		if (!is_space(*line))
			return (false);
		line++;
	}
	return (true);
}
