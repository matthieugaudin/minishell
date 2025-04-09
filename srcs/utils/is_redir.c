/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mgaudin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/09 18:33:02 by mgaudin           #+#    #+#             */
/*   Updated: 2025/04/09 18:33:03 by mgaudin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/tokenizer.h"

bool	is_redir(enum e_token type)
{
	if (type == INPUT || type == OUTPUT
		|| type == APPEND || type == HERE_DOC)
		return (true);
	else
		return (false);
}
